/**
 * @file kernel.c
 * @brief Main application entry point.
 *
 * This file contains the main program flow and peripheral initialization
 * routines for the STM32G031 microcontroller. The application initializes
 * the system, configures peripherals such as UART and ADC, enables timer
 * interrupts, and executes the main control loop.
 *
 * The system also relies on callback-based initialization functions
 * defined in the kernel interface to configure clocks, GPIOs, PWM,
 * and timers before enabling interrupts.
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
#include "KernelInterface.h"
#include "TimeBase.h"
#include "gpio.h"
extern TimeBase_t oTimeBase;
/* tracking version */
#define FW_VERSION "v1.0.0"

/** @brief Example counter used for PWM related tasks */
uint32_t ui32counter = 0;

/**
 * @brief Increment internal PWM counter.
 *
 * This function increments a global counter that may be used
 * for waveform indexing or periodic PWM related operations.
 */
void incCountertopwmDebug(void) { ui32counter++; }

/**
 * @brief Execute periodic tasks based on time base flags.
 *
 * This function implements the cooperative scheduler loop that executes
 * application tasks at different intervals. Each task is triggered by
 * its corresponding time base flag set by the interrupt handler.
 *
 * The scheduler operates on a non-blocking, cooperative model where:
 * - Each task checks its flag and executes if the time interval has elapsed
 * - The flag is cleared after task execution to prevent re-execution
 * - No task blocks or waits, allowing rapid loop cycling
 *
 * Supported task intervals:
 * - 10 milliseconds: General periodic tasks
 * - 20 milliseconds: Slower periodic operations
 * - 100 milliseconds: Background maintenance tasks
 * - 1 second: Status monitoring and diagnostics
 *
 * @note This function should be called continuously in the main loop
 * after system initialization and interrupt enablement.
 *
 * @see TimeBase_10msFlagGet()
 * @see TimeBase_20msFlagGet()
 * @see TimeBase_100msFlagGet()
 * @see TimeBase_1secFlagGet()
 */
void RunScheduler(void) {
  /* 10ms periodic task */
  if (TimeBase_10msFlagGet()) {
    /* Insert 10ms task implementation here */
    TimeBase_10msFlagClear();
  } else {
    /*do nothing*/
  }
  /* 20ms periodic task */
  if (TimeBase_20msFlagGet()) {
    /* Insert 20ms task implementation here */
    TimeBase_20msFlagClear();
  } else {
    /*do nothing*/
  }

  /* 100ms periodic task */
  if (TimeBase_100msFlagGet()) {
    /* Insert 100ms task implementation here */
    TimeBase_100msFlagClear();
  } else {
    /*do nothing*/
  }

  /* 1 second periodic task */
  if (TimeBase_1secFlagGet()) {
    /* Insert 1s task implementation here */
    TimeBase_1secFlagClear();
  } else {
    /*do nothing*/
  }
}

/**
 * @brief Main program entry point.
 *
 * Initializes the HAL library, configures system peripherals,
 * enables timer interrupts, and runs the main application loop.
 *
 * @retval int Program return status (never returns in embedded systems)
 */
int main(void) {
  HAL_Init();

  /* Initialize system components before enabling interrupts */
  vKernelInterface_initBeforeInterruptEnable();

  /*enable user interrupts */
  vKernelInterface_enableInterruptsForAllPeripherals();
  while (1) {
    RunScheduler();
  }
}

/**
 * @brief Error handler function.
 *
 * This function is executed whenever a HAL error occurs.
 * The system disables interrupts and enters an infinite loop.
 */
void Error_Handler(void) {
  __disable_irq();
  while (1) {
  }
}

/***************************************************************************
 * Custom initialization functions
 ***************************************************************************/

/**
 * @brief Initialize system modules before enabling interrupts.
 *
 * This function executes a sequence of callback functions responsible
 * for configuring the system clock, GPIOs, PWM modules, and timers.
 *
 * The callbacks are defined in the kernel interface layer to allow
 * hardware abstraction and modular configuration.
 */
void vKernelInterface_initBeforeInterruptEnable(void) {
  cbRCC();
  cbGPIOS();
  cbADC();
  cbPWM();
  cbTIM();
  cbUART();
  cbSVPWM();
}

/**
 * @brief Enable interrupts for all configured peripherals.
 *
 * Configures and enables the Nested Vector Interrupt Controller (NVIC)
 * for the timers used in the application. Each interrupt is assigned
 * a priority level before being enabled.
 *
 * The following interrupts are enabled:
 * - TIM2 update interrupt
 * - TIM3 update interrupt
 */
void vKernelInterface_enableInterruptsForAllPeripherals(void) {
  /* Enable TIM2 interrupt */
  vCORTEX_NVICSetPriority(TIM2_IRQn, 2, 0);
  vCORTEX_NVICEnableIRQ(TIM2_IRQn);

  /* Enable TIM3 interrupt */
  vCORTEX_NVICSetPriority(TIM3_IRQn, 4, 0);
  vCORTEX_NVICEnableIRQ(TIM3_IRQn);

  /* Enable UART1 interrupt */
  vCORTEX_NVICSetPriority(USART1_IRQn, 3, 0);
  vCORTEX_NVICEnableIRQ(USART1_IRQn);

  /* Enable ADC interrupt */
  vCORTEX_NVICSetPriority(ADC1_IRQn, 5, 0);
  vCORTEX_NVICEnableIRQ(ADC1_IRQn);
}
