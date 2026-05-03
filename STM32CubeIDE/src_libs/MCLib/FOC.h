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
  float ibus;
  float ialpha;
  float ibeta;

  float id;
  float iq;

  float vd;
  float vq;

  uint8_t sector;

  struct {
    int16_t i16adcraw;
  } adc;
} tFOC_State;

void vFOC_Init(void);
void vFOC_Execute(void);
void vFOC_OnAdcSample(int16_t i16Bus, uint8_t ui8sector);
void vFOC_SetReference(float idref, float iqref);
void vFOC_UpdatePWM(void);
bool vFOC_IsReady(void);
tFOC_State *vFOC_GetState(void);

#endif /* __FOC_H */