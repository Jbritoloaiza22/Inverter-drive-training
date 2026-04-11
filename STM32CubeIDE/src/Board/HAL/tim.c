#include "tim.h"
#include "stm32g031xx.h"

void TIM_Init(void)
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
	  TIM2->PSC = 63;

	  /* Set auto reload */
	  TIM2->ARR = 249;

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

void TIM_Start(void)
{
  TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler_TIM(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;   // limpiar flag

        cbPWM();                  // tu callback
    }
}
