#ifndef __TIM_H
#define __TIM_H

#include "stm32g0xx_hal.h"
#define TIM2_PRESCALER 63U
#define TIM2_ARR 249U
#define TIM3_PRESCALER 63U
#define TIM3_ARR 999U
void tim2_Init(void);
void tim2_Start(void);
void tim2_IRQHandler_TIM(void);
void tim3_Init(void);
void tim3_Start(void);
void tim3_IRQHandler_TIM(void);
#endif /* __TIM_H */
