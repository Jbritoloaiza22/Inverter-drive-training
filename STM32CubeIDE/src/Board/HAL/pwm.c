/**
 * @file pwm.c
 * @brief PWM driver using TIM1 for three-phase control.
 *
 * This module implements a low-level PWM driver for TIM1 to generate
 * three-phase complementary PWM signals typically used in motor
 * control or inverter applications.
 *
 * @author Jesus Daniel Britoloaiza
 *
 * @copyright
 * Copyright (c) 2026 Jesus Daniel Britoloaiza
 *
 * @license
 * This source code is provided for educational and research purposes.
 */
#include "pwm.h"
#include "KernelInterface.h"
#include "stm32g031xx.h"


/**
 * @brief Initialize PWM peripheral using TIM1.
 *
 * Configures TIM1 registers for PWM generation on channels 1, 2 and 3,
 * including complementary outputs (CHxN). The timer is configured with
 * the selected prescaler and auto-reload value corresponding to the
 * desired PWM frequency (e.g., 16 kHz).
 *
 * This function:
 * - Resets timer configuration registers
 * - Sets the PWM frequency using ARR
 * - Configures PWM mode for channels 1, 2 and 3
 * - Enables complementary outputs
 * - Configures deadtime and break settings
 * - Generates an update event to load registers
 *
 * @note Must be called before starting PWM generation.
 *
 * @author Jesus Daniel Britoloaiza
 */
void pwm_Init(void)
{
  /* Configure TIM1 */
  TIM1->CR1   = 0;
  TIM1->CR2   = 0;
  TIM1->SMCR  = 0;
  TIM1->DIER  = 0;
  TIM1->PSC   = 0;
  TIM1->ARR   = dPWM_FREQ_16KHZ;
  TIM1->RCR   = 0;
  TIM1->CCR1  = 0;
  TIM1->CCR2  = 0;
  TIM1->CCR3  = 0;
  TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE;
  TIM1->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC3FE;
  TIM1->CCMR3 = 0;
  TIM1->CCER  = TIM_CCER_CC1E | TIM_CCER_CC1NE | TIM_CCER_CC2E | TIM_CCER_CC2NE | TIM_CCER_CC3E | TIM_CCER_CC3NE;
  TIM1->CNT   = 0;
  TIM1->BDTR  = TIM_BDTR_BK2P | TIM_BDTR_BKP | TIM_BDTR_MOE;
  TIM1->DCR   = 0;
  TIM1->DMAR  = 0;
  TIM1->CR1   |=  TIM_CR1_CEN | TIM_CR1_DIR | TIM_CR1_CMS_1 | TIM_CR1_ARPE | TIM_CR1_CKD_0;
  TIM1->EGR   = TIM_EGR_UG;
}

/**
 * @brief Start PWM generation.
 *
 * Enables the TIM1 counter allowing PWM signals to start toggling
 * on the configured channels.
 *
 * @author Jesus Daniel Britoloaiza
 */
void pwm_Start(void)
{
  TIM1->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Update compare values for the three PWM phases.
 *
 * Updates the compare registers (CCR1, CCR2, CCR3) corresponding
 * to phases A, B, and C. These values define the duty cycle of
 * each PWM output.
 *
 * @param compareA Compare value for phase A (TIM1->CCR1)
 * @param compareB Compare value for phase B (TIM1->CCR2)
 * @param compareC Compare value for phase C (TIM1->CCR3)
 *
 * @note Values must be between 0 and TIM1->ARR.
 *
 * @author Jesus Daniel Britoloaiza
 */
void pwm_UpdatePhaseCompare(uint32_t compareA, uint32_t compareB, uint32_t compareC)
{
  TIM1->CCR1 = compareA;
  TIM1->CCR2 = compareB;
  TIM1->CCR3 = compareC;
}

/**
 * @brief Set duty cycle for PWM channel 1.
 *
 * Writes directly to TIM1 CCR1 register to update the duty cycle
 * for channel 1.
 *
 * @param ui32DutyCycle Duty cycle compare value (0 to ARR)
 *
 * @author Jesus Daniel Britoloaiza
 */
void pwm_channel1_set_duty(uint32_t ui32DutyCycle){
	TIM1->CCR1 = ui32DutyCycle;
}

/**
 * @brief Set duty cycle for PWM channel 2.
 *
 * Writes directly to TIM1 CCR2 register to update the duty cycle
 * for channel 2.
 *
 * @param ui32DutyCycle Duty cycle compare value (0 to ARR)
 *
 * @author Jesus Daniel Britoloaiza
 */
void pwm_channel2_set_duty(uint32_t ui32DutyCycle){
	TIM1->CCR2 = ui32DutyCycle;
}

/**
 * @brief Set duty cycle for PWM channel 3.
 *
 * Writes directly to TIM1 CCR3 register to update the duty cycle
 * for channel 3.
 *
 * @param ui32DutyCycle Duty cycle compare value (0 to ARR)
 *
 * @author Jesus Daniel Britoloaiza
 */
void pwm_channel3_set_duty(uint32_t ui32DutyCycle){
	TIM1->CCR3 = ui32DutyCycle;
}

/**
 * @brief PWM callback function.
 *
 * Alias to PWM_Init(), can be called as a callback or initialization routine.
 */
void cbPWM(void){
	pwm_Init();
	pwm_Start();
}

/**
 * @brief Update PWM duty cycle for phase A via kernel interface.
 *
 * Provides a hardware abstraction layer allowing the application
 * to control phase A duty cycle without direct access to the HAL
 * or low-level PWM driver.
 *
 * @param ui32DutyCycle Duty cycle value.
 */
void vKernelInterface_SetPhaseADuty(uint32_t ui32DutyCycle){
	pwm_channel1_set_duty(ui32DutyCycle);
}

/**
 * @brief Update PWM duty cycle for phase B via kernel interface.
 *
 * Provides an interface between the application layer and the
 * underlying PWM driver managed by the kernel.
 *
 * @param ui32DutyCycle Duty cycle value.
 */
void vKernelInterface_SetPhaseBDuty(uint32_t ui32DutyCycle){
	pwm_channel1_set_duty(ui32DutyCycle);
}

/**
 * @brief Update PWM duty cycle for phase C via kernel interface.
 *
 * Allows the application to control the duty cycle of phase C
 * through the kernel abstraction layer.
 *
 * @param ui32DutyCycle Duty cycle value.
 */
void vKernelInterface_SetPhaseCDuty(uint32_t ui32DutyCycle){
	pwm_channel1_set_duty(ui32DutyCycle);;
}

