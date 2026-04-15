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
#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
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
/* =========================================================
 * PWM OBJECT
 * ========================================================= */
typedef struct
{
    uint32_t arr;

    /* internal state (optional future use) */
    uint8_t enabled;
} PWM_t;

/* =========================================================
 * CONSTRUCTOR
 * ========================================================= */
void vPWM_Init(PWM_t *self, uint32_t arr);
void vPWM_Start(PWM_t *self);

/* =========================================================
 * METHODS
 * ========================================================= */
void vPWM_SetPhaseA(PWM_t *self, uint32_t duty);
void vPWM_SetPhaseB(PWM_t *self, uint32_t duty);
void vPWM_SetPhaseC(PWM_t *self, uint32_t duty);

void vPWM_SetPhases(PWM_t *self,
                   uint32_t a,
                   uint32_t b,
                   uint32_t c);

/* =========================================================
 * PHASE CONTROL (ON/OFF)
 * ========================================================= */
void vPWM_EnablePhaseA(PWM_t *self);
void vPWM_EnablePhaseB(PWM_t *self);
void vPWM_EnablePhaseC(PWM_t *self);

void vPWM_DisablePhaseA(PWM_t *self);
void vPWM_DisablePhaseB(PWM_t *self);
void vPWM_DisablePhaseC(PWM_t *self);

#ifdef __cplusplus
}
#endif

#endif /* PWM_H */