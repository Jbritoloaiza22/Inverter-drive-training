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
 * @brief Set duty cycle for phase A through the kernel interface.
 *
 * This function provides an abstraction layer between the application
 * and the underlying hardware driver (HAL). It allows the application
 * to update the PWM duty cycle for phase A without directly accessing
 * the hardware registers or PWM driver.
 *
 * @param ui32DutyCycle Duty cycle value to be applied to phase A.
 */
void vKernelInterface_SetPhaseADuty(uint32_t ui32DutyCycle);

/**
 * @brief Set duty cycle for phase B through the kernel interface.
 *
 * This function acts as an interface between the application layer
 * and the hardware abstraction layer (HAL). It updates the PWM duty
 * cycle corresponding to phase B while keeping the hardware access
 * encapsulated within the kernel layer.
 *
 * @param ui32DutyCycle Duty cycle value to be applied to phase B.
 */
void vKernelInterface_SetPhaseBDuty(uint32_t ui32DutyCycle);

/**
 * @brief Set duty cycle for phase C through the kernel interface.
 *
 * This function allows the application to modify the PWM duty cycle
 * for phase C via the kernel interface. It prevents the application
 * from directly interacting with low-level PWM driver functions,
 * preserving modularity and hardware abstraction.
 *
 * @param ui32DutyCycle Duty cycle value to be applied to phase C.
 */
void vKernelInterface_SetPhaseCDuty(uint32_t ui32DutyCycle);


void vKernelInterface_TableSinInit(void);
float fKernelInterface_SineLookup(float angle);
