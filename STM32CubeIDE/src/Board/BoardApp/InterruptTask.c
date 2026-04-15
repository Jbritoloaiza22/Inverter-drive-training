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
 * The implementation is designed for STM32 microcontrollers (e.g. STM32G0 series)
 * and is intended to run inside high-priority interrupt service routines (ISRs).
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
#include "stm32g031xx.h"

extern SPWM_t spwm;
extern Timer_t tim2;
extern Timer_t tim3;
extern SVM_t svm;
/**
  * @brief This function handles TIM2 global interrupt.
  */
void vKernelInterface_TIM2IRQHandler(void)
{
  vTimer_ClearIRQ(&tim2);
  SVM_Run(&svm);
}
/**
  * @brief This function handles TIM2 global interrupt.
  */
void vKernelInterface_TIM3IRQHandler(void)
{

  vTimer_ClearIRQ(&tim3);
  //vSPWM_Update(&spwm); onlyt for SPWM, not used in SVM mode
}

