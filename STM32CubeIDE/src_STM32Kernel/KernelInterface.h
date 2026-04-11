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
void InitBeforeInterruptEnable(void);

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
