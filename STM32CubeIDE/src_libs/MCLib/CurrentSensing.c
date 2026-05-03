/**
 * @file CurrentSensing.c
 * @brief Current sensing module implementation
 *
 * This file implements the processing of ADC raw samples into
 * physical current values, including offset correction and filtering.
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

#include "CurrentSensing.h"

/**
 * @brief Internal state of current sensing module
 *
 * Static instance holding the latest ADC sample, processed current value,
 * offset, and validity flag.
 */
static tCurrentSensing_State CurrentSensing_State;

/**
 * @brief Update current measurement from ADC raw sample
 *
 * This function performs:
 * - Raw sample storage
 * - Offset correction
 * - Conversion to physical current (Amperes)
 * - First-order low-pass filtering
 *
 * @param i16AdcRaw Raw ADC value (counts)
 */
void vCurrentSensing_UpdateRaw(int16_t i16AdcRaw) {
  /* Store raw ADC sample */
  CurrentSensing_State.i16Raw = i16AdcRaw;

  /* Apply offset correction */
  int32_t i32Temp = (int32_t)i16AdcRaw - CurrentSensing_State.i16Offset;

  /* Convert to physical current (Amperes) */
  float fCurrent = (float)i32Temp * dCURRENTSCALEGAIN;

  /* Apply simple first-order low-pass filter */
  CurrentSensing_State.fCurrent_A =
      CurrentSensing_State.fCurrent_A * 0.9f + fCurrent * 0.1f;

  /* Mark sample as valid */
  CurrentSensing_State.ui8Valid = 1;
}

/**
 * @brief Check if a valid current sample is available
 *
 * This function indicates whether the current sensing module has a valid
 * and usable measurement available. The validity flag is set when a new
 * ADC sample has been processed and converted into a current value.
 *
 * @details
 * - Returns the internal validity flag without modifying it
 * - Does not consume or clear the flag (non-destructive read)
 * - Intended to be used by upper layers (e.g., MotorControl) to verify
 *   data readiness before executing control algorithms
 *
 * @note
 * This function is typically called after vCurrentSensing_UpdateRaw()
 * within the control pipeline.
 *
 * @return true  A valid current sample is available
 * @return false No valid sample available
 */
bool vCurrentSensing_IsReady(void) {
  return (CurrentSensing_State.ui8Valid != 0);
}

void vCurrentSensing_ReconstructABC(float *ia, float *ib, float *ic) {
  float ibus = CurrentSensing_State.fCurrent_A;

  *ia = ibus;
  *ib = -0.5f * ibus;
  *ic = -0.5f * ibus;
}