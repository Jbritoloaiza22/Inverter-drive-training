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

void cbRCC(void);
