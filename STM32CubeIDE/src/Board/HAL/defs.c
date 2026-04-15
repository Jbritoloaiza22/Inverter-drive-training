#include "defs.h"
__IO uint32_t uwTick;
uint32_t uwTickPrio = (1UL << __NVIC_PRIO_BITS); /* Invalid PRIO */
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;  /* 1KHz */
HAL_StatusTypeDef HAL_Init(void)
{
  HAL_StatusTypeDef  status = HAL_OK;
  if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
  }

  return status;
}

__weak HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  HAL_StatusTypeDef  status = HAL_OK;

  if ((uint32_t)uwTickFreq != 0U)
  {
    if (vCORTEX_SYSTICKConfig(SystemCoreClock / (1000U /(uint32_t)uwTickFreq)) == 0U)
    {
      if (TickPriority < (1UL << __NVIC_PRIO_BITS))
      {
        vCORTEX_NVICSetPriority(SysTick_IRQn, TickPriority, 0U);
        uwTickPrio = TickPriority;
      }
      else
      {
        status = HAL_ERROR;
      }
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
}
__weak void HAL_IncTick(void)
{
  uwTick += (uint32_t)uwTickFreq;
}
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}
