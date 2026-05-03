/**
 * @file CurrentSensing.h
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
#ifndef __CURRENTSENSING_H
#define __CURRENTSENSING_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  int16_t i16Raw;

  float fCurrent_A;

  int16_t i16Offset;

  uint8_t ui8Valid;
} tCurrentSensing_State;

#define dVREF 3.3f
#define dADC_RES 4095.0f
#define dRSHUNT 0.005f // 5 mOhm
#define dAMPGAIN 20.0f
#define dCURRENTSCALEGAIN (dVREF / (dADC_RES * dRSHUNT))

void vCurrentSensing_Init(void);
void vCurrentSensing_UpdateRaw(int16_t i16AdcRaw);
float vCurrentSensing_GetBusCurrent_A(void);
void vCurrentSensing_SetOffset(int16_t offset);
bool vCurrentSensing_IsReady(void);

#endif /* __CURRENTSENSING_H */