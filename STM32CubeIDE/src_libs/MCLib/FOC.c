/**
 * @file foc.c
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
#include "FOC.h"
#include <math.h>

#define dONE_BY_SQRT3 (0.57735026919f)

static PI_Controller_t pi_d;
static PI_Controller_t pi_q;

static float fPI_Run(PI_Controller_t *pi, float error);

/**
 * @brief Clarke transform implementation
 */
void vFOC_Clarke(float ia, float ib, float ic, float *ialpha, float *ibeta) {
  (void)ic; // no se usa en forma reducida

  *ialpha = ia;
  *ibeta = (ia + 2.0f * ib) * dONE_BY_SQRT3;
}

/**
 * @brief Park transform implementation
 *
 * Converts alpha-beta currents into dq frame using provided angle.
 */
void vFOC_Park(float ialpha, float ibeta, float sinTheta, float cosTheta,
               float *id, float *iq) {
  *id = ialpha * cosTheta + ibeta * sinTheta;
  *iq = -ialpha * sinTheta + ibeta * cosTheta;
}

/**
 * @brief Current control implementation using PI regulators
 */
void vFOC_CurrentControl(float id, float iq, float id_ref, float iq_ref,
                         float *vd, float *vq) {
  float err_d = id_ref - id;
  float err_q = iq_ref - iq;

  *vd = fPI_Run(&pi_d, err_d);
  *vq = fPI_Run(&pi_q, err_q);
}

/**
 * @brief PI controller execution with basic anti-windup
 *
 * Implements a proportional-integral controller with output saturation
 * and simple anti-windup correction.
 *
 * @param[in,out] pi     Pointer to PI controller structure
 * @param[in]     error  Control error input
 * @return Control output (saturated)
 */
static float fPI_Run(PI_Controller_t *pi, float error) {
  /* Proportional term */
  float p = pi->kp * error;

  /* Integral term */
  pi->integrator += pi->ki * error;

  /* Raw output */
  float out = p + pi->integrator;

  /* Saturation + anti-windup */
  if (out > pi->out_max) {
    out = pi->out_max;

    /* Prevent further integration in positive direction */
    if (error > 0.0f) {
      pi->integrator -= pi->ki * error;
    } else {
      /*do nothing*/
    }
  } else if (out < pi->out_min) {
    out = pi->out_min;

    /* Prevent further integration in negative direction */
    if (error < 0.0f) {
      pi->integrator -= pi->ki * error;
    } else {
      /* do nothing*/
    }
  } else {
    /*do nothing*/
  }

  return out;
}

/**
 * @brief Inverse Park transformation (dq → αβ)
 *
 * Converts voltage references from the rotating dq reference frame
 * into the stationary alpha-beta frame using the electrical angle.
 *
 * This function is used in the FOC control loop to generate the
 * stationary voltage vector required by the SVPWM stage.
 *
 * @param[in]  vd        d-axis voltage reference
 * @param[in]  vq        q-axis voltage reference
 * @param[in]  sinTheta  Sine of electrical angle θ
 * @param[in]  cosTheta  Cosine of electrical angle θ
 * @param[out] valpha    Alpha-axis voltage output
 * @param[out] vbeta     Beta-axis voltage output
 */
void vFOC_InversePark(float vd, float vq,
                      float sinTheta, float cosTheta,
                      float *valpha, float *vbeta)
{
    *valpha = vd * cosTheta - vq * sinTheta;
    *vbeta  = vd * sinTheta + vq * cosTheta;
}