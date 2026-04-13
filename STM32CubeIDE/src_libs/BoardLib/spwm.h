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

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================
 * INCLUDES
 * ========================================================= */
#include <stdint.h>

/* =========================================================
 * CONFIGURATION MACROS
 * ========================================================= */




#ifdef __cplusplus
}
#endif
#define dSINTABLESIZE 1024
#define dPI 3.14159265358979323846f

void vSPWM_TableSinInit(void);
float fSPWM_SineLookup(float angle);
#endif /* SPWM_H */

