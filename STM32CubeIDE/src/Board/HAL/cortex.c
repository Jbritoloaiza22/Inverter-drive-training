/**
 * @file cortex.c
 * @brief Cortex-M NVIC and SysTick abstraction layer.
 *
 * This module provides a wrapper interface for configuring and controlling
 * Cortex-M core features such as:
 * - NVIC interrupt priority
 * - Interrupt enable/disable
 * - System reset
 * - SysTick timer configuration
 *
 * It abstracts direct CMSIS calls to maintain portability and consistency
 * within the kernel architecture.
 *
 * Responsibilities:
 * - Encapsulate NVIC configuration
 * - Provide a clean API for interrupt management
 * - Configure system tick timer
 *
 * @note
 * These functions are thin wrappers over CMSIS core functions.
 *
 * @warning
 * Incorrect priority configuration may lead to interrupt starvation
 * or unexpected system behavior.
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

#include "stm32g0xx_hal.h"

/* =========================================================
 * NVIC CONFIGURATION
 * ========================================================= */

/**
 * @brief Set interrupt priority.
 *
 * Configures the priority of a given interrupt in the NVIC.
 *
 * @param[in] IRQn Interrupt number (IRQn_Type)
 * @param[in] PreemptPriority Preemption priority level
 * @param[in] SubPriority Subpriority level (not used in Cortex-M0+)
 *
 * @note
 * On Cortex-M0+, only preemption priority is supported.
 * SubPriority parameter is ignored.
 */
void vCORTEX_NVICSetPriority(IRQn_Type IRQn,
                            uint32_t PreemptPriority,
                            uint32_t SubPriority)
{
    (void)SubPriority; /* Not used in Cortex-M0+ */
    NVIC_SetPriority(IRQn, PreemptPriority);
}

/**
 * @brief Enable interrupt in NVIC.
 *
 * Allows the specified interrupt to be serviced.
 *
 * @param[in] IRQn Interrupt number
 */
void vCORTEX_NVICEnableIRQ(IRQn_Type IRQn)
{
    NVIC_EnableIRQ(IRQn);
}

/**
 * @brief Disable interrupt in NVIC.
 *
 * Prevents the specified interrupt from being serviced.
 *
 * @param[in] IRQn Interrupt number
 */
void vCORTEX_NVICDisableIRQ(IRQn_Type IRQn)
{
    NVIC_DisableIRQ(IRQn);
}

/* =========================================================
 * SYSTEM CONTROL
 * ========================================================= */

/**
 * @brief Perform a system reset.
 *
 * Triggers a software reset of the microcontroller.
 *
 * @note
 * This function does not return.
 */
void vCORTEX_NVICSystemReset(void)
{
    NVIC_SystemReset();
}

/* =========================================================
 * SYSTICK CONFIGURATION
 * ========================================================= */

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
 * Typically used to generate a 1 ms system tick:
 * @code
 * vCORTEX_SYSTICKConfig(SystemCoreClock / 1000U);
 * @endcode
 */
uint32_t vCORTEX_SYSTICKConfig(uint32_t TicksNumb)
{
    return SysTick_Config(TicksNumb);
}