/**
 * @file kernel_irq.c
 * @brief Cortex-M interrupt handlers and peripheral IRQ interface.
 *
 * This module defines the core exception handlers and peripheral
 * interrupt service routines (ISR) used in the system.
 *
 * It acts as the bridge between:
 * - Low-level hardware interrupts
 * - HAL drivers (e.g., ADC)
 * - Kernel/application-level callbacks
 *
 * Handlers included:
 * - Core exceptions (NMI, HardFault, SVC, PendSV, SysTick)
 * - Peripheral interrupts (ADC)
 *
 * @note
 * - HardFault and NMI handlers are implemented as infinite loops
 *   for debugging purposes.
 * - SysTick is used as the system time base.
 *
 * @warning
 * Do not place heavy processing inside ISRs. Keep them short and
 * delegate work to the kernel/application layer when possible.
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

#include "kernel.h"
#include "gpio.h"
#include "tim.h"

/**
 * @brief External ADC handle (HAL driver).
 */
extern ADC_HandleTypeDef hadc1;

/* =========================================================
 * CORE EXCEPTION HANDLERS
 * ========================================================= */

/**
 * @brief Non-Maskable Interrupt (NMI) handler.
 *
 * This interrupt is triggered by critical hardware faults
 * such as clock failure.
 *
 * @note Enters infinite loop for debugging.
 */
void vIRQ_NMIHandler(void)
{
    while (1)
    {
        /* Trap CPU for debugging */
    }
}

/**
 * @brief Hard Fault handler.
 *
 * Triggered when a severe fault occurs (e.g., invalid memory access,
 * division by zero, or corrupted stack).
 *
 * @note Enters infinite loop for debugging.
 */
void vIRQ_HardFaultHandler(void)
{
    while (1)
    {
        /* Trap CPU for debugging */
    }
}

/**
 * @brief Supervisor Call (SVC) handler.
 *
 * Used for system service calls from user code.
 *
 * @note Currently not used.
 */
void vIRQ_SVCHandler(void)
{
    /* No implementation */
}

/**
 * @brief PendSV handler.
 *
 * Typically used for context switching in RTOS systems.
 *
 * @note Currently not used.
 */
void vIRQ_PendSVHandler(void)
{
    /* No implementation */
}

/**
 * @brief SysTick interrupt handler.
 *
 * This function is called periodically based on the SysTick timer.
 *
 * Responsibilities:
 * - Increment HAL tick (time base)
 * - Execute debug or timing-related hooks
 *
 * @note Usually configured at 1 ms interval.
 */
void vIRQ_SysTickHandler(void)
{
    incCountertopwmDebug();  /**< Custom debug counter */
    HAL_IncTick();           /**< HAL time base increment */
}

/* =========================================================
 * PERIPHERAL INTERRUPT HANDLERS
 * ========================================================= */

/**
 * @brief ADC1 interrupt handler.
 *
 * Handles ADC conversion complete and error interrupts.
 *
 * Delegates processing to the HAL ADC driver.
 *
 * @note Must be linked to ADC1 IRQ in vector table.
 */
void vIRQ_ADC1IRQHandler(void)
{
    HAL_ADC_IRQHandler(&hadc1);
}