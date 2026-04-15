#include "stm32g0xx_hal.h"

void vCORTEX_NVICSetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
  NVIC_SetPriority(IRQn, PreemptPriority);
}


void vCORTEX_NVICEnableIRQ(IRQn_Type IRQn)
{

  NVIC_EnableIRQ(IRQn);
}


void vCORTEX_NVICDisableIRQ(IRQn_Type IRQn)
{
  NVIC_DisableIRQ(IRQn);
}


void vCORTEX_NVICSystemReset(void)
{
  /* System Reset */
  NVIC_SystemReset();
}


uint32_t vCORTEX_SYSTICKConfig(uint32_t TicksNumb)
{
  return SysTick_Config(TicksNumb);
}

