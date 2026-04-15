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

/* =========================================================
 *  CONSTANTS (shared math definitions)
 * ========================================================= */

#define dTWO_BY_SQRT3   (1.15470053838f)
#define dONE_BY_SQRT3   (0.57735026919f)
#define dSQRT3          (1.73205080757f)
#define dTWOPI          (6.28318530718f)
#define dPI             (3.14159265359f)

/* =========================================================
 *  OBJECT DEFINITION (SVM "CLASS")
 * ========================================================= */

/**
 * @brief SVM object structure (encapsulated state)
 */
typedef struct
{
    float theta;        /**< Electrical angle [rad] */
    float freq;         /**< Output frequency [Hz] */
    uint32_t counter;   /**< Internal startup counter */

    float amplitude;    /**< Modulation amplitude */

    uint32_t pwmPeriod; /**< PWM timer period (ARR) */

    void *pwm;          /**< Pointer to PWM driver (opaque handle) */

} SVM_t;

/* =========================================================
 *  PUBLIC API
 * ========================================================= */

/**
 * @brief Initialize SVM object
 *
 * @param self Pointer to SVM instance
 * @param pwmHandle Pointer to PWM driver object
 * @param pwmPeriod Timer period (ARR)
 */
void SVM_Init(SVM_t *self, void *pwmHandle, uint32_t pwmPeriod);

/**
 * @brief Execute one SVPWM update step (call in ISR)
 *
 * @param self Pointer to SVM instance
 */
void SVM_Run(SVM_t *self);


#endif /* SVM_H */
