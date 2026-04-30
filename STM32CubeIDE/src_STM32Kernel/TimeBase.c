/**
 * @file TimeBase.c
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
#include "TimeBase.h"

TimeBase_t oTimeBase;

/** @brief Set the 10ms flag.
 */
void TimeBase_10msFlagSet(void) { oTimeBase.flags.bitsFlags.b10ms = 1U; }

/** @brief Set the 20ms flag.
 */
void TimeBase_20msFlagSet(void) { oTimeBase.flags.bitsFlags.b20ms = 1U; }

/** @brief Set the 100ms flag.
 */
void TimeBase_100msFlagSet(void) { oTimeBase.flags.bitsFlags.b100ms = 1U; }

/** @brief Set the 1sec flag.
 */
void TimeBase_1secFlagSet(void) { oTimeBase.flags.bitsFlags.b1sec = 1; }

/** @brief Get the 10ms flag value.
 *
 * @return uint32_t The value of the 10ms flag.
 */
uint32_t TimeBase_10msFlagGet(void) { return oTimeBase.flags.bitsFlags.b10ms; }

/** @brief Get the 20ms flag value.
 *
 * @return uint32_t The value of the 20ms flag.
 */
uint32_t TimeBase_20msFlagGet(void) { return oTimeBase.flags.bitsFlags.b20ms; }

/** @brief Get the 100ms flag value.
 *
 * @return uint32_t The value of the 100ms flag.
 */
uint32_t TimeBase_100msFlagGet(void) {
  return oTimeBase.flags.bitsFlags.b100ms;
}

/** @brief Get the 1sec flag value.
 *
 * @return uint32_t The value of the 1sec flag.
 */
uint32_t TimeBase_1secFlagGet(void) { return oTimeBase.flags.bitsFlags.b1sec; }

/** @brief Clear the 10ms flag.
 */
void TimeBase_10msFlagClear(void) { oTimeBase.flags.bitsFlags.b10ms = 0U; }

/** @brief Clear the 20ms flag.
 */
void TimeBase_20msFlagClear(void) { oTimeBase.flags.bitsFlags.b20ms = 0U; }

/** @brief Clear the 100ms flag.
 */
void TimeBase_100msFlagClear(void) { oTimeBase.flags.bitsFlags.b100ms = 0U; }

/** @brief Clear the 1sec flag.
 */
void TimeBase_1secFlagClear(void) { oTimeBase.flags.bitsFlags.b1sec = 0U; }
