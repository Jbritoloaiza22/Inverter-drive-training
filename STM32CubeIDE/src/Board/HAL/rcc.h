/**
 * @file rcc.h
 * @brief RCC register bitfield macros for STM32G031.
 *
 * This header file defines macros and declarations used for configuring
 * the Reset and Clock Control (RCC) peripheral of the STM32G031
 * microcontroller. It provides convenient access to register bitfields
 * and configuration utilities required for enabling and managing
 * peripheral clocks within the system.
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

#ifndef __RCC_H
#define __RCC_H

#include "stm32g031xx.h"
#include <stdint.h>

/* =========================================================
 * GENERAL MACROS
 * ========================================================= */

/**
 * @brief Logical ON value.
 */
#define dOn  1U

/**
 * @brief Logical OFF value.
 */
#define dOff 0U

/* =========================================================
 * RCC OBJECT
 * ========================================================= */

/**
 * @brief RCC object structure.
 *
 * This structure represents the RCC module instance.
 * It stores the internal state of the RCC driver.
 *
 * @note This is a lightweight abstraction since hardware
 *       registers are globally accessible.
 */
typedef struct
{
    /**
     * @brief Initialization flag.
     *
     * Indicates whether the RCC has been successfully initialized.
     * - 0: Not initialized
     * - 1: Initialized
     */
    uint8_t initialized;

} RCC_t;

/* =========================================================
 * PUBLIC METHODS
 * ========================================================= */

/**
 * @brief Initialize RCC system.
 *
 * This function performs full RCC configuration including:
 * - Oscillator setup (HSE, PLL)
 * - System clock configuration
 * - Peripheral clock enabling
 *
 * @param[in,out] self Pointer to RCC object instance
 */
void vRCC_Init(RCC_t *self);

/**
 * @brief Enable peripheral clocks.
 *
 * Enables required peripheral clocks such as:
 * - GPIO ports
 * - Timers (TIM1, TIM2, TIM3)
 * - USART
 * - ADC
 *
 * @param[in] self Pointer to RCC object instance
 */
void vRCC_EnablePeripherals(RCC_t *self);

/**
 * @brief RCC initialization callback.
 *
 * This function is intended to be used by the KernelInterface
 * as part of the system initialization sequence.
 *
 * It internally initializes the RCC object and configures
 * all system clocks.
 */
void cbRCC(void);

#endif /* __RCC_H */