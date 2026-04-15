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
#include <math.h>

/* External PWM handle */
extern PWM_t pwm;

/* =========================
 *  CONSTANTS (NO MAGIC NUMBERS)
 * ========================= */
#define dSVMINITIALCOUNTERLIMIT     (8000U)
#define dSVMPWMPERIOD                (1999U)
#define dSVMSTARTAMPLITUDE           (0.8f)
#define dSVMRUNAMPLITUDE             (0.8f)
#define dSVMFREQMAXHZ              (25.0f)
#define dSVMFREQSTEP                (0.02f)
#define dSVMSAMPLETIMESEC          (0.0000625f)
#define dSVMZEROFLOAT               (0.0f)
#define dSVMONEFLOAT                (1.0f)

/* Math constants (if not already in svm.h) */
#ifndef dTWOPI
#define dTWOPI (6.28318530718f)
#endif

/* =========================
 *  STATIC FUNCTION PROTOTYPES
 * ========================= */
static void vSVM_NormalizeAngleRad(float *theta);
static void vSVM_ComputeDutyCycles(float valpha, float vbeta, float vbus,
                                    uint32_t ui32pwmPeriod,
                                    uint32_t *pwm_u,
                                    uint32_t *pwm_v,
                                    uint32_t *pwm_w);

static uint8_t u8SVM_GetSector(float alpha, float beta);

static inline void vSVM_NormalizeAngleRad(float *theta)
{
    if (*theta >= dTWOPI)
    {
        *theta -= dTWOPI;
    }
    else
    {
        /* MISRA-friendly structure */
    }

    if (*theta < dSVMZEROFLOAT)
    {
        *theta += dTWOPI;
    }
    else
    {
        /* MISRA-friendly structure */
    }
}


