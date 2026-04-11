#ifndef __PWM_H
#define __PWM_H

#include "stm32g0xx_hal.h"

void PWM_Init(void);
void PWM_Start(void);
void PWM_UpdatePhaseCompare(uint32_t compareA, uint32_t compareB, uint32_t compareC);
void PWM_CHANNEL1_SET_CYCLEDUTY(uint32_t ui32DutyCycle);
void PWM_CHANNEL2_SET_CYCLEDUTY(uint32_t ui32DutyCycle);
void PWM_CHANNEL3_SET_CYCLEDUTY(uint32_t ui32DutyCycle);

#endif /* __PWM_H */
