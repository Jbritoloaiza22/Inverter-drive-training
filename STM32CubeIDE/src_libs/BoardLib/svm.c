/**
 * @file svm.c
 * @brief Space Vector Modulation (SVM) implementation.
 *
 * This module implements a simplified Space Vector Modulation (SVM)
 * algorithm using an object-oriented approach in C.
 *
 * Features:
 * - Inverse Clarke transformation (αβ → abc)
 * - Offset-based normalization (centered PWM)
 * - Duty cycle generation for three-phase inverter
 *
 * @note This implementation does not include sector-based switching.
 *       It is intended for educational purposes and basic inverter control.
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

#include "svm.h"
#include "pwm.h"
#include "stm32g031xx.h"

/* =========================================================
 * PRIVATE DEFINES
 * ========================================================= */

/**
 * @brief Square root of 3 constant.
 *
 * Used in Clarke transformation calculations.
 */
#define dSQRT3 1.73205080757f

/* =========================================================
 * GLOBAL OBJECT
 * ========================================================= */

/**
 * @brief Global SVM instance.
 *
 * Used internally by the kernel callback.
 */
static SVM_t svm;

/* =========================================================
 * PRIVATE METHODS
 * ========================================================= */

/**
 * @brief Clamp value within [-1, 1].
 *
 * Ensures modulation inputs remain within valid range.
 *
 * @param x Input value
 * @return Clamped value
 */
static float vSVM_Clamp(float x)
{
    if (x > 1.0f) return 1.0f;
    if (x < -1.0f) return -1.0f;
    return x;
}

/**
 * @brief Convert αβ components to three-phase abc.
 *
 * Implements inverse Clarke transformation.
 *
 * @param alpha Alpha component
 * @param beta  Beta component
 * @param a     Output phase A
 * @param b     Output phase B
 * @param c     Output phase C
 */
static void vSVM_AlphaBetaToABC(float alpha, float beta,
                                float *a, float *b, float *c)
{
    *a = alpha;
    *b = -0.5f * alpha + (dSQRT3 * 0.5f) * beta;
    *c = -0.5f * alpha - (dSQRT3 * 0.5f) * beta;
}

/**
 * @brief Normalize phase voltages to PWM range [0,1].
 *
 * Applies offset injection to maximize DC bus utilization
 * and centers the waveform before scaling.
 *
 * @param a Phase A (input/output)
 * @param b Phase B (input/output)
 * @param c Phase C (input/output)
 */
static void vSVM_Normalize(float *a, float *b, float *c)
{
    float vmax = *a;
    float vmin = *a;

    if (*b > vmax) vmax = *b;
    if (*c > vmax) vmax = *c;

    if (*b < vmin) vmin = *b;
    if (*c < vmin) vmin = *c;

    float offset = (vmax + vmin) * 0.5f;

    /* Center signals */
    *a -= offset;
    *b -= offset;
    *c -= offset;

    /* Scale to 0..1 */
    *a = (*a + 1.0f) * 0.5f;
    *b = (*b + 1.0f) * 0.5f;
    *c = (*c + 1.0f) * 0.5f;

    /* Clamp again for safety */
    *a = vSVM_Clamp(*a);
    *b = vSVM_Clamp(*b);
    *c = vSVM_Clamp(*c);
}

/* =========================================================
 * PUBLIC METHODS
 * ========================================================= */

/**
 * @brief Initialize SVM object.
 *
 * Marks the SVM instance as initialized and ready for use.
 *
 * @param self Pointer to SVM object
 */
void vSVM_Init(SVM_t *self)
{
    if (self == 0) return;

    self->initialized = 1U;
}

/**
 * @brief Update SVM modulation output.
 *
 * This function:
 * 1. Clamps input voltages
 * 2. Transforms αβ → abc
 * 3. Normalizes signals to PWM range
 * 4. Converts to timer compare values
 * 5. Updates PWM hardware
 *
 * @param self   Pointer to SVM object
 * @param Valpha Alpha component (-1.0 to 1.0)
 * @param Vbeta  Beta component (-1.0 to 1.0)
 */
void vSVM_Update(SVM_t *self, float Valpha, float Vbeta)
{
    if ((self == 0) || (self->initialized == 0U)) return;

    float a, b, c;

    /* Clamp inputs */
    Valpha = vSVM_Clamp(Valpha);
    Vbeta  = vSVM_Clamp(Vbeta);

    /* αβ → abc */
    vSVM_AlphaBetaToABC(Valpha, Vbeta, &a, &b, &c);

    /* Normalize */
    vSVM_Normalize(&a, &b, &c);

    /* Convert to timer counts */
    uint32_t arr = TIM1->ARR;

    uint32_t dutyA = (uint32_t)(a * arr);
    uint32_t dutyB = (uint32_t)(b * arr);
    uint32_t dutyC = (uint32_t)(c * arr);

    /* Update PWM */
    vPWM_UpdatePhaseCompare(dutyA, dutyB, dutyC);
}

/* =========================================================
 * CALLBACK (KERNEL)
 * ========================================================= */

/**
 * @brief SVM initialization callback.
 *
 * This function is intended to be called by the Kernel layer
 * during system initialization.
 *
 * It initializes the global SVM instance.
 */
void cbSVM(void)
{
    vSVM_Init(&svm);
}