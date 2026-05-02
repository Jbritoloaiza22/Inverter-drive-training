/**
 * @file InterruptTask.c
 * @brief Real-time interrupt task implementation for motor control system.
 *
 * This module implements the interrupt-driven control layer of the embedded
 * motor control firmware.
 *
 * It contains the execution logic for time-critical tasks that are triggered
 * by hardware interrupts such as timer update events, ADC conversions,
 * and communication peripherals.
 *
 * The main role of this module is to execute deterministic real-time control
 * algorithms required for PMSM/BLDC motor operation, including:
 *
 * - Electrical angle generation for open-loop operation
 * - Sinusoidal PWM (SPWM) signal generation
 * - Future support for Space Vector PWM (SVPWM)
 * - Future support for Field Oriented Control (FOC)
 * - ADC-based feedback processing (currents, voltage, temperature)
 *
 * The implementation is designed for STM32 microcontrollers (e.g. STM32G0
 * series) and is intended to run inside high-priority interrupt service
 * routines (ISRs).
 *
 * Key characteristics:
 * - Deterministic execution time
 * - ISR-safe minimal computation overhead
 * - Fixed-step control loop synchronized with PWM frequency
 * - Scalable architecture for advanced motor control algorithms
 *
 * This module acts as the real-time execution layer between hardware interrupts
 * and the motor control algorithm stack.
 *
 * @note All functions executed here must remain fast and non-blocking.
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
#include "KernelInterface.h"
#include "TimeBase.h"
#include "stm32g031xx.h"

extern SPWM_t spwm;
extern Timer_t tim2;
extern Timer_t tim3;
extern SVM_t svm;
extern UART_t uart1;
uint8_t ui8BufferRecepcion[50];
uint8_t ui8IndexDataRX = 0;

typedef struct {
  uint16_t ui16Timer1ms;
  uint16_t ui16Timer20ms;
  uint16_t ui16Timer100ms;
  uint16_t ui16Timer1000ms;
} TIMTask;

TIMTask oTimTaskFlags;

/**
 * @brief Generate asynchronous task flags based on timer tick counters.
 *
 * This function is called from the 1ms timer interrupt (TIM3) and maintains
 * internal counters for generating periodic task flags at different intervals.
 * It implements a software-based time base divider that converts the 1ms
 * interrupt into multiple time-slotted execution windows.
 *
 * The function maintains individual counters for each time interval:
 * - 10ms: General control loop tasks
 * - 20ms: Secondary control or slower feedback processing
 * - 100ms: Slow diagnostic or monitoring tasks
 * - 1000ms (1s): Status reporting or periodic maintenance
 *
 * When a counter reaches its target interval, the corresponding TimeBase flag
 * is set via the TimeBase module, signaling the main scheduler that a task
 * should execute at that interval. The counter then resets or is adjusted to
 * maintain phase alignment.
 *
 * Execution characteristics:
 * - Called from TIM3 ISR at 1ms intervals
 * - Non-blocking execution (completes within ISR time budget)
 * - Uses modular arithmetic to maintain accurate timing
 * - Generates software events for the cooperative scheduler
 *
 * @note This function MUST be called from a 1ms timer interrupt for correct
 * timing behavior. Missing calls or timing variations will degrade the
 * accuracy of generated task intervals.
 *
 * @note This is a private static function not intended for external use.
 *
 * @see TimeBase_10msFlagSet()
 * @see TimeBase_20msFlagSet()
 * @see TimeBase_100msFlagSet()
 * @see TimeBase_1secFlagSet()
 * @see vKernelInterface_TIM3IRQHandler1ms()
 */
static void InterruptTask_GenerateAsyncTasks(void) {
  /* This function can be used to generate asynchronous tasks that need to be
     executed in the main loop, based on flags set by the timer ISRs. For
     example, it can set flags for tasks that need to run every 10ms, 20ms,
     100ms, or 1s. */
  oTimTaskFlags.ui16Timer1ms++;

  /* every 10ms */
  if (oTimTaskFlags.ui16Timer1ms >= 10) {
    TimeBase_10msFlagSet();
    oTimTaskFlags.ui16Timer1ms -= 10;
  } else {
    /*do nothing*/
  }

  /* every 20ms */
  oTimTaskFlags.ui16Timer20ms++;
  if (oTimTaskFlags.ui16Timer20ms >= 20) {
    TimeBase_20msFlagSet();
    oTimTaskFlags.ui16Timer20ms = 0;
  } else {
    /*do nothing*/
  }

  /* every 100ms */
  oTimTaskFlags.ui16Timer100ms++;
  if (oTimTaskFlags.ui16Timer100ms >= 100) {
    TimeBase_100msFlagSet();
    oTimTaskFlags.ui16Timer100ms = 0;
  } else {
    /*do nothing*/
  }

  /* every 1000ms (1s) */
  oTimTaskFlags.ui16Timer1000ms++;
  if (oTimTaskFlags.ui16Timer1000ms >= 1000) {
    TimeBase_1secFlagSet();
    oTimTaskFlags.ui16Timer1000ms = 0;
  } else {
    /*do nothing*/
  }
}
/**
 * @brief This function handles TIM2 global interrupt.
 */
void vKernelInterface_TIM2IRQHandler250us(void) {
  vTimer_ClearIRQ(&tim2);
  SVM_Run(&svm);
}
/**
 * @brief This function handles TIM3 global interrupt.
 */
void vKernelInterface_TIM3IRQHandler1ms(void) {

  vTimer_ClearIRQ(&tim3);
  InterruptTask_GenerateAsyncTasks();
  /*vSPWM_Update(&spwm); onlyt for SPWM, not used in SVM mode*/
}

void vKernelInterface_USART1IRQHandler(void) {
  if (uart1.Instance->ISR & USART_ISR_RXNE_RXFNE) {
    ui8BufferRecepcion[ui8IndexDataRX++] = uart1.Instance->RDR;
  } else if (uart1.Instance->ISR & USART_ISR_TXE_TXFNF) {
    /*send data */
  } else if (uart1.Instance->ISR & USART_ISR_ORE) {
    /*Overrun error*/
  } else if (uart1.Instance->ISR & USART_ISR_FE) {
    /*Framing error*/
  } else {
    /*do nothing */
  }
}

void vKernelInterface_ADCIRQHandler(void) {
  vGPIO_ToggleDebugPin();
  if (ADC1->ISR & ADC_ISR_EOC) {
    uint16_t value = ADC1->DR;
  }
}
