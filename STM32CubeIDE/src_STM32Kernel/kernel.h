/**
 * @file kernel.h
 * @brief Core kernel definitions and common utilities.
 *
 * This header file defines core declarations used by the system kernel,
 * including common error handling mechanisms and shared interfaces
 * required across the application and hardware abstraction layers.
 *
 * It provides compatibility with both C and C++ environments and
 * includes essential HAL dependencies required by the kernel layer.
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

#ifndef __KERNEL_H
#define __KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "defs.h"

/**
 * @brief System error handler.
 *
 * This function is called when a critical error occurs within the system.
 * It typically disables interrupts and halts the system execution to
 * prevent undefined behavior.
 */
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

/**
 * @brief Execute the cooperative scheduler for periodic tasks.
 *
 * This function manages the main scheduler loop that executes periodic
 * tasks based on the time base flags. It coordinates task execution
 * at different intervals (1ms, 10ms, 20ms, 100ms, 1000ms) without
 * blocking execution.
 *
 * The scheduler is designed for cooperative multitasking where tasks
 * voluntarily yield control back to the main loop, allowing other
 * tasks to execute within their respective time slots.
 *
 * @note This function should be called repeatedly in the main loop
 * after system initialization.
 *
 * @see TimeBase_GetTick()
 * @see InterruptTask_GenerateAsyncTasks()
 */
void RunScheduler(void);
#endif /* __KERNEL_H */
