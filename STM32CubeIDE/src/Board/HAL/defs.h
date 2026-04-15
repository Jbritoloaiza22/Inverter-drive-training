/**
 * @file defs.h
 * @brief Global definitions and core HAL interface configuration.
 *
 * This header provides:
 * - Global constants and oscillator definitions
 * - HAL tick configuration
 * - Core HAL function prototypes
 * - Assertion handling interface
 *
 * It centralizes low-level system definitions required by:
 * - HAL drivers
 * - Kernel layer
 * - Peripheral modules
 *
 * @note
 * This file acts as a bridge between CMSIS/HAL and the custom
 * abstraction layers (CORTEX, Kernel, Drivers).
 *
 * @warning
 * Modifying oscillator values incorrectly may break timing,
 * delays, and peripheral configurations.
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

#ifndef DEFS_H
#define DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================
 * INCLUDES
 * ========================================================= */

/**
 * @brief HAL ADC driver headers.
 */
#include "stm32g0xx_hal_adc.h"
#include "stm32g0xx_hal_adc_ex.h"

/**
 * @brief HAL UART driver header.
 */
#include "stm32g0xx_hal_uart.h"

/**
 * @brief Cortex abstraction layer.
 */
#include "cortex.h"

/* =========================================================
 * SYSTEM CONSTANTS
 * ========================================================= */

/**
 * @brief SysTick interrupt priority.
 */
#define TICK_INT_PRIORITY 3U

/**
 * @brief Internal high-speed oscillator frequency (HSI).
 *
 * Default value for STM32G0 series.
 */
#define HSI_VALUE (16000000UL)

/**
 * @brief External low-speed oscillator frequency (LSE).
 */
#define LSE_VALUE (32768UL)

/* =========================================================
 * ASSERT HANDLING
 * ========================================================= */

/**
 * @brief Assertion failure handler.
 *
 * Called when an assert_param macro fails.
 *
 * @param[in] file Pointer to source file name
 * @param[in] line Line number where the assertion failed
 *
 * @note Typically used for debugging purposes.
 */
void assert_failed(uint8_t *file, uint32_t line);

/* =========================================================
 * HAL TICK CONFIGURATION
 * ========================================================= */

/**
 * @brief HAL tick frequency enumeration.
 *
 * Defines the frequency of the system tick used by HAL.
 */
typedef enum
{
  HAL_TICK_FREQ_10HZ    = 100U, /**< Tick every 100 ms */
  HAL_TICK_FREQ_100HZ   = 10U,  /**< Tick every 10 ms */
  HAL_TICK_FREQ_1KHZ    = 1U,   /**< Tick every 1 ms */
  HAL_TICK_FREQ_DEFAULT = HAL_TICK_FREQ_1KHZ /**< Default: 1 ms */
} HAL_TickFreqTypeDef;

/* =========================================================
 * HAL CORE API
 * ========================================================= */

/**
 * @brief Initialize HAL library.
 *
 * Configures the Flash prefetch, instruction cache,
 * and initializes the SysTick.
 *
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_Init(void);

/**
 * @brief Initialize HAL tick.
 *
 * Configures the system tick timer with the given priority.
 *
 * @param[in] TickPriority SysTick interrupt priority
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);

/**
 * @brief Increment HAL tick counter.
 *
 * Called inside SysTick interrupt handler.
 */
void HAL_IncTick(void);

/**
 * @brief Get current HAL tick value.
 *
 * @return Current tick count (in milliseconds)
 */
uint32_t HAL_GetTick(void);

#ifdef __cplusplus
}
#endif

#endif /* DEFS_H */