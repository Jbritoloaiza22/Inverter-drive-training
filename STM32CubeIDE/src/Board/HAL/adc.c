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

/**
 * @brief Initialize ADC peripheral with PWM-synchronized external trigger.
 *
 * Configures ADC in single conversion mode using TIM1_TRGO2 as external
 * trigger. The ADC is intended for motor control applications (e.g.
 * single-shunt current sensing), where deterministic sampling relative to the
 * PWM cycle is required.
 *
 * @param self Pointer to ADC_t structure containing configuration (e.g.
 * channel).
 */
void vADC_Init(ADC_t *self) {
  /* 1. Enable ADC clock - this is in rcc.c file*/

  /* 2. Enable GPIO analog pins (ejemplo: PA0 = ADC_IN0) - this is in gpio
   * module */

  /* 3. Disable ADC before configuration */
  if (ADC1->CR & ADC_CR_ADEN) {
    ADC1->CR |= ADC_CR_ADDIS; /* Disable ADC */
    while (ADC1->CR & ADC_CR_ADEN)
      ; /* Wait until disabled*/
  }

  /* 3.1 make sure that there isnt conversion in progress */
  if (ADC1->CR & ADC_CR_ADSTART) {
    ADC1->CR |= ADC_CR_ADSTP;
    while (ADC1->CR & ADC_CR_ADSTP)
      ;
  }

  /* 4. Configure ADC clock (asynchronous) */
  ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;
  /* 5. Data alignment (right), 5. Resolution (12-bit) */
  ADC1->CFGR1 &= ~(ADC_CFGR1_RES | ADC_CFGR1_ALIGN);

  /* 6. External trigger */
  ADC1->CFGR1 &= ~ADC_CFGR1_EXTSEL;
  ADC1->CFGR1 |= (0b000 << ADC_CFGR1_EXTSEL_Pos); /* TIM1_TRGO2*/
  ADC1->CFGR1 &= ~ADC_CFGR1_EXTEN;
  ADC1->CFGR1 |= ADC_CFGR1_EXTEN_0; /* rising edge */

  /* 7. Select channel */
  ADC1->CHSELR = (1U << self->ui8channel);

  /* 8. Single conversion mode */
  ADC1->CFGR1 &= ~ADC_CFGR1_CONT;

  /* 9. sampling */
  ADC1->SMPR = (0U << 0) | (0U << 4);
  ADC1->SMPR |= (1U << self->ui8channel);

  /* 10. Clear ALL flags */
  ADC1->ISR = 0xFFFFFFFF;

  /* 11. enable regulator */
  ADC1->CR |= ADC_CR_ADVREGEN;
  for (volatile int i = 0; i < 1000; i++)
    ;

  /*12. calibrate ADC */
  vADC_Calibrate();

  /*13. enable adc*/
  vADC_Enable();

  /* 14. Enable End Of Conversion interrupt */
  ADC1->IER |= ADC_IER_EOCIE;

  /* 15. Mark as initialized */
  self->ui8initialized = 1;

  /* 16. only to trigger for first time */
  ADC1->CR |= ADC_CR_ADSTART;
}

/**
 * @brief Perform ADC calibration.
 *
 * Ensures improved accuracy by calibrating internal ADC parameters.
 * Must be executed with ADC disabled and no ongoing conversion.
 */
void vADC_Calibrate(void) {
  /* 1. make sure ADC off */
  if (ADC1->CR & ADC_CR_ADEN) {
    ADC1->CR |= ADC_CR_ADDIS;
    while (ADC1->CR & ADC_CR_ADEN)
      ;
  }

  /* 2. stop any conversion in progress */
  if (ADC1->CR & ADC_CR_ADSTART) {
    ADC1->CR |= ADC_CR_ADSTP;
    while (ADC1->CR & ADC_CR_ADSTP)
      ;
  }

  /* 3. make sure ADCAL is in 0 */
  if (ADC1->CR & ADC_CR_ADCAL) {
    return;
  }

  /* 4. calibration init */
  ADC1->CR |= ADC_CR_ADCAL;

  /* 5. delay to ensure calibration */
  uint32_t ui32timeout = 1000000;
  while ((ADC1->CR & ADC_CR_ADCAL) && ui32timeout--)
    ;

  if (ui32timeout == 0) {
    while (1)
      ; /*breakpoint*/
  }
}

/**
 * @brief Enable ADC peripheral.
 *
 * Activates ADC and waits until it is ready to start conversions.
 */
void vADC_Enable(void) {
  if (!(ADC1->CR & ADC_CR_ADEN)) {
    /* 1. Enable regulator */
    ADC1->CR &= ~ADC_CR_ADVREGEN;
    ADC1->CR |= ADC_CR_ADVREGEN;

    for (volatile uint32_t ui32i = 0; ui32i < 1000; ui32i++)
      ;

    /* 2. Enable ADC */
    ADC1->CR |= ADC_CR_ADEN;

    /* 3. Wait ready */
    while (!(ADC1->ISR & ADC_ISR_ADRDY))
      ;

    /* 4. Clear flag */
    ADC1->ISR = ADC_ISR_ADRDY;
  }
}

/**
 * @brief Disable ADC peripheral.
 *
 * Safely stops ADC operation.
 */
void vADC_Disable(void) {
  if (ADC1->CR & ADC_CR_ADEN) {
    ADC1->CR |= ADC_CR_ADDIS;
    while (ADC1->CR & ADC_CR_ADEN)
      ;
  }
}

int16_t vADC_i16ReadRaw(void) { return (int16_t)ADC1->DR; }
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
  adc.ui8channel = 6; /* PA6: Curr_fdbk */
  adc.ui8initialized = 0;
  vADC_Init(&adc);
}