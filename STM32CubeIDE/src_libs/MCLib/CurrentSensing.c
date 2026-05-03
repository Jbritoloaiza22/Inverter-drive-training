/**
 * @file CurrentSensing.c
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

static tCurrentSensing_State CurrentSensing_State;

void vCurrentSensing_UpdateRaw(int16_t i16AdcRaw) {

  CurrentSensing_State.i16Raw = i16AdcRaw;

  int32_t i32Temp = (int32_t)i16AdcRaw - CurrentSensing_State.i16Offset;

  float fCurrent = (float)i32Temp * dCURRENTSCALEGAIN;

  /* simple filter */
  CurrentSensing_State.fCurrent_A =
      CurrentSensing_State.fCurrent_A * 0.9f + fCurrent * 0.1f;

  CurrentSensing_State.ui8Valid = 1;
}