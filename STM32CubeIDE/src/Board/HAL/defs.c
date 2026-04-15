/**
 * @file hal.c
 * @brief Minimal HAL core implementation (tick and initialization).
 *
 * This module provides a lightweight implementation of essential HAL
 * functions required for system initialization and time base management.
 *
 * Features:
 * - SysTick-based time base
 * - Tick increment and retrieval
 * - NVIC priority configuration through Cortex abstraction
 *
 * This implementation is designed to:
 * - Replace or simplify the standard STM32 HAL
 * - Integrate with a custom kernel architecture
 *
 * @note
 * Functions are declared as __weak to allow user overrides.
 *
 * @warning
 * Incorrect SysTick configuration may affect delays, scheduling,
 * and time-dependent peripherals.
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

#include "defs.h"

/* =========================================================
 * GLOBAL VARIABLES
 * ========================================================= */

/**
 * @brief Global tick counter.
 *
 * Incremented periodically by SysTick interrupt.
 */
__IO uint32_t uwTick;

/**
 * @brief SysTick interrupt priority.
 *
 * Initialized with an invalid value.
 */
uint32_t uwTickPrio = (1UL << __NVIC_PRIO_BITS);

/**
 * @brief Tick frequency configuration.
 *
 * Default: 1 kHz (1 ms tick).
 */
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;

/* =========================================================
 * HAL CORE FUNCTIONS
 * ========================================================= */

/**
 * @brief Initialize HAL library.
 *
 * Configures the system tick timer and sets interrupt priority.
 *
 * @retval HAL_OK Initialization successful
 * @retval HAL_ERROR Initialization failed
 */
HAL_StatusTypeDef HAL_Init(void)
{
    HAL_StatusTypeDef status = HAL_OK;

    if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Additional initialization can be added here */
    }

    return status;
}

/**
 * @brief Initialize SysTick time base.
 *
 * Configures the SysTick timer based on the selected tick frequency
 * and sets its interrupt priority.
 *
 * @param[in] TickPriority SysTick interrupt priority
 *
 * @retval HAL_OK Configuration successful
 * @retval HAL_ERROR Configuration failed
 *
 * @note
 * This function is declared as __weak and can be overridden by the user.
 */
__weak HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
    HAL_StatusTypeDef status = HAL_OK;

    if ((uint32_t)uwTickFreq != 0U)
    {
        if (vCORTEX_SYSTICKConfig(SystemCoreClock / (1000U / (uint32_t)uwTickFreq)) == 0U)
        {
            if (TickPriority < (1UL << __NVIC_PRIO_BITS))
            {
                vCORTEX_NVICSetPriority(SysTick_IRQn, TickPriority, 0U);
                uwTickPrio = TickPriority;
            }
            else
            {
                status = HAL_ERROR;
            }
        }
        else
        {
            status = HAL_ERROR;
        }
    }
    else
    {
        status = HAL_ERROR;
    }

    return status;
}

/**
 * @brief Increment HAL tick counter.
 *
 * This function is called inside the SysTick interrupt handler.
 *
 * @note
 * Declared as __weak to allow user customization.
 */
__weak void HAL_IncTick(void)
{
    uwTick += (uint32_t)uwTickFreq;
}

/**
 * @brief Get current HAL tick value.
 *
 * @return Current tick count in milliseconds (or configured unit)
 *
 * @note
 * Declared as __weak to allow user customization.
 */
__weak uint32_t HAL_GetTick(void)
{
    return uwTick;
}