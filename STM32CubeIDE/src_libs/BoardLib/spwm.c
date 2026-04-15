/**
 * @file spwm.c
 * @brief Sinusoidal PWM (SPWM) implementation for three-phase motor control.
 *
 * This module implements a basic Sinusoidal Pulse Width Modulation (SPWM)
 * strategy for driving a three-phase inverter used in PMSM or BLDC motor control.
 *
 * The algorithm generates three sinusoidal reference signals (Va, Vb, Vc)
 * that are phase-shifted by 120 degrees. These signals are then scaled using
 * a modulation index and converted into duty cycles for a hardware timer
 * (typically TIM1) to generate PWM signals for power stage switching.
 *
 * This implementation is intended for educational purposes and open-loop
 * motor control experiments. It does not include current control loops,
 * sensor feedback, or space vector optimization (SVPWM).
 *
 * Key characteristics:
 * - Pure sinusoidal generation (no sector decomposition)
 * - 3-phase balanced waveform generation
 * - Simple amplitude modulation (modulation index)
 * - Direct conversion to PWM duty cycles (0–ARR range)
 * - Suitable for open-loop motor spin testing
 *
 * Typical usage:
 * - Open-loop PMSM/BLDC motor startup
 * - Learning PWM modulation concepts
 * - Base stage before SVPWM or FOC implementation
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

#include "spwm.h"
#include "pwm.h"
#include "stm32g031xx.h"
#include "KernelInterface.h"
#include <math.h>

/* =========================================================
 * PRIVATE DATA
 * ========================================================= */

/**
 * @brief Sine lookup table.
 *
 * Stores precomputed sine values in the range [-1, 1].
 */
static float sin_table[dSPWM_TABLE_SIZE];

/**
 * @brief Global SPWM instance.
 *
 * Used by kernel callback (cbSPWM).
 */
SPWM_t spwm;

/**
 * @brief External PWM object reference.
 */
extern PWM_t pwm;

/* =========================================================
 * PRIVATE FUNCTIONS
 * ========================================================= */

/**
 * @brief Normalize angle to the range [0, 2π).
 *
 * @param angle Input angle in radians
 * @return Normalized angle
 */
static float fSPWM_NormalizeAngle(float angle)
{
    while (angle < 0.0f) angle += 2.0f * dSPWM_PI;
    while (angle >= 2.0f * dSPWM_PI) angle -= 2.0f * dSPWM_PI;
    return angle;
}

/* =========================================================
 * PUBLIC FUNCTIONS
 * ========================================================= */

/**
 * @brief Initialize sine lookup table.
 *
 * Precomputes sine values to improve runtime performance.
 *
 * @note Must be called before using fSPWM_Sine().
 */
void vSPWM_TableInit(void)
{
    for (uint32_t i = 0; i < dSPWM_TABLE_SIZE; i++)
    {
        sin_table[i] = sinf((2.0f * dSPWM_PI * i) / dSPWM_TABLE_SIZE);
    }
}

/**
 * @brief Get sine value using lookup table.
 *
 * @param angle Angle in radians
 * @return Sine value in range [-1, 1]
 */
float fSPWM_Sine(float angle)
{
    angle = fSPWM_NormalizeAngle(angle);

    uint32_t index = (uint32_t)(angle * (dSPWM_TABLE_SIZE / (2.0f * dSPWM_PI)));
    return sin_table[index];
}

/**
 * @brief Initialize SPWM object.
 *
 * Configures the internal state of the SPWM generator.
 *
 * @param[in,out] self Pointer to SPWM object
 * @param[in] step Angle increment per update (controls frequency)
 * @param[in] arr Timer auto-reload value (PWM resolution)
 *
 * @note Also initializes the sine lookup table.
 */
void vSPWM_Init(SPWM_t *self, float step, uint32_t arr)
{
    if (self == 0) return;

    self->theta = 0.0f;
    self->step = step;
    self->arr = arr;
    self->initialized = 1U;

    vSPWM_TableInit();
}

/**
 * @brief Update SPWM output.
 *
 * Generates three-phase sinusoidal signals and updates PWM duty cycles.
 *
 * Steps:
 * 1. Advance electrical angle
 * 2. Generate 3-phase sine signals (120° shifted)
 * 3. Normalize to PWM duty range (0..ARR)
 * 4. Apply to PWM driver
 *
 * @param[in,out] self Pointer to SPWM object
 *
 * @note Typically called periodically from a timer ISR.
 */
void vSPWM_Update(SPWM_t *self)
{
    if ((self == 0) || (self->initialized == 0U)) return;

    float phase_u, phase_v, phase_w;
    float duty_u, duty_v, duty_w;

    /* Advance electrical angle */
    self->theta += self->step;
    if (self->theta >= 2.0f * dSPWM_PI)
    {
        self->theta -= 2.0f * dSPWM_PI;
    }

    /* Generate 3-phase sinusoidal signals */
    phase_u = fSPWM_Sine(self->theta);
    phase_v = fSPWM_Sine(self->theta - 2.0f * dSPWM_PI / 3.0f);
    phase_w = fSPWM_Sine(self->theta + 2.0f * dSPWM_PI / 3.0f);

    /* Convert to PWM duty cycles */
    duty_u = ((phase_u + 1.0f) * 0.5f) * self->arr;
    duty_v = ((phase_v + 1.0f) * 0.5f) * self->arr;
    duty_w = ((phase_w + 1.0f) * 0.5f) * self->arr;

    /* Clamp to valid range */
    if (duty_u > self->arr) duty_u = self->arr;
    if (duty_v > self->arr) duty_v = self->arr;
    if (duty_w > self->arr) duty_w = self->arr;

    /* Apply duty cycles to PWM hardware */
    vPWM_SetPhaseA(&pwm, (uint32_t)duty_u);
    vPWM_SetPhaseB(&pwm, (uint32_t)duty_v);
    vPWM_SetPhaseC(&pwm, (uint32_t)duty_w);
}

/* =========================================================
 * CALLBACK (KERNEL)
 * ========================================================= */

/**
 * @brief SPWM initialization callback.
 *
 * Initializes the global SPWM instance with default parameters.
 *
 * Configuration:
 * - Step: 0.06 rad/update (defines output frequency)
 * - ARR:  TIM1 auto-reload value (PWM resolution)
 *
 * @note Typically called during system startup by the kernel.
 */
void cbSPWM(void)
{
    vSPWM_Init(&spwm, 0.06f, (uint32_t)TIM1->ARR);
}