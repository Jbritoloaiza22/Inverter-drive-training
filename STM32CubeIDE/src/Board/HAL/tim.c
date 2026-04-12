/**
 * @file tim.c
 * @brief Timer driver for TIM2 and TIM3 configuration.
 *
 * This module provides low-level initialization and control functions
 * for TIM2 and TIM3 peripherals of the STM32G031 microcontroller.
 *
 * TIM2 and TIM3 are configured as basic time base generators that
 * generate periodic update interrupts used by the application.
 *
 * @author
 * Jesus Daniel Britoloaiza
 *
 * @copyright
 * Copyright (c) 2026 Jesus Daniel Britoloaiza
 *
 * @license
 * This source code is provided for educational and research purposes.
 */

#include "tim.h"
#include "stm32g031xx.h"

#define dSINTABLESIZE 1024
#define dPI 3.14159265358979323846f
float sin_table[dSINTABLESIZE];
/* global variables */
volatile float theta = 0.0f; /* radians */
/**
 * @brief Initialize TIM2 peripheral.
 *
 * Configures TIM2 as a basic up-counter timer using the prescaler
 * and auto-reload values defined by TIM2_PRESCALER and TIM2_ARR.
 * The timer generates an update interrupt on overflow.
 */
void vTIM2_Init(void)
{
  /* Reset configuration */
  TIM2->CR1 = 0;
  TIM2->CR2 = 0;
  TIM2->SMCR = 0;
  TIM2->DIER = 0;

  /* Set prescaler */
  TIM2->PSC = TIM2_PRESCALER;

  /* Set auto reload value */
  TIM2->ARR = TIM2_ARR;

  /* Counter mode: up */
  TIM2->CR1 &= ~TIM_CR1_DIR;

  /* Clock division */
  TIM2->CR1 &= ~TIM_CR1_CKD;

  /* Enable update interrupt */
  TIM2->DIER |= TIM_DIER_UIE;

  /* Reset counter */
  TIM2->CNT = 0;

  /* Generate update event to load registers */
  TIM2->EGR = TIM_EGR_UG;
}

/**
 * @brief Start TIM2 timer.
 *
 * Enables the counter allowing TIM2 to begin counting
 * and generating periodic update events.
 */
void vTIM2_Start(void)
{
  TIM2->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief TIM2 interrupt handler routine.
 *
 * This function checks for the update interrupt flag (UIF)
 * and clears it when triggered.
 *
 * Additional application logic can be inserted inside
 * the interrupt service routine.
 */
void vTIM2_IRQHandler(void)
{
  if (TIM2->SR & TIM_SR_UIF)
  {
    TIM2->SR &= ~TIM_SR_UIF;   /* Clear update interrupt flag */
  }
  else
  {
    /* Do nothing */
  }
}

/**
 * @brief Initialize TIM3 peripheral.
 *
 * Configures TIM3 as a basic up-counter timer using the prescaler
 * and auto-reload values defined by TIM3_PRESCALER and TIM3_ARR.
 * The timer generates an update interrupt on overflow.
 */
void vTIM3_Init(void)
{
  /* Reset configuration */
  TIM3->CR1 = 0;
  TIM3->CR2 = 0;
  TIM3->SMCR = 0;
  TIM3->DIER = 0;

  /* Set prescaler */
  TIM3->PSC = TIM3_PRESCALER;

  /* Set auto reload value */
  TIM3->ARR = TIM3_ARR;

  /* Counter mode: up */
  TIM3->CR1 &= ~TIM_CR1_DIR;

  /* Clock division */
  TIM3->CR1 &= ~TIM_CR1_CKD;

  /* Enable update interrupt */
  TIM3->DIER |= TIM_DIER_UIE;

  /* Reset counter */
  TIM3->CNT = 0;

  /* Generate update event to load registers */
  TIM3->EGR = TIM_EGR_UG;
}

/**
 * @brief Start TIM3 timer.
 *
 * Enables the counter allowing TIM3 to begin counting
 * and generating periodic update events.
 */
void vTIM3_Start(void)
{
  TIM3->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief TIM3 interrupt handler routine.
 *
 * This function checks for the update interrupt flag (UIF)
 * and clears it when triggered.
 *
 * Additional application logic can be executed inside
 * this interrupt service routine.
 */
void vTIM3_IRQHandler(void)
{
  if (TIM3->SR & TIM_SR_UIF)
  {
    TIM3->SR &= ~TIM_SR_UIF;   /* Clear update interrupt flag */
  }
  else
  {
    /* Do nothing */
  }
  theta += 0.1f;
  if(theta >= 2.0f * dPI)
  {
    theta -= 2.0f * dPI;
  }


}

/**
 * @brief TIM callback function.
 *
 * Alias to TIMx_Init(), can be called as a callback or initialization routine.
 */
void cbTIM(void){
	vTIM2_Init();
	vTIM2_Start();
	vTIM3_Init();
	vTIM3_Start();
}

void vKernelInterface_TableSinInit(void)
{
  /* Initialize the sine table with precomputed values */
  /* This function can be called during system initialization if needed */
  for(uint32_t i = 0; i < dSINTABLESIZE; i++)
  {
    /* Compute sine values scaled to the desired range (e.g., 0 to 1000) */
    sin_table[i] = (int16_t)((sinf((2 * dPI * i) / dSINTABLESIZE)));
  }
}

float fKernelInterface_SineLookup(float angle)
{
  while(angle < 0)angle += 2.0f * dPI;
  while(angle >= 2.0f * dPI)angle -= 2.0f * dPI;

  int32_t index = (uint32_t)(angle * (dSINTABLESIZE / (2.0f * dPI)));
  return sin_table[index];
}
