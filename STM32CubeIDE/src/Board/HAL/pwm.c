/**
 * @file pwm.c
 * @brief PWM driver using TIM1 for three-phase control (OOP style).
 *
 * This module implements a low-level PWM driver for TIM1 to generate
 * three-phase complementary PWM signals typically used in motor
 * control or inverter applications.
 *
 * The driver is structured in an object-oriented style using C,
 * allowing better scalability for SPWM, SVPWM, and FOC systems.
 *
 * @author Jesus Daniel Britoloaiza
 * @copyright Copyright (c) 2026
 */

#include "pwm.h"
#include "KernelInterface.h"
#include "stm32g031xx.h"

PWM_t pwm;

/* =========================================================
 * CONSTRUCTOR
 * ========================================================= */

/**
 * @brief Initializes TIM1 as a 3-phase PWM generator.
 *
 * Configures TIM1 for PWM generation on channels 1, 2, and 3,
 * including complementary outputs (CHxN).
 *
 * The configuration includes:
 * - PWM frequency via ARR
 * - PWM mode 1
 * - Preload enable
 * - Complementary outputs enabled
 * - Main output enable (MOE)
 *
 * @param self Pointer to PWM object instance.
 * @param arr Auto-reload value defining PWM period.
 */
void vPWM_Init(PWM_t *self, uint32_t arr)
{
    self->arr = arr;
    self->enabled = 0;

    TIM1->CR1   = 0;
    TIM1->CR2   = 0;
    TIM1->SMCR  = 0;
    TIM1->DIER  = 0;

    TIM1->PSC   = 0;
    TIM1->ARR   = arr;

    TIM1->CCR1  = 0;
    TIM1->CCR2  = 0;
    TIM1->CCR3  = 0;

    TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 |
                  TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE |
                  TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 |
                  TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE;

    TIM1->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 |
                  TIM_CCMR2_OC3PE | TIM_CCMR2_OC3FE;

    TIM1->CCER  = TIM_CCER_CC1E | TIM_CCER_CC1NE |
                  TIM_CCER_CC2E | TIM_CCER_CC2NE |
                  TIM_CCER_CC3E | TIM_CCER_CC3NE;

    TIM1->BDTR  = TIM_BDTR_MOE;

    TIM1->EGR   = TIM_EGR_UG;
}

/* =========================================================
 * START
 * ========================================================= */

/**
 * @brief Starts PWM generation on TIM1.
 *
 * Enables the TIM1 counter, allowing PWM signals to be
 * output on configured channels.
 *
 * @param self Pointer to PWM object instance.
 */
void vPWM_Start(PWM_t *self)
{
    TIM1->CR1 |= TIM_CR1_CEN;
    self->enabled = 1;
}

/* =========================================================
 * DUTY CYCLE CONTROL
 * ========================================================= */

/**
 * @brief Sets duty cycle for Phase A (TIM1 Channel 1).
 *
 * @param self Pointer to PWM object instance.
 * @param duty Duty cycle value (0 to ARR).
 */
void vPWM_SetPhaseA(PWM_t *self, uint32_t duty)
{
    TIM1->CCR1 = duty;
}

/**
 * @brief Sets duty cycle for Phase B (TIM1 Channel 2).
 *
 * @param self Pointer to PWM object instance.
 * @param duty Duty cycle value (0 to ARR).
 */
void vPWM_SetPhaseB(PWM_t *self, uint32_t duty)
{
    TIM1->CCR2 = duty;
}

/**
 * @brief Sets duty cycle for Phase C (TIM1 Channel 3).
 *
 * @param self Pointer to PWM object instance.
 * @param duty Duty cycle value (0 to ARR).
 */
void vPWM_SetPhaseC(PWM_t *self, uint32_t duty)
{
    TIM1->CCR3 = duty;
}

/**
 * @brief Updates all three PWM phases simultaneously.
 *
 * Useful for synchronized updates in:
 * - SPWM
 * - SVPWM
 * - FOC control loops
 *
 * @param self Pointer to PWM object instance.
 * @param a Duty cycle for phase A.
 * @param b Duty cycle for phase B.
 * @param c Duty cycle for phase C.
 */
void vPWM_SetPhases(PWM_t *self,
                   uint32_t a,
                   uint32_t b,
                   uint32_t c)
{
    TIM1->CCR1 = a;
    TIM1->CCR2 = b;
    TIM1->CCR3 = c;
}

/* =========================================================
 * CALLBACK
 * ========================================================= */

/**
 * @brief PWM initialization callback.
 *
 * Kernel-level initialization wrapper. Initializes and starts
 * PWM generation using global PWM object.
 */
void cbPWM(void)
{
    vPWM_Init(&pwm, dPWM_FREQ_16KHZ);
    vPWM_Start(&pwm);
}

/* =========================================================
 * PHASE ENABLE / DISABLE
 * ========================================================= */

/**
 * @brief Enables Phase A output (CH1 + CH1N).
 */
void vPWM_EnablePhaseA(PWM_t *self)
{
    TIM1->CCER |= TIM_CCER_CC1E;
}

/**
 * @brief Enables Phase B output (CH2 + CH2N).
 */
void vPWM_EnablePhaseB(PWM_t *self)
{
    TIM1->CCER |= TIM_CCER_CC2E;
}

/**
 * @brief Enables Phase C output (CH3 + CH3N).
 */
void vPWM_EnablePhaseC(PWM_t *self)
{
    TIM1->CCER |= TIM_CCER_CC3E;
}

/**
 * @brief Disables Phase A output.
 */
void vPWM_DisablePhaseA(PWM_t *self)
{
    TIM1->CCER &= ~TIM_CCER_CC1E;
}

/**
 * @brief Disables Phase B output.
 */
void vPWM_DisablePhaseB(PWM_t *self)
{
    TIM1->CCER &= ~TIM_CCER_CC2E;
}

/**
 * @brief Disables Phase C output.
 */
void vPWM_DisablePhaseC(PWM_t *self)
{
    TIM1->CCER &= ~TIM_CCER_CC3E;
}