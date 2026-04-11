/**
 * @file svm.h
 * @brief Space Vector Modulation (SVM) module for three-phase PWM generation.
 *
 * This module implements the Space Vector Modulation algorithm used to
 * generate three-phase PWM duty cycles for motor control and inverter
 * applications. The SVM algorithm computes the appropriate duty cycles
 * for the three phases based on the reference voltage vector within
 * the α-β stationary reference frame.
 *
 * The resulting duty cycles are typically applied to a timer peripheral
 * (e.g., TIM1) configured for complementary three-phase PWM generation.
 *
 * This module is commonly used in Field-Oriented Control (FOC),
 * BLDC control, and inverter-based power electronics systems.
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

#ifndef __SVM_H
#define __SVM_H

#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>
#include <stdint.h>

typedef struct{
	float Va;
	float Vb;
	float Vc;
} kPhaseVoltages;

typedef struct{
	float T1;
	float T2;
	float T0;
} kSVMTimes;




#ifdef __cplusplus
}
#endif

#endif /* __SVM_H */