static void vSVM_ComputeDutyCycles(float valpha, float vbeta, float vbus,
                                   uint32_t ui32pwmPeriod,
                                   uint32_t *pwm_u,
                                   uint32_t *pwm_v,
                                   uint32_t *pwm_w)
{
    int32_t i32t1;
    int32_t i32t2;

    float alpha = valpha / vbus;
    float beta  = vbeta  / vbus;

    uint8_t sector = u8SVM_GetSector(alpha, beta);

    switch (sector)
    {
        case 1U:
            i32t1 = (int32_t)((alpha - dONE_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            i32t2 = (int32_t)((dTWO_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            *pwm_u = (ui32pwmPeriod + (uint32_t)i32t1 + (uint32_t)i32t2) / 2U;
            *pwm_v = *pwm_u - (uint32_t)i32t1;
            *pwm_w = *pwm_v - (uint32_t)i32t2;
            break;

        case 2U:
            i32t1 = (int32_t)((alpha + dONE_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            i32t2 = (int32_t)((-alpha + dONE_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            *pwm_v = (ui32pwmPeriod + (uint32_t)i32t1 + (uint32_t)i32t2) / 2U;
            *pwm_u = *pwm_v - (uint32_t)i32t2;
            *pwm_w = *pwm_u - (uint32_t)i32t1;
            break;

        case 3U:
            i32t1 = (int32_t)((dTWO_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            i32t2 = (int32_t)((-alpha - dONE_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            *pwm_v = (ui32pwmPeriod + (uint32_t)i32t1 + (uint32_t)i32t2) / 2U;
            *pwm_w = *pwm_v - (uint32_t)i32t1;
            *pwm_u = *pwm_w - (uint32_t)i32t2;
            break;

        case 4U:
            i32t1 = (int32_t)((-alpha + dONE_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            i32t2 = (int32_t)((-dTWO_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            *pwm_w = (ui32pwmPeriod + (uint32_t)i32t1 + (uint32_t)i32t2) / 2U;
            *pwm_v = *pwm_w - (uint32_t)i32t2;
            *pwm_u = *pwm_v - (uint32_t)i32t1;
            break;

        case 5U:
            i32t1 = (int32_t)((-alpha - dONE_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            i32t2 = (int32_t)((alpha - dONE_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            *pwm_w = (ui32pwmPeriod + (uint32_t)i32t1 + (uint32_t)i32t2) / 2U;
            *pwm_u = *pwm_w - (uint32_t)i32t1;
            *pwm_v = *pwm_u - (uint32_t)i32t2;
            break;

        case 6U:
            i32t1 = (int32_t)((-dTWO_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            i32t2 = (int32_t)((alpha + dONE_BY_SQRT3 * beta) * (float)ui32pwmPeriod);
            *pwm_u = (ui32pwmPeriod + (uint32_t)i32t1 + (uint32_t)i32t2) / 2U;
            *pwm_w = *pwm_u - (uint32_t)i32t2;
            *pwm_v = *pwm_w - (uint32_t)i32t1;
            break;

        default:
            *pwm_u = (ui32pwmPeriod / 2U);
            *pwm_v = (ui32pwmPeriod / 2U);
            *pwm_w = (ui32pwmPeriod / 2U);
            break;
    }

    if (*pwm_u > ui32pwmPeriod) 
    {
        *pwm_u = ui32pwmPeriod;
    }
    else
    {
        /* MISRA-friendly structure */
    }
    if (*pwm_v > ui32pwmPeriod) 
    {
        *pwm_v = ui32pwmPeriod;
    }
    else
    {
        /* MISRA-friendly structure */
    }
    if (*pwm_w > ui32pwmPeriod) 
    {
        *pwm_w = ui32pwmPeriod;
    }
    else
    {
        /* MISRA-friendly structure */
    }
}

static uint8_t u8SVM_GetSector(float alpha, float beta)
{
    uint8_t sector = 0U;

    if (beta >= dSVMZEROFLOAT)
    {
        if (alpha >= dSVMZEROFLOAT)
        {
            sector = ((dONE_BY_SQRT3 * beta) > alpha) ? 2U : 1U;
        }
        else
        {
            sector = ((-dONE_BY_SQRT3 * beta) > alpha) ? 3U : 2U;
        }
    }
    else
    {
        if (alpha >= dSVMZEROFLOAT)
        {
            sector = ((-dONE_BY_SQRT3 * beta) > alpha) ? 5U : 6U;
        }
        else
        {
            sector = ((dONE_BY_SQRT3 * beta) > alpha) ? 4U : 5U;
        }
    }

    return sector;
}


void vSVM_PeriodElapsedCallback(void)
{
    static float theta = dSVMZEROFLOAT;
    static float freq  = dSVMZEROFLOAT;
    static uint32_t ui32counter = 0U;

    uint32_t ui32dutyA;
    uint32_t ui32dutyB;
    uint32_t ui32dutyC;

    float Valpha;
    float Vbeta;

    if (ui32counter < dSVMINITIALCOUNTERLIMIT)
    {
        Valpha = dSVMSTARTAMPLITUDE;
        Vbeta  = dSVMZEROFLOAT;
    }
    else
    {
        freq += dSVMFREQSTEP;

        if (freq > dSVMFREQMAXHZ)
        {
            freq = dSVMFREQMAXHZ;
        }
        else
        {
            /* MISRA-friendly structure */
        }

        theta += dTWOPI * freq * dSVMSAMPLETIMESEC;
        vSVM_NormalizeAngleRad(&theta);

        Valpha = dSVMRUNAMPLITUDE * cosf(theta);
        Vbeta  = dSVMRUNAMPLITUDE * sinf(theta);
    }

    ui32counter++;

    vSVM_ComputeDutyCycles(Valpha, Vbeta, dSVMONEFLOAT,
                           dSVMPWMPERIOD,
                           &ui32dutyA,
                           &ui32dutyB,
                           &ui32dutyC);

    vPWM_SetPhaseA(&pwm, ui32dutyA);
    vPWM_SetPhaseB(&pwm, ui32dutyB);
    vPWM_SetPhaseC(&pwm, ui32dutyC);
}