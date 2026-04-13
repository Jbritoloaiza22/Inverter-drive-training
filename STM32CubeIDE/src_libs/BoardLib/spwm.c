/**
 * @file spwm.c
 * @brief Sinusoidal PWM (SPWM) implementation for three-phase motor control.
 *
 * This module implements a basic Sinusoidal Pulse Width Modulation (SPWM)
 * strategy for driving a three-phase inverter used in PMSM or BLDC motor control.
 *
 * The algorithm generates three sinusoidal reference signals (Va, Vb, Vc)
 * that are phase-shifted by 120 degrees. These signals are then scaled using
 * a modulation index and converted into duty cycles for a hardware timer
 * (typically TIM1) to generate PWM signals for power stage switching.
 *
 * This implementation is intended for educational purposes and open-loop
 * motor control experiments. It does not include current control loops,
 * sensor feedback, or space vector optimization (SVPWM).
 *
 * Key characteristics:
 * - Pure sinusoidal generation (no sector decomposition)
 * - 3-phase balanced waveform generation
 * - Simple amplitude modulation (modulation index)
 * - Direct conversion to PWM duty cycles (0–ARR range)
 * - Suitable for open-loop motor spin testing
 *
 * Typical usage:
 * - Open-loop PMSM/BLDC motor startup
 * - Learning PWM modulation concepts
 * - Base stage before SVPWM or FOC implementation
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
#include "spwm.h"
#include "pwm.h"
#include "stm32g031xx.h"
#include <math.h>
#include <stdint.h>

#define dSINTABLESIZE 1024
#define dPI 3.14159265358979323846f
float sin_table[dSINTABLESIZE];

/* global variables */
volatile float theta = 0.0f; /* radians */
float phase_v = 0.0f;
float phase_u = 0.0f;
float phase_w = 0.0f;

float duty_u = 0.0f;
float duty_v = 0.0f;
float duty_w = 0.0f;

void vSPWM_TableSinInit(void)
{
  /* Initialize the sine table with precomputed values */
  /* This function can be called during system initialization if needed */
  for(uint32_t i = 0; i < dSINTABLESIZE; i++)
  {
    /* Compute sine values scaled to the desired range (e.g., 0 to 1000) */
    sin_table[i] = ((sinf((2 * dPI * (float)i) / (float)dSINTABLESIZE)));
  }
}

float fSPWM_SineLookup(float angle)
{
  while(angle < 0)angle += 2.0f * dPI;
  while(angle >= 2.0f * dPI)angle -= 2.0f * dPI;

  int32_t index = (uint32_t)(angle * (dSINTABLESIZE / (2.0f * dPI)));
  return sin_table[index];
}
void vSPWM_Update(void)
{
  theta += 0.06f;
  if(theta >= 2.0f * dPI)
  {
    theta -= 2.0f * dPI;
  }
  phase_u = fSPWM_SineLookup(theta);
  phase_v = fSPWM_SineLookup(theta - 2.0f * dPI / 3.0f);
  phase_w = fSPWM_SineLookup(theta + 2.0f * dPI / 3.0f);

  duty_u = ((phase_u + 1.0f) * 0.5f) * 1999;
  duty_v = ((phase_v + 1.0f) * 0.5f) * 1999;
  duty_w = ((phase_w + 1.0f) * 0.5f) * 1999;

  if(duty_u > 1999)duty_u = 1999;
  if(duty_v > 1999)duty_v = 1999;
  if(duty_w > 1999)duty_w = 1999;

  vKernelInterface_SetPhaseADuty((uint32_t)duty_u);
  vKernelInterface_SetPhaseBDuty((uint32_t)duty_v );
  vKernelInterface_SetPhaseCDuty((uint32_t)duty_w );
}
