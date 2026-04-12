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

/**
 * @brief Prescaler value for TIM2.
 *
 * Defines the clock division applied to the timer input clock.
 */
#define TIM2_PRESCALER 63U

/**
 * @brief Auto-reload value for TIM2.
 *
 * Determines the timer overflow period and interrupt frequency.
 */
#define TIM2_ARR 249U

/**
 * @brief Prescaler value for TIM3.
 */
#define TIM3_PRESCALER 63U

/**
 * @brief Auto-reload value for TIM3.
 */
#define TIM3_ARR 999U

/**
 * @brief Initialize TIM2 peripheral.
 *
 * Configures TIM2 as a periodic timer generating update interrupts
 * based on the configured prescaler and auto-reload values.
 */
void vTIM2_Init(void);

/**
 * @brief Start TIM2 timer.
 *
 * Enables the TIM2 counter allowing it to begin counting
 * and generating periodic update events.
 */
void vTIM2_Start(void);

/**
 * @brief TIM2 interrupt service routine handler.
 *
 * This function processes the update interrupt generated
 * by TIM2 and clears the corresponding interrupt flag.
 */
void vTIM2_IRQHandler(void);

/**
 * @brief Initialize TIM3 peripheral.
 *
 * Configures TIM3 as a periodic timer generating update interrupts
 * according to the configured prescaler and auto-reload values.
 */
void vTIM3_Init(void);

/**
 * @brief Start TIM3 timer.
 *
 * Enables the TIM3 counter allowing it to begin counting
 * and generating periodic update events.
 */
void vTIM3_Start(void);

/**
 * @brief TIM3 interrupt service routine handler.
 *
 * This function handles the update interrupt generated
 * by TIM3 and clears the interrupt flag.
 */
void vTIM3_IRQHandler(void);
#endif /* __TIM_H */