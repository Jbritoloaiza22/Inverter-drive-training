/**
 * @file adc.c
 * @brief ADC configuration and control for STM32G031 microcontroller.
 *
 * This module implements the ADC driver for the STM32G031, providing
 * initialization, calibration, and data acquisition functionalities.
 * It supports single-shunt current sensing and other analog measurements
 * required for motor control applications.
 *
 * The driver is designed to work with timer-triggered conversions to ensure
 * precise synchronization with PWM signals, which is critical for accurate
 * current reconstruction in FOC algorithms.
 *
 * Features:
 * - ADC initialization and calibration sequence
 * - Configurable channel selection and sampling time
 * - Timer-triggered conversion support (e.g., synchronized with PWM)
 * - Interrupt-based end-of-conversion handling
 * - Optional DMA support for efficient data transfer
 *
 * @note
 * This configuration is tailored for the EVS32 motor control board,
 * where the ADC is primarily used for single-shunt current measurement
 * and DC bus voltage sensing.
 *
 * @warning
 * Incorrect trigger configuration or sampling time may lead to
 * distorted current measurements, directly affecting control stability.
 *
 * @author
 * Jesus Daniel Britoloaiza
 *
 * @copyright
 * Copyright (c) 2026 Jesus Daniel Britoloaiza
 *
 * @license
 * This source code is provided for educational and research purposes.
 */

#include "adc.h"
static ADC_t adc;


void vADC_Init(ADC_t *self)
{
    /* 1. Enable ADC clock - this is in rcc.c file*/

    /* 2. Enable GPIO analog pins (ejemplo: PA0 = ADC_IN0) - this is in gpio module */

    /* 3. Disable ADC before configuration */
    if(ADC1->CR & ADC_CR_ADEN) {
        ADC1->CR |= ADC_CR_ADDIS; // Disable ADC
        while (ADC1->CR & ADC_CR_ADEN); // Wait until disabled
    }
    
    /* 4. Configure ADC clock (asynchronous) */
    ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;

    /* 5. Resolution (12-bit) */
    ADC1->CFGR1 &= ~ADC_CFGR1_RES;

    /* 6. Data alignment (right) */
    ADC1->CFGR1 &= ~ADC_CFGR1_ALIGN;

    /* 7. External trigger */
    ADC1->CFGR1 &= ~ADC_CFGR1_EXTSEL;
    ADC1->CFGR1 |= (1 << ADC_CFGR1_EXTSEL_Pos); /* TIM1_CC4*/
    ADC1->CFGR1 &= ~ADC_CFGR1_EXTEN;
    ADC1->CFGR1 |= ADC_CFGR1_EXTEN_0; /* rising edge */

    /* 8. Sampling time  */
    ADC1->SMPR = (2U << 0) | (4U << 4);
    ADC1->SMPR |= (1U << self->channel);

    /* 9. Select channel */
    ADC1->CHSELR = (1U << self->channel);

    /* 10. Single conversion mode (no continuous) */
    ADC1->CFGR1 &= ~ADC_CFGR1_CONT;

    /* 11. Clear ADRDY flag */
    ADC1->ISR = ADC_ISR_ADRDY;
    self->initialized = 1;

    /*calibrate call */
    vADC_Calibrate();

    /*enable adc*/
    vADC_Enable();

    /* enable interrupt for adc conversion completed */
    ADC1->IER |= ADC_IER_EOCIE;  // End Of Conversion interrupt enable
}


void vADC_Calibrate(void){
    if (ADC1->CR & ADC_CR_ADEN)
    {
        ADC1->CR |= ADC_CR_ADDIS;
        while (ADC1->CR & ADC_CR_ADEN);
    }

    ADC1->CR |= ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL);
}


void vADC_Enable(void){
    if (!(ADC1->CR & ADC_CR_ADEN))
    {
        ADC1->CR |= ADC_CR_ADEN;
        while (!(ADC1->ISR & ADC_ISR_ADRDY));
        ADC1->ISR = ADC_ISR_ADRDY;
    }
}


void vADC_Disable(void){
    if (ADC1->CR & ADC_CR_ADEN)
    {
        ADC1->CR |= ADC_CR_ADDIS;
        while (ADC1->CR & ADC_CR_ADEN);
    }
}

/* =========================================================
 * CALLBACK (KERNEL)
 * ========================================================= */

/**
 * @brief ADC initialization callback.
 *
 * This function is intended to be registered within the kernel
 * initialization sequence. It initializes the global ADC object
 * and configures the necessary settings.
 *
 * Acts as the entry point for ADC setup during system startup.
 */
void cbADC(void) { 
    adc.channel = 6; /* PA6: Curr_fdbk */
    adc.initialized = 0;
    vADC_Init(&adc); 
}