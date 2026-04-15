/**
 * @file spwm.h
 * @brief Sinusoidal PWM (SPWM) generator for 3-phase inverter control.
 *
 * This module implements a basic Sinusoidal PWM (SPWM) algorithm for
 * three-phase motor control applications such as PMSM or BLDC drives.
 *
 * The implementation generates three sinusoidal reference signals
 * (Va, Vb, Vc) from an electrical angle and converts them into PWM
 * duty cycles for a hardware timer (e.g., TIM1).
 *
 * This is intended for educational purposes and open-loop motor control.
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

#ifndef SPWM_H
#define SPWM_H

#include <stdint.h>

/* =========================================================
 * CONFIGURATION
 * ========================================================= */

/**
 * @brief Sine table size.
 */
#define dSPWM_TABLE_SIZE 1024U

/**
 * @brief Pi constant.
 */
#define dSPWM_PI 3.14159265358979323846f

/* =========================================================
 * OBJECT
 * ========================================================= */

/**
 * @brief SPWM object structure.
 */
typedef struct
{
    float theta;          /**< Electrical angle (rad) */
    float step;           /**< Angle increment per update */
    uint32_t arr;            /**< PWM period (timer ARR) */
    uint8_t initialized;  /**< Initialization flag */

} SPWM_t;

/* =========================================================
 * API
 * ========================================================= */

/**
 * @brief Initialize SPWM module.
 *
 * @param self Pointer to SPWM object
 * @param step Angle increment per update (speed control)
 * @param arr  PWM period (TIM ARR)
 */
void vSPWM_Init(SPWM_t *self, float step, uint32_t arr);

/**
 * @brief Update SPWM output.
 *
 * Generates 3-phase PWM signals.
 *
 * @param self Pointer to SPWM object
 */
void vSPWM_Update(SPWM_t *self);

/**
 * @brief Initialize sine lookup table.
 */
void vSPWM_TableInit(void);

/**
 * @brief Sine lookup function.
 *
 * @param angle Input angle in radians
 * @return Sine value
 */
float fSPWM_Sine(float angle);

#endif /* SPWM_H */
