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

/**
 * @brief FOC runtime state structure
 *
 * This structure contains all relevant variables used during the FOC control
 * loop, including measured currents, transformed components, control outputs,
 * and auxiliary ADC data.
 */
typedef struct {
  /** DC-link current (Amperes) */
  float ibus;

  /** Alpha-axis current (Clarke transform output) */
  float ialpha;

  /** Beta-axis current (Clarke transform output) */
  float ibeta;

  /** d-axis current (Park transform output) */
  float id;

  /** q-axis current (Park transform output) */
  float iq;

  /** d-axis voltage reference */
  float vd;

  /** q-axis voltage reference */
  float vq;

  /** Current SVPWM sector (1–6) */
  uint8_t sector;

  /**
   * @brief Raw ADC data container
   */
  struct {
    /** Raw ADC sample (counts) */
    int16_t i16adcraw;
  } adc;

} tFOC_State;

/**
 * @brief Initialize FOC module
 *
 * Initializes internal state variables, controllers, and default references.
 */
void vFOC_Init(void);

/**
 * @brief Execute FOC control loop
 *
 * Runs the full control algorithm:
 * Clarke → Park → PI controllers → Inverse Park → SVPWM.
 *
 * This function should be called when a valid current sample is available.
 */
void vFOC_Execute(void);

/**
 * @brief Provide ADC sample to FOC
 *
 * Updates FOC input data with a new ADC measurement and corresponding sector.
 *
 * @param i16Bus   Raw DC-link current sample (ADC counts)
 * @param ui8sector Current SVPWM sector (1–6)
 */
void vFOC_OnAdcSample(int16_t i16Bus, uint8_t ui8sector);

/**
 * @brief Set FOC current references
 *
 * Defines desired d-axis and q-axis current setpoints.
 *
 * @param idref Reference d-axis current (Amperes)
 * @param iqref Reference q-axis current (Amperes)
 */
void vFOC_SetReference(float idref, float iqref);

/**
 * @brief Update PWM outputs
 *
 * Converts computed voltage references into PWM duty cycles
 * and updates hardware timer registers.
 */
void vFOC_UpdatePWM(void);

/**
 * @brief Check if FOC is ready to execute
 *
 * Indicates whether required inputs (e.g., ADC samples) are available.
 *
 * @return true if ready, false otherwise
 */
bool vFOC_IsReady(void);

/**
 * @brief Get pointer to FOC state
 *
 * Provides access to internal FOC state for monitoring or debugging.
 *
 * @return Pointer to tFOC_State structure
 */
tFOC_State *vFOC_GetState(void);

#endif /* __FOC_H */