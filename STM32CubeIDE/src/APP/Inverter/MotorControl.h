/**
 * @file MotorControl.h
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

typedef struct {

  /* ===== Sampling / Sync ===== */
  volatile uint8_t u8SampleReady;
  volatile uint8_t u8SamplesPerPwm;
  volatile uint8_t u8SampleCount;

  /* ===== ADC data (raw domain) ===== */
  volatile int16_t i16BusCurrentRaw;
  volatile uint8_t u8AdcValid;

  /* ===== PWM / timing context ===== */
  volatile uint16_t u16PwmCounter;
  volatile uint8_t u8Sector;

  /* ===== Control flags ===== */
  volatile uint8_t u8RunControlLoop;
  volatile uint8_t u8Fault;

} tMotorControl_State;

void vMotorControl_Init(void);
void vMotorControl_OnAdcSample(int16_t iBusRaw);
void vMotorControl_OnPwmEvent(void);
void vMotorControl_Process(void);
void vMotorControl_SetSampleReady(bool bReady);

#endif /* __MOTORCONTROL_H */