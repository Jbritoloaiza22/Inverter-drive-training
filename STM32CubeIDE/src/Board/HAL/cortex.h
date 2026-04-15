#ifndef STM32G0xx_HAL_CORTEX_H
#define STM32G0xx_HAL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g0xx_hal_def.h"

#define SYSTICK_CLKSOURCE_HCLK_DIV8       0x00000000U
#define SYSTICK_CLKSOURCE_HCLK            0x00000004U

void vCORTEX_NVICSetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void vCORTEX_NVICEnableIRQ(IRQn_Type IRQn);
void vCORTEX_NVICDisableIRQ(IRQn_Type IRQn);
void vCORTEX_NVICSystemReset(void);
uint32_t vCORTEX_SYSTICKConfig(uint32_t TicksNumb);

#endif /* CORTEX_H */



