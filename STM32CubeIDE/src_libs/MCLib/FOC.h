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
#include <stdbool.h>
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
 * @brief PI controller structure
 *
 * Holds parameters and state for a proportional-integral controller
 * with output saturation.
 */
typedef struct {

  /** @brief Proportional gain */
  float kp;

  /** @brief Integral gain */
  float ki;

  /** @brief Integrator accumulator */
  float integrator;

  /** @brief Minimum output limit */
  float out_min;

  /** @brief Maximum output limit */
  float out_max;

} PI_Controller_t;

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

/**
 * @brief Perform Clarke transformation (abc → αβ)
 *
 * Converts three-phase currents (ia, ib, ic) into the stationary
 * two-axis reference frame (alpha-beta).
 *
 * Uses the reduced Clarke transform assuming a balanced system:
 * ia + ib + ic = 0
 *
 * Equations:
 *  - i_alpha = ia
 *  - i_beta  = (ia + 2 * ib) / sqrt(3)
 *
 * @param[in]  ia     Phase A current
 * @param[in]  ib     Phase B current
 * @param[in]  ic     Phase C current (unused in reduced form)
 * @param[out] ialpha Alpha-axis component
 * @param[out] ibeta  Beta-axis component
 *
 * @note Common in FOC implementations
 */
void vFOC_Clarke(float ia, float ib, float ic, float *ialpha, float *ibeta);

/**
 * @brief Perform Park transformation (αβ → dq)
 *
 * Converts stationary reference frame currents (alpha-beta) into the
 * rotating reference frame (d-q) using the electrical angle.
 *
 * This transformation aligns the d-axis with the rotor flux, enabling
 * decoupled control of flux (Id) and torque (Iq).
 *
 * Transformation equations:
 *  - id =  ialpha * cos(theta) + ibeta * sin(theta)
 *  - iq = -ialpha * sin(theta) + ibeta * cos(theta)
 *
 * @param[in]  ialpha    Alpha-axis current component
 * @param[in]  ibeta     Beta-axis current component
 * @param[in]  sinTheta  Sine of electrical angle (θ)
 * @param[in]  cosTheta  Cosine of electrical angle (θ)
 * @param[out] id        Direct-axis current component (flux)
 * @param[out] iq        Quadrature-axis current component (torque)
 *
 * @note
 * - Requires precomputed sin(θ) and cos(θ) for efficiency
 * - Typically used after Clarke transform in FOC pipeline
 *
 * @warning
 * Accuracy depends on the correctness of the electrical angle (θ)
 */
void vFOC_Park(float ialpha, float ibeta, float sinTheta, float cosTheta,
               float *id, float *iq);

/**
 * @brief Executes current control loop (PI controllers)
 *
 * Computes the voltage references (vd, vq) based on the error
 * between reference currents and measured currents in dq frame.
 *
 * This function implements two independent PI controllers:
 * - d-axis (flux control)
 * - q-axis (torque control)
 *
 * @param[in]  id      Measured d-axis current
 * @param[in]  iq      Measured q-axis current
 * @param[in]  id_ref  Reference d-axis current
 * @param[in]  iq_ref  Reference q-axis current
 * @param[out] vd      Output d-axis voltage reference
 * @param[out] vq      Output q-axis voltage reference
 */
void vFOC_CurrentControl(float id, float iq, float id_ref, float iq_ref,
                         float *vd, float *vq);

/**
 * @brief Perform Inverse Park transformation (dq → αβ)
 *
 * Converts rotating frame voltages (d-q) into stationary
 * alpha-beta frame using electrical angle.
 *
 * @param[in]  vd        d-axis voltage reference
 * @param[in]  vq        q-axis voltage reference
 * @param[in]  sinTheta  sine of electrical angle
 * @param[in]  cosTheta  cosine of electrical angle
 * @param[out] valpha    alpha-axis voltage
 * @param[out] vbeta     beta-axis voltage
 */
void vFOC_InversePark(float vd, float vq, float sinTheta, float cosTheta,
                      float *valpha, float *vbeta);
#endif /* __FOC_H */