#include "tim.h"
#include "stm32g031xx.h"

void TIM2_Init(void)
{
	  /* Enable TIM2 and TIM3 clocks */
	  RCC->APBENR1 |= RCC_APBENR1_TIM2EN | RCC_APBENR1_TIM3EN;

	  /* ---------------- TIM2 ---------------- */

	  /* Reset configuration */
	  TIM2->CR1 = 0;
	  TIM2->CR2 = 0;
	  TIM2->SMCR = 0;
	  TIM2->DIER = 0;

	  /* Set prescaler */
	  TIM2->PSC = TIM2_PRESCALER;

	  /* Set auto reload */
	  TIM2->ARR = TIM2_ARR;

	  /* Counter mode up */
	  TIM2->CR1 &= ~TIM_CR1_DIR;

	  /* Clock division */
	  TIM2->CR1 &= ~TIM_CR1_CKD;

	  /* Enable update interrupt */
	  TIM2->DIER |= TIM_DIER_UIE;

	  /* Reset counter */
	  TIM2->CNT = 0;

	  /* Generate update event (load registers) */
	  TIM2->EGR = TIM_EGR_UG;

}

void TIM2_Start(void)
{
  TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler_TIM(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;   // limpiar flag

    }
}

void TIM3_Init(void)
{
	  /* Enable TIM2 and TIM3 clocks */
	  RCC->APBENR1 |= RCC_APBENR1_TIM2EN | RCC_APBENR1_TIM3EN;

	  /* ---------------- TIM3 ---------------- */

	  /* Reset configuration */
	  TIM3->CR1 = 0;
	  TIM3->CR2 = 0;
	  TIM3->SMCR = 0;
	  TIM3->DIER = 0;

	  /* Set prescaler */
	  TIM3->PSC = TIM3_PRESCALER;

	  /* Set auto reload */
	  TIM3->ARR = TIM3_ARR;

	  /* Counter mode up */
	  TIM3->CR1 &= ~TIM_CR1_DIR;

	  /* Clock division */
	  TIM3->CR1 &= ~TIM_CR1_CKD;

	  /* Enable update interrupt */
	  TIM3->DIER |= TIM_DIER_UIE;

	  /* Reset counter */
	  TIM3->CNT = 0;

	  /* Generate update event (load registers) */
	  TIM3->EGR = TIM_EGR_UG;

}

void TIM3_Start(void)
{
  TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM3_IRQHandler_TIM(void)
{
    if (TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;   // limpiar flag

    }
}

