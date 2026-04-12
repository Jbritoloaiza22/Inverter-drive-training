#ifndef SVM_H
#define SVM_H

#include <stdint.h>

/**
 * @brief Initializes the SVM module.
 */
void vSVM_Init(void);

/**
 * @brief Generates three-phase PWM using Space Vector Modulation.
 *
 * @param Valpha Alpha component (-1.0 to 1.0)
 * @param Vbeta  Beta component (-1.0 to 1.0)
 */
void vSVM_Update(float Valpha, float Vbeta);

#endif /* SVM_H */