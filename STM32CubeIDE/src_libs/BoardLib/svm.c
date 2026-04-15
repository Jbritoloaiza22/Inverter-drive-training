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
#include "math.h"

extern PWM_t pwm;


static void vSVM_NormalizeAngleRad(float *theta);
static void vSVM_ComputeDutyCycles(float valpha, float vbeta, float vbus, uint32_t ui32pwmPeriod,
			uint32_t *pwm_u, uint32_t *pwm_v, uint32_t *pwm_w);
static uint8_t u8SVM_GetSector(float alpha, float beta);

static inline void vSVM_NormalizeAngleRad(float *theta)
{
    if (*theta >= dTWOPI) *theta -= dTWOPI;
    if (*theta < 0.0f)    *theta += dTWOPI;
}


static void vSVM_ComputeDutyCycles(float valpha, float vbeta, float vbus, uint32_t ui32pwmPeriod,
           uint32_t *pwm_u, uint32_t *pwm_v, uint32_t *pwm_w)
{
    int32_t i32t1;
	int32_t i32t2;
    float alpha = valpha / vbus;
    float beta  = vbeta  / vbus;

    uint8_t sector = u8SVM_GetSector(alpha, beta);
    switch(sector)
    {
        case 1:
            i32t1 = (alpha - dONE_BY_SQRT3 * beta) * ui32pwmPeriod;
            i32t2 = (dTWO_BY_SQRT3 * beta) * ui32pwmPeriod;
            *pwm_u = (ui32pwmPeriod + i32t1 + i32t2) / 2;
            *pwm_v = *pwm_u - i32t1;
            *pwm_w = *pwm_v - i32t2;
            break;

        case 2:
            i32t1 = (alpha + dONE_BY_SQRT3 * beta) * ui32pwmPeriod;
            i32t2 = (-alpha + dONE_BY_SQRT3 * beta) * ui32pwmPeriod;
            *pwm_v = (ui32pwmPeriod + i32t1 + i32t2) / 2;
            *pwm_u = *pwm_v - i32t2;
            *pwm_w = *pwm_u - i32t1;
            break;

        case 3:
            i32t1 = (dTWO_BY_SQRT3 * beta) * ui32pwmPeriod;
            i32t2 = (-alpha - dONE_BY_SQRT3 * beta) * ui32pwmPeriod;
            *pwm_v = (ui32pwmPeriod + i32t1 + i32t2) / 2;
            *pwm_w = *pwm_v - i32t1;
            *pwm_u = *pwm_w - i32t2;
            break;

        case 4:
            i32t1 = (-alpha + dONE_BY_SQRT3 * beta) * ui32pwmPeriod;
            i32t2 = (-dTWO_BY_SQRT3 * beta) * ui32pwmPeriod;
            *pwm_w = (ui32pwmPeriod + i32t1 + i32t2) / 2;
            *pwm_v = *pwm_w - i32t2;
            *pwm_u = *pwm_v - i32t1;
            break;

        case 5:
            i32t1 = (-alpha - dONE_BY_SQRT3 * beta) * ui32pwmPeriod;
            i32t2 = (alpha - dONE_BY_SQRT3 * beta) * ui32pwmPeriod;
            *pwm_w = (ui32pwmPeriod + i32t1 + i32t2) / 2;
            *pwm_u = *pwm_w - i32t1;
            *pwm_v = *pwm_u - i32t2;
            break;

        case 6:
            i32t1 = (-dTWO_BY_SQRT3 * beta) * ui32pwmPeriod;
            i32t2 = (alpha + dONE_BY_SQRT3 * beta) * ui32pwmPeriod;
            *pwm_u = (ui32pwmPeriod + i32t1 + i32t2) / 2;
            *pwm_w = *pwm_u - i32t2;
            *pwm_v = *pwm_w - i32t1;
            break;

        default:
            *pwm_u = ui32pwmPeriod / 2;
            *pwm_v = ui32pwmPeriod / 2;
            *pwm_w = ui32pwmPeriod / 2;
            break;
    }

    if (*pwm_u > ui32pwmPeriod) *pwm_u = ui32pwmPeriod;
    if (*pwm_v > ui32pwmPeriod) *pwm_v = ui32pwmPeriod;
    if (*pwm_w > ui32pwmPeriod) *pwm_w = ui32pwmPeriod;
}

static uint8_t u8SVM_GetSector(float alpha, float beta)
{
    uint8_t sector;

    if (beta >= 0.0f)
    {
        if (alpha >= 0.0f)
        {
            if ((dONE_BY_SQRT3 * beta) > alpha)
            {
                sector = 2U;
            }
            else
            {
                sector = 1U;
            }
        }
        else
        {
            if ((-dONE_BY_SQRT3 * beta) > alpha)
            {
                sector = 3U;
            }
            else
            {
                sector = 2U;
            }
        }
    }
    else
    {
        if (alpha >= 0.0f)
        {
            if ((-dONE_BY_SQRT3 * beta) > alpha)
            {
                sector = 5U;
            }
            else
            {
                sector = 6U;
            }
        }
        else
        {
            if ((dONE_BY_SQRT3 * beta) > alpha)
            {
                sector = 4U;
            }
            else
            {
                sector = 5U;
            }
        }
    }

    return (sector);
}


void vSVM_PeriodElapsedCallback(void)
{
    static float theta = 0.0f;
    static float freq = 0.0f;
    static uint32_t ui32counter = 0;
    uint32_t ui32dutyA;
    uint32_t ui32dutyB;
    uint32_t ui32dutyC;
    float Valpha;
    float Vbeta;

    const float Ts = 0.0000625f;

    if (ui32counter < 8000)
    {
        Valpha = 0.8f;
        Vbeta  = 0.0f;
    }
    else
    {

        freq += 0.02f;
        if (freq > 25.0f)
            freq = 25.0f;

        theta += dTWOPI * freq * Ts;
        vSVM_NormalizeAngleRad(&theta);

        float sin_t = sinf(theta);
        float cos_t = cosf(theta);

        float amplitude = 0.8f;

        Valpha = amplitude * cos_t;
        Vbeta  = amplitude * sin_t;
    }

    ui32counter++;

    vSVM_ComputeDutyCycles(Valpha, Vbeta, 1.0f, 1999,
          &ui32dutyA, &ui32dutyB, &ui32dutyC);

    vPWM_SetPhaseA(&pwm, ui32dutyA);
    vPWM_SetPhaseB(&pwm, ui32dutyB);
    vPWM_SetPhaseC(&pwm, ui32dutyC);
}
