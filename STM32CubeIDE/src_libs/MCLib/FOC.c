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
#include <math.h>

#define ONE_BY_SQRT3 (0.57735026919f)

/**
 * @brief Clarke transform implementation
 */
void vFOC_Clarke(float ia, float ib, float ic, float *ialpha, float *ibeta) {
  (void)ic; // no se usa en forma reducida

  *ialpha = ia;
  *ibeta = (ia + 2.0f * ib) * ONE_BY_SQRT3;
}