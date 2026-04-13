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
#include "spwm.h"

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

/**
 * @brief RCC initialization callback.
 *
 * This function initializes and configures the Reset and Clock Control (RCC)
 * subsystem. It sets up the system clock source, PLL configuration,
 * and enables the required peripheral clocks.
 *
 * @note This function must be executed before initializing any peripheral
 *       that depends on clock configuration.
 */
void cbRCC(void);

/**
 * @brief SPWM initialization callback.
 *
 * This function initializes the Sinusoidal PWM (SPWM) module.
 * It configures internal parameters such as the sine table,
 * modulation step, and PWM period.
 *
 * @note Typically called once during system startup.
 */
void cbSPWM(void);

/**
 * @brief PWM initialization callback.
 *
 * This function initializes and starts the PWM peripheral.
 * It configures the timer (e.g., TIM1) for three-phase PWM generation
 * and enables the output channels.
 *
 * @note This function is usually executed during system initialization
 *       before starting modulation (SPWM/SVM).
 */
void cbPWM(void);

/**
 * @brief Timer initialization callback.
 *
 * This function initializes and starts the system timers (e.g., TIM2, TIM3).
 * These timers are typically used to generate periodic interrupts for
 * time-based tasks such as control loops or waveform updates.
 *
 * @note Called during system initialization phase.
 */
void cbTIM(void);

/**
 * @brief GPIO initialization callback.
 *
 * This function configures General Purpose Input/Output (GPIO) pins,
 * including mode (input/output/alternate), speed, pull-up/down resistors,
 * and alternate function mapping required by peripherals.
 *
 * @note Must be executed before using any GPIO-dependent peripheral
 *       such as PWM outputs or communication interfaces.
 */
void cbGPIOS(void);