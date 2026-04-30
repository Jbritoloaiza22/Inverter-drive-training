/**
 * @file TimeBase.h
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

#ifndef __TIMEBASE_H
#define __TIMEBASE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#include <stdint.h>

typedef union kFlags_t {
  uint8_t ui8EveryFlag; /* Flag set every time the timer reaches the auto-reload
                           value */
  struct {
    uint32_t b10ms : 1;  /* Flag set every 10ms */
    uint32_t b100ms : 1; /* Flag set every 100ms */
    uint32_t b20ms : 1;  /* Flag set every 20ms */
    uint32_t b1sec : 1;  /* Flag set every 1s */
  } bitsFlags;
} TimeBaseFlags_t;

typedef struct kTimeBase_t {
  uint32_t ui32Counter;  /* Counter incremented by timer ISR */
  TimeBaseFlags_t flags; /* Time base flags */
} TimeBase_t;

/** @brief Set the 10ms flag */
void TimeBase_10msFlagSet(void);
/** @brief Set the 20ms flag */
void TimeBase_20msFlagSet(void);
/** @brief Set the 100ms flag */
void TimeBase_100msFlagSet(void);
/** @brief Set the 1s flag */
void TimeBase_1secFlagSet(void);
/** @brief Get the 10ms flag */
uint32_t TimeBase_10msFlagGet(void);
/** @brief Get the 20ms flag */
uint32_t TimeBase_20msFlagGet(void);
/** @brief Get the 100ms flag */
uint32_t TimeBase_100msFlagGet(void);
/** @brief Get the 1s flag */
uint32_t TimeBase_1secFlagGet(void);
/** @brief Clear the 10ms flag */
void TimeBase_10msFlagClear(void);
/** @brief Clear the 20ms flag */
void TimeBase_20msFlagClear(void);
/** @brief Clear the 100ms flag */
void TimeBase_100msFlagClear(void);
/** @brief Clear the 1s flag */
void TimeBase_1secFlagClear(void);

#endif /* __TIMEBASE_H */