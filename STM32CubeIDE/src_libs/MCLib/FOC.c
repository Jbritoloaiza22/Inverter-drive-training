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

void vFOC_CurrentControl(float id, float iq, float id_ref, float iq_ref,
                         float *vd, float *vq) {
  float err_d = id_ref - id;
  float err_q = iq_ref - iq;

  *vd = fPI_Run(&pi_d, err_d);
  *vq = fPI_Run(&pi_q, err_q);
}

static float fPI_Run(PI_Controller_t *pi, float error) {
  /* Proporcional */
  float p = pi->kp * error;

  /* Integrador */
  pi->integrator += pi->ki * error;

  /* Suma */
  float out = p + pi->integrator;

  /* Saturación + anti-windup simple */
  if (out > pi->out_max) {
    out = pi->out_max;
    /* evitar seguir integrando hacia arriba */
    if (error > 0.0f) {
      pi->integrator -= pi->ki * error;
    }
  } else if (out < pi->out_min) {
    out = pi->out_min;
    /* evitar seguir integrando hacia abajo */
    if (error < 0.0f) {
      pi->integrator -= pi->ki * error;
    }
  }

  return out;
}