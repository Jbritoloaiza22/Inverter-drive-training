/**
 * @file MotorControl.c
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
static tMotorControl_State MotorControl_State;

void vMotorControl_OnAdcSample(int16_t iBusRaw) {

  /* 1. Pass raw data to sensing layer */
  vCurrentSensing_UpdateRaw(iBusRaw);

  /* 2. Mark sample as available for control loop */
  vMotorControl_SetSampleReady(true);

  /* 3. Optional: update cycle bookkeeping */
  MotorControl_State.u8SampleCount++;
}

void vMotorControl_SetSampleReady(bool bReady) {
  MotorControl_State.u8SampleReady = (uint8_t)bReady;

  if (bReady) {
    MotorControl_State.u8RunControlLoop = 1;
  }
}

void vMotorControl_Process(void) {

  // FOC_Execute(&frame);
}