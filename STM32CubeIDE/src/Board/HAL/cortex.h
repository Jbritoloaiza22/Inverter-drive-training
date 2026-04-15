/**
 * @file cortex.h
 * @brief Cortex-M NVIC and SysTick abstraction interface.
 *
 * This module defines the public API for configuring and controlling
 * Cortex-M core features such as interrupt management and system timing.
 *
 * It acts as a lightweight abstraction layer over CMSIS functions,
 * allowing better portability and integration within the system kernel.
 *
 * Features:
 * - NVIC interrupt priority configuration
 * - Interrupt enable/disable control
 * - System reset control
 * - SysTick timer configuration
 *
 * @note
 * This layer wraps CMSIS core functions (NVIC, SysTick).
 *
 * @warning
 * Incorrect usage of interrupt priorities may lead to unpredictable
 * system behavior or priority inversion issues.
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

#ifndef CORTEX_H
#define CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g0xx_hal_def.h"

/* =========================================================
 * SYSTICK CLOCK SOURCE DEFINITIONS
 * ========================================================= */

/**
 * @brief SysTick clock source: HCLK divided by 8.
 */
#define SYSTICK_CLKSOURCE_HCLK_DIV8       0x00000000U

/**
 * @brief SysTick clock source: HCLK.
 */
#define SYSTICK_CLKSOURCE_HCLK            0x00000004U

/* =========================================================
 * PUBLIC API
 * ========================================================= */

/**
 * @brief Set interrupt priority.
 *
 * Configures the priority level of the specified interrupt.
 *
 * @param[in] IRQn Interrupt number
 * @param[in] PreemptPriority Preemption priority level
 * @param[in] SubPriority Subpriority level (not used in Cortex-M0+)
 *
 * @note
 * Cortex-M0+ only supports preemption priority.
 * SubPriority parameter is ignored.
 */
void vCORTEX_NVICSetPriority(IRQn_Type IRQn,
                            uint32_t PreemptPriority,
                            uint32_t SubPriority);

/**
 * @brief Enable interrupt.
 *
 * Enables the specified interrupt in the NVIC.
 *
 * @param[in] IRQn Interrupt number
 */
void vCORTEX_NVICEnableIRQ(IRQn_Type IRQn);

/**
 * @brief Disable interrupt.
 *
 * Disables the specified interrupt in the NVIC.
 *
 * @param[in] IRQn Interrupt number
 */
void vCORTEX_NVICDisableIRQ(IRQn_Type IRQn);

/**
 * @brief Perform system reset.
 *
 * Triggers a software reset of the microcontroller.
 *
 * @note This function does not return.
 */
void vCORTEX_NVICSystemReset(void);

/**
 * @brief Configure SysTick timer.
 *
 * Initializes the SysTick timer to generate periodic interrupts.
 *
 * @param[in] TicksNumb Number of clock ticks between interrupts
 *
 * @return
 * - 0: Success
 * - 1: Failure (reload value out of range)
 *
 * @note
 * Typical configuration for 1 ms tick:
 * @code
 * vCORTEX_SYSTICKConfig(SystemCoreClock / 1000U);
 * @endcode
 */
uint32_t vCORTEX_SYSTICKConfig(uint32_t TicksNumb);

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_H */