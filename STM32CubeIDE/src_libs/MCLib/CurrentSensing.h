/**
 * @file CurrentSensing.h
 * @brief Current sensing module interface and state definition
 *
 * This module handles acquisition and conditioning of current measurements
 * from ADC raw values, including offset correction and scaling to physical
 * units.
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

#ifndef CURRENT_SENSING_H_
#define CURRENT_SENSING_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Current sensing runtime state
 *
 * Holds raw ADC measurements and processed current values.
 */
typedef struct {
  /** Raw ADC sample (counts) */
  int16_t i16Raw;

  /** Bus current in amperes */
  float fCurrent_A;

  /** ADC offset (counts) */
  int16_t i16Offset;

  /** Valid sample flag */
  uint8_t ui8Valid;

} tCurrentSensing_State;

/**
 * @name Hardware-dependent scaling constants
 * @{
 */

/** ADC reference voltage (Volts) */
#define dVREF 3.3f

/** ADC resolution (counts) */
#define dADC_RES 4095.0f

/** Shunt resistance (Ohms) */
#define dRSHUNT 0.005f /**< 5 mΩ */

/** Amplifier gain */
#define dAMPGAIN 20.0f

/**
 * @brief Current scaling gain (A per ADC count)
 *
 * Converts ADC counts to current in amperes:
 * I = ADC_counts * dCURRENTSCALEGAIN
 */
#define dCURRENTSCALEGAIN (dVREF / (dADC_RES * dRSHUNT * dAMPGAIN))

/** @} */

/**
 * @brief Initialize current sensing module
 *
 * Initializes internal state, offsets, and filtering variables.
 */
void vCurrentSensing_Init(void);

/**
 * @brief Update raw ADC measurement
 *
 * Processes a new ADC sample, applying offset correction and scaling
 * to obtain the bus current in amperes.
 *
 * @param i16AdcRaw Raw ADC value (counts)
 */
void vCurrentSensing_UpdateRaw(int16_t i16AdcRaw);

/**
 * @brief Get bus current in amperes
 *
 * Returns the latest processed current value.
 *
 * @return Current in amperes
 */
float vCurrentSensing_GetBusCurrent_A(void);

/**
 * @brief Set ADC offset
 *
 * Defines the offset used for raw ADC correction.
 *
 * @param offset Offset value in ADC counts
 */
void vCurrentSensing_SetOffset(int16_t offset);

/**
 * @brief Check if a valid current sample is available
 *
 * Indicates whether the latest measurement is valid and ready for use.
 *
 * @return true if valid sample is available, false otherwise
 */
bool vCurrentSensing_IsReady(void);

#endif /* CURRENT_SENSING_H_ */