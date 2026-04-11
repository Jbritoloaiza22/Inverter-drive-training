#include "tim.h"
#include "stm32g031xx.h"

void TIM_Init(void)
{
  // Enable TIM2 and TIM3 clocks
  RCC->APBENR1 |= RCC_APBENR1_TIM2EN | RCC_APBENR1_TIM3EN;

  // Configure TIM2
  TIM2->CR1 = 0;
  TIM2->CR2 = 0;
  TIM2->SMCR = 0;
  TIM2->DIER = TIM_DIER_UIE;
  TIM2->PSC = 63;
  TIM2->ARR = 249;
  TIM2->CNT = 0;
  TIM2->EGR = TIM_EGR_UG;

  // Configure TIM3
  TIM3->CR1 = 0;
  TIM3->CR2 = 0;
  TIM3->SMCR = 0;
  TIM3->DIER = TIM_DIER_UIE;
  TIM3->PSC = 63;
  TIM3->ARR = 999;
  TIM3->CNT = 0;
  TIM3->EGR = TIM_EGR_UG;
}

void TIM_Start(void)
{
  TIM2->CR1 |= TIM_CR1_CEN;
  TIM3->CR1 |= TIM_CR1_CEN;
}
