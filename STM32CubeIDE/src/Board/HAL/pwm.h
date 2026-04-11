/**
 * @file pwm.h
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
#ifndef __PWM_H
#define __PWM_H

#include "stm32g0xx_hal.h"
/** @brief PWM frequency setting for 8 kHz */
#define dPWM_FREQ_8KHZ      3999U

/** @brief PWM frequency setting for 16 kHz */
#define dPWM_FREQ_16KHZ     1999U

/** @brief PWM frequency setting for 32 kHz */
#define dPWM_FREQ_32KHZ     999U

/** @brief PWM frequency setting for 64 kHz */
#define dPWM_FREQ_64KHZ     499U

/** @brief PWM frequency setting for 128 kHz */
#define dPWM_FREQ_128KHZ    249U

/** @brief PWM frequency setting for 256 kHz */
#define dPWM_FREQ_256KHZ    124U

/** @brief PWM frequency setting for 512 kHz */
#define dPWM_FREQ_512KHZ    61U

/**
 * @brief Initialize PWM peripheral using TIM1.
 *
 * Configures TIM1 to generate three-phase complementary PWM signals.
 * The timer is configured according to the selected ARR value which
 * determines the PWM switching frequency.
 */
void pwm_Init(void);

/**
 * @brief Start PWM generation.
 *
 * Enables TIM1 counter allowing PWM outputs to start switching.
 */
void pwm_Start(void);

/**
 * @brief Update duty cycle for three phases.
 *
 * Writes new compare values into CCR registers for phases A, B and C.
 *
 * @param compareA Duty cycle value for phase A (CCR1)
 * @param compareB Duty cycle value for phase B (CCR2)
 * @param compareC Duty cycle value for phase C (CCR3)
 */
void pwm_UpdatePhaseCompare(uint32_t compareA, uint32_t compareB, uint32_t compareC);

/**
 * @brief Set duty cycle for PWM channel 1.
 *
 * Updates the compare register CCR1 which controls the duty cycle
 * of phase A output.
 *
 * @param ui32DutyCycle Duty cycle value (0 to ARR)
 */
void pwm_channel1_set_duty(uint32_t ui32DutyCycle);

/**
 * @brief Set duty cycle for PWM channel 2.
 *
 * Updates the compare register CCR1 which controls the duty cycle
 * of phase B output.
 *
 * @param ui32DutyCycle Duty cycle value (0 to ARR)
 */
void pwm_channel2_set_duty(uint32_t ui32DutyCycle);

/**
 * @brief Set duty cycle for PWM channel 3.
 *
 * Updates the compare register CCR1 which controls the duty cycle
 * of phase C output.
 *
 * @param ui32DutyCycle Duty cycle value (0 to ARR)
 */
void pwm_channel3_set_duty(uint32_t ui32DutyCycle);

#endif /* __PWM_H */
