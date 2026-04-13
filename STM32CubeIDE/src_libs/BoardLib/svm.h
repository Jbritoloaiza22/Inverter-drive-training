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
 * SVM OBJECT
 * ========================================================= */

/**
 * @brief SVM object structure.
 *
 * Represents a Space Vector Modulation instance.
 */
typedef struct
{
    /**
     * @brief Initialization flag.
     * - 0: Not initialized
     * - 1: Initialized
     */
    uint8_t initialized;

} SVM_t;

/* =========================================================
 * PUBLIC API
 * ========================================================= */

/**
 * @brief Initialize SVM module.
 *
 * @param[in,out] self Pointer to SVM object
 */
void vSVM_Init(SVM_t *self);

/**
 * @brief Update SVM output.
 *
 * Generates PWM duty cycles from αβ components.
 *
 * @param[in,out] self Pointer to SVM object
 * @param[in] Valpha Alpha component (-1.0 to 1.0)
 * @param[in] Vbeta  Beta component (-1.0 to 1.0)
 */
void vSVM_Update(SVM_t *self, float Valpha, float Vbeta);

/**
 * @brief Kernel callback for SVM.
 */
void cbSVM(void);

#endif /* SVM_H */