/**
 * @file svm.h
 * @brief Space Vector Modulation (SVM) driver .
 *
 * This module implements Space Vector Modulation using an
 * object-oriented approach in C.
 *
 * The SVM_t structure represents the SVM "object" and encapsulates
 * its configuration and runtime state.
 *
 * Responsibilities:
 * - αβ → abc transformation
 * - Voltage normalization
 * - PWM duty generation
 *
 * Typically used in:
 * - Field Oriented Control (FOC)
 * - Three-phase inverter control
 *
 * @author
 * Jesus Daniel Britoloaiza
 */

#ifndef SVM_H
#define SVM_H

#include <stdint.h>
#include <complex.h>

#define dTWO_BY_SQRT3 1.15470053838f
#define dONE_BY_SQRT3 0.57735026919f
#define dSQRT3 1.73205080757f
#define dTWOPI 6.2831853f
#define dPI 3.1415926f



void vSVM_PeriodElapsedCallback(void);


#endif /* SVM_H */
