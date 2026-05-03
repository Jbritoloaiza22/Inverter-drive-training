/**
 * @file MotorControl.h
 * @brief Motor control orchestration layer interface
 *
 * This module acts as an intermediate layer between hardware events
 * (ADC, PWM) and the control algorithm (FOC).
 *
 * It is responsible for:
 * - Synchronizing ADC sampling with PWM events
 * - Managing control loop execution timing
 * - Providing a central state for motor control coordination
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

#ifndef __MOTORCONTROL_H
#define __MOTORCONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Motor control runtime state
 *
 * Holds synchronization flags, ADC data, PWM context, and control execution
 * flags. This structure is shared between ISR context and main control loop.
 */
typedef struct {
  /** @name Sampling / Synchronization */
  /** @{ */

  /** Indicates a new ADC sample is available */
  volatile uint8_t ui8SampleReady;

  /** Number of samples expected per PWM cycle */
  volatile uint8_t ui8SamplesPerPwm;

  /** Counter of samples within current PWM cycle */
  volatile uint8_t ui8SampleCount;

  /** @} */

  /** @name ADC Data (raw domain) */
  /** @{ */

  /** Raw DC-link current sample (ADC counts) */
  volatile int16_t i16BusCurrentRaw;

  /** Indicates validity of ADC data */
  volatile uint8_t ui8AdcValid;

  /** @} */

  /** @name PWM / Timing Context */
  /** @{ */

  /** Current PWM counter value */
  volatile uint16_t ui16PwmCounter;

  /** Active SVPWM sector (1–6) */
  volatile uint8_t ui8Sector;

  /** @} */

  /** @name Control Flags */
  /** @{ */

  /** Flag to trigger execution of control loop */
  volatile uint8_t ui8RunControlLoop;

  /** Fault flag (e.g., overcurrent, invalid state) */
  volatile uint8_t ui8Fault;

  /** @} */

} tMotorControl_State;

/**
 * @brief Initialize motor control module
 *
 * Initializes internal state variables and prepares the control layer
 * for operation.
 */
void vMotorControl_Init(void);

/**
 * @brief Handle ADC sample event
 *
 * Called when a new ADC sample is available.
 * This function forwards the sample to the sensing layer and updates
 * synchronization flags.
 *
 * @param iBusRaw Raw DC-link current sample (ADC counts)
 */
void vMotorControl_OnAdcSample(int16_t i16BusRaw);

/**
 * @brief Handle PWM event
 *
 * Called on PWM update or synchronization event.
 * Used to align control execution with PWM cycle boundaries.
 */
void vMotorControl_OnPwmEvent(void);

/**
 * @brief Process motor control tasks
 *
 * Executes control loop when conditions are met (e.g., new sample available).
 * This function is typically called in the main loop or scheduler.
 */
void vMotorControl_Process(void);

/**
 * @brief Set sample ready flag
 *
 * Updates internal flag indicating availability of a new ADC sample
 * and optionally triggers control loop execution.
 *
 * @param bReady true if sample is ready, false otherwise
 */
void vMotorControl_SetSampleReady(bool bReady);

#ifdef __cplusplus
}
#endif

#endif /* __MOTORCONTROL_H */