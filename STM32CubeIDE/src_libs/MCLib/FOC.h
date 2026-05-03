/**
 * @file foc.h
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
#ifndef __FOC_H
#define __FOC_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
typedef struct {
  float i_bus;
  float i_alpha;
  float i_beta;

  float i_d;
  float i_q;

  float v_d;
  float v_q;

  uint8_t sector;

  struct {
    int16_t adc_raw;
  } adc;
} tFOC_State;

void vFOC_Init(void);
void vFOC_Execute(void);
void vFOC_OnAdcSample(int16_t iBus, uint8_t sector);
void vFOC_SetReference(float id_ref, float iq_ref);
void vFOC_UpdatePWM(void);
bool vFOC_IsReady(void);
tFOC_State *vFOC_GetState(void);

#endif /* __FOC_H */