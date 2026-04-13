/**
 * @file kernelinterface.h
 * @brief Interface for communication between application and hardware layer.
 *
 * This file contains function prototypes that initialize system peripherals
 * and provide an interface layer between the application code and the
 * low-level hardware configuration. The functions defined here are intended
 * to configure the system before interrupts are enabled and the main
 * application starts executing.
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

/**
 * @brief Initializes the GPIOs used by the application.
 *
 * Configures the microcontroller's input and output pins, including
 * mode, output type, speed, and pull-up/pull-down resistors according
 * to the system requirements. This allows the application to interact
 * correctly with the configured hardware peripherals.
 *
 * @note Must be called before enabling any interrupts that rely on GPIOs.
 */
#include <stdint.h>
#include <tim.h>
void cbGPIOS(void);

/**
 * @brief   PWM update callback.
 *
 * This function updates the compare values of the PWM channels used
 * for three-phase modulation. It typically reads the next values from
 * a waveform table (e.g., sine table) and writes them to the timer
 * compare registers to generate the desired waveform.
 *
 * @note    Usually executed periodically from a timer interrupt.
 */
void cbPWM(void);

/**
 * @brief Timer update callback.
 *
 * This function is executed when the timer update interrupt occurs.
 * It is typically used to execute periodic tasks such as updating
 * PWM compare values, advancing waveform indexes, or running
 * time-based control routines.
 *
 * @note This function is usually called from the TIM interrupt
 *       service routine (ISR).
 */

void cbTIM(void);
/**
 * @brief   Performs system initializations before enabling interrupts.
 *
 * Sets up essential peripherals and initial system state required
 * by the application before interrupts are enabled. Ensures proper
 * communication between the application layer and HAL components.
 *
 * @note    Recommended to call this at the very start of the program,
 *          after basic hardware initialization.
 */
void vKernelInterface_initBeforeInterruptEnable(void);

/**
 * @brief RCC configuration callback.
 *
 * This function is responsible for performing custom configuration
 * related to the Reset and Clock Control (RCC) peripheral. It may
 * include enabling peripheral clocks or configuring system clock
 * sources required by the application.
 *
 * @note This callback is typically invoked during system initialization
 *       before peripherals dependent on the clock configuration are used.
 */
void cbRCC(void);

/**
 * @brief Enable interrupts for all configured peripherals.
 *
 * This function enables the NVIC interrupts associated with the
 * peripherals used by the application. Currently it enables the
 * interrupts for TIM2 and TIM3 timers.
 *
 * @note Must be called after peripheral initialization and before
 *       starting the timers.
 */
void vKernelInterface_enableInterruptsForAllPeripherals(void);

/**
 * @brief TIM2 interrupt handler interface.
 *
 * This function is called by the hardware interrupt vector when
 * the TIM2 update interrupt occurs. It acts as a bridge between
 * the low-level ISR and the KernelInterface layer.
 *
 * Responsibilities:
 * - Clear the TIM2 interrupt flag
 * - Execute timer-related tasks (if required)
 * - Dispatch events to higher-level modules
 *
 * @note This function should be linked to the actual ISR
 *       (e.g., TIM2_IRQHandler) in the interrupt vector table.
 */
void vKernelInterface_TIM2IRQHandler(void);

/**
 * @brief TIM3 interrupt handler interface.
 *
 * This function is invoked when a TIM3 update interrupt is triggered.
 * It provides an abstraction layer between the hardware ISR and
 * the application/kernel logic.
 *
 * Responsibilities:
 * - Clear the TIM3 interrupt flag
 * - Handle periodic tasks associated with TIM3
 * - Serve as a hook for scheduler or background processing
 *
 * @note This function must be called from the TIM3 ISR
 *       (e.g., TIM3_IRQHandler).
 */
void vKernelInterface_TIM3IRQHandler(void);