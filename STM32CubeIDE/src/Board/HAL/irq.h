/**
 * @file irq.h
 * @brief Interrupt handler interface for Cortex-M core and peripherals.
 *
 * This header declares the interrupt service routines (ISR) used by the system.
 * It includes both core exception handlers and peripheral interrupt handlers.
 *
 * These functions are typically mapped in the interrupt vector table and are
 * invoked automatically by the hardware when an interrupt occurs.
 *
 * Responsibilities:
 * - Handle core exceptions (NMI, HardFault, SysTick, etc.)
 * - Interface with HAL drivers (e.g., ADC)
 * - Provide hooks for kernel-level processing
 *
 * @note
 * Keep ISR implementations as short as possible and defer heavy processing
 * to the main loop or kernel scheduler.
 *
 * @warning
 * Incorrect ISR implementation may lead to system instability.
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

#ifndef __IRQ_H
#define __IRQ_H

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================
 * CORE EXCEPTION HANDLERS
 * ========================================================= */

/**
 * @brief Non-Maskable Interrupt (NMI) handler.
 *
 * Triggered by critical hardware faults such as clock failure.
 */
void vIRQ_NMIHandler(void);

/**
 * @brief Hard Fault handler.
 *
 * Handles severe system faults such as invalid memory access
 * or execution errors.
 */
void vIRQ_HardFaultHandler(void);

/**
 * @brief Supervisor Call (SVC) handler.
 *
 * Used for system service requests from software.
 */
void vIRQ_SVCHandler(void);

/**
 * @brief PendSV handler.
 *
 * Typically used for context switching in RTOS-based systems.
 */
void vIRQ_PendSVHandler(void);

/**
 * @brief SysTick handler.
 *
 * Periodic interrupt used as system time base.
 */
void vIRQ_SysTickHandler(void);

/* =========================================================
 * PERIPHERAL INTERRUPT HANDLERS
 * ========================================================= */

/**
 * @brief ADC1 interrupt handler.
 *
 * Handles ADC conversion complete and error events.
 */
void vIRQ_ADC1IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __IRQ_H */