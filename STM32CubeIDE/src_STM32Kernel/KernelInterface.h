/**
 * @file    kernelinterface.h
 * @brief   Interface for communication between application and HAL
 *
 * This file contains function prototypes that initialize peripherals
 * and provide an interface layer between the application code and
 * the Hardware Abstraction Layer (HAL). Functions here are meant
 * to configure the system before enabling interrupts.
 */

/**
 * @brief   Initializes the GPIOs used by the application.
 *
 * Configures the microcontroller's input and output pins, setting the mode,
 * output type, speed, and pull-up/pull-down resistors according to system requirements.
 * This allows the application to interact safely with the underlying HAL.
 *
 * @note    Must be called before enabling any interrupts that rely on GPIOs.
 */
void cbGPIOS(void);


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
void InitBeforeInterruptEnable(void);
