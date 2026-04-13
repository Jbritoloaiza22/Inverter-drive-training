/**
 * @file tim.h
 * @brief Timer driver interface for TIM2 and TIM3.
 *
 * This module defines the configuration parameters and public
 * interface functions used to control TIM2 and TIM3 peripherals
 * of the STM32G031 microcontroller.
 *
 * The timers are configured as basic time-base generators that
 * produce periodic update interrupts for application tasks.
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

#ifndef __TIM_H
#define __TIM_H

#include "stm32g0xx_hal.h"

/* =========================================================
 * TIMER OBJECT
 * ========================================================= */

typedef struct
{
    TIM_TypeDef *instance;   /**< TIM peripheral base address */
    uint32_t psc;            /**< Prescaler value */
    uint32_t arr;            /**< Auto-reload value */
    uint8_t enabled;        /**< Runtime state */
} Timer_t;

/* =========================================================
 * API
 * ========================================================= */

void Timer_Init(Timer_t *self, TIM_TypeDef *instance,
                uint32_t psc, uint32_t arr);

void Timer_Start(Timer_t *self);
void Timer_Stop(Timer_t *self);

void Timer_ClearIRQ(Timer_t *self);

/* Callback style (optional kernel hook) */
void cbTIM(void);

#endif