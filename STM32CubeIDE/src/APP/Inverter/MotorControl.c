/**
 * @file MotorControl.c
 * @brief Motor control orchestration layer implementation
 *
 * This module coordinates data flow between hardware-triggered events
 * (ADC, PWM) and higher-level control algorithms (e.g., FOC).
 *
 * It manages synchronization flags and delegates signal processing
 * to the appropriate modules (e.g., CurrentSensing).
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

#include "MotorControl.h"
#include "CurrentSensing.h"
#include <stdint.h>

/**
 * @brief Internal motor control state
 *
 * Static instance used to track sampling status, synchronization flags,
 * and control execution conditions.
 */
static tMotorControl_State MotorControl_State;

/**
 * @brief Handle ADC sample event
 *
 * This function is called when a new ADC conversion is completed.
 * It forwards the raw sample to the CurrentSensing module and updates
 * internal synchronization flags for control loop execution.
 *
 * @param iBusRaw Raw DC-link current sample (ADC counts)
 *
 * @note This function is typically called from an ADC ISR context.
 */
void vMotorControl_OnAdcSample(int16_t i16BusRaw) {
  /* 1. Sensing */
  vCurrentSensing_UpdateRaw(i16BusRaw);

  /* 2. (Opcional) validar muestra */
  if (!vCurrentSensing_IsReady())
    return;

  /* 3. Contar muestra */
  MotorControl_State.ui8SampleCount++;

  /* 4. Gating configurable */
  if (MotorControl_State.ui8SampleCount >=
      MotorControl_State.ui8SamplesPerPwm) {
    MotorControl_State.ui8SampleCount = 0;

    /* listo para ejecutar control */
    vMotorControl_SetSampleReady(true);
  }
}

/**
 * @brief Set sample ready flag
 *
 * Updates the internal flag indicating that a new ADC sample is available.
 * Optionally triggers control loop execution.
 *
 * @param bReady true if a new sample is available, false otherwise
 *
 * @note This function may be called from ISR context.
 */
void vMotorControl_SetSampleReady(bool bReady) {
  MotorControl_State.ui8SampleReady = (uint8_t)bReady;

  if (bReady) {
    MotorControl_State.ui8RunControlLoop = 1;
  }
}

/**
 * @brief Motor control processing function
 *
 * This function is intended to be called from the main loop or scheduler.
 * It checks if conditions are met to execute the control algorithm.
 *
 * @note FOC execution is not yet implemented at this stage.
 * Future implementation will:
 * - Validate sample readiness
 * - Execute FOC control loop
 * - Reset synchronization flags
 */
void vMotorControl_Process(void) {
  /* Placeholder for future control loop execution */

  /*
  if (MotorControl_State.ui8RunControlLoop)
  {
      MotorControl_State.ui8RunControlLoop = 0;

      FOC_Execute(...);
  }
  */
}

bool vMotorControl_IsControlReady(void) {
  if (MotorControl_State.ui8RunControlLoop) {
    MotorControl_State.ui8RunControlLoop = 0;
    return true;
  }

  return false;
}

void vMotorControl_RunControl(void) {
  /* 5. Reconstruct phase currents from DC-link current */

  /* 6. Clarke transform (abc -> alpha-beta) */

  /* 7. Park transform (alpha-beta -> dq) */

  /* 8. Current control (PI controllers) */

  /* 9. Inverse Park transform (dq -> alpha-beta) */

  /* 4. Detect active SVPWM sector (1..6) */
  /* NOTE: Sector detection is handled internally by SVM */

  /* 10. SVPWM computation */
  /* Convert alpha-beta voltages to duty cycles */

  /* 11. Update PWM registers (CCR1, CCR2, CCR3) */

  /* 12. Prepare next cycle */
}