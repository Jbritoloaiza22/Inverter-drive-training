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

#include "stm32g031xx.h"
#include <stdint.h>

/* =========================================================
 * TIMER OBJECT
 * ========================================================= */

/**
 * @brief Timer object structure.
 *
 * Represents a hardware timer instance and its configuration.
 *
 * @note This is a lightweight abstraction over STM32 TIM peripherals.
 */
typedef struct
{
    /**
     * @brief Pointer to hardware timer instance.
     *
     * Example:
     * - TIM2
     * - TIM3
     */
    TIM_TypeDef *instance;

    /**
     * @brief Prescaler value.
     *
     * Divides the input clock frequency.
     */
    uint32_t psc;

    /**
     * @brief Auto-reload value.
     *
     * Defines the timer period.
     */
    uint32_t arr;

    /**
     * @brief Runtime enable flag.
     *
     * - 0: Timer stopped
     * - 1: Timer running
     */
    uint8_t enabled;

} Timer_t;

/* =========================================================
 * PUBLIC API
 * ========================================================= */

/**
 * @brief Initialize timer instance.
 *
 * Configures the timer hardware and stores parameters
 * inside the Timer_t object.
 *
 * @param[in,out] self Pointer to Timer object
 * @param[in] instance Timer peripheral base (TIM2, TIM3, etc.)
 * @param[in] psc Prescaler value
 * @param[in] arr Auto-reload value (period)
 */
void vTimer_Init(Timer_t *self, TIM_TypeDef *instance,
                uint32_t psc, uint32_t arr);

/**
 * @brief Start timer.
 *
 * Enables the timer counter.
 *
 * @param[in,out] self Pointer to Timer object
 */
void vTimer_Start(Timer_t *self);

/**
 * @brief Stop timer.
 *
 * Disables the timer counter.
 *
 * @param[in,out] self Pointer to Timer object
 */
void vTimer_Stop(Timer_t *self);

/**
 * @brief Clear timer interrupt flag.
 *
 * Clears the update interrupt flag (UIF).
 * Should be called inside the ISR.
 *
 * @param[in,out] self Pointer to Timer object
 */
void vTimer_ClearIRQ(Timer_t *self);

/**
 * @brief Timer initialization callback.
 *
 * Intended for integration with the KernelInterface layer.
 * Initializes and starts system timers.
 */
void cbTIM(void);

#endif /* __TIM_H */