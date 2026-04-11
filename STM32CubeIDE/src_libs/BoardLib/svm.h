#ifndef SVM_H
#define SVM_H

#include <stdint.h>

/**
 * @brief Inicializa el módulo SVM (si requiere configuración futura).
 */
void vSVM_Init(void);

/**
 * @brief Genera PWM trifásico usando Space Vector Modulation.
 *
 * @param Valpha Componente alfa normalizada (-1.0 a 1.0)
 * @param Vbeta  Componente beta normalizada (-1.0 a 1.0)
 */
void vSVM_Update(float Valpha, float Vbeta);

#endif
