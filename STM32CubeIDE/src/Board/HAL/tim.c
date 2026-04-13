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
#include "KernelInterface.h"
/* =========================================================
 * INIT
 * ========================================================= */

/**
 * @brief Initializes a timer instance.
 *
 * Configures hardware registers and stores configuration
 * inside the object.
 */
void Timer_Init(Timer_t *self, TIM_TypeDef *instance,
                uint32_t psc, uint32_t arr)
{
    self->instance = instance;
    self->psc = psc;
    self->arr = arr;
    self->enabled = 0;

    /* Reset timer */
    instance->CR1 = 0;
    instance->CR2 = 0;
    instance->SMCR = 0;
    instance->DIER = 0;

    instance->PSC = psc;
    instance->ARR = arr;

    instance->CR1 &= ~TIM_CR1_DIR;  /* upcounter */
    instance->CR1 &= ~TIM_CR1_CKD;

    instance->DIER |= TIM_DIER_UIE; /* interrupt enable */

    instance->CNT = 0;
    instance->EGR = TIM_EGR_UG;
}

/* =========================================================
 * START / STOP
 * ========================================================= */

void Timer_Start(Timer_t *self)
{
    self->instance->CR1 |= TIM_CR1_CEN;
    self->enabled = 1;
}

void Timer_Stop(Timer_t *self)
{
    self->instance->CR1 &= ~TIM_CR1_CEN;
    self->enabled = 0;
}

/* =========================================================
 * IRQ HANDLING
 * ========================================================= */

void Timer_ClearIRQ(Timer_t *self)
{
    if (self->instance->SR & TIM_SR_UIF)
    {
        self->instance->SR &= ~TIM_SR_UIF;
    }
}

/* =========================================================
 * CALLBACK (KERNEL LAYER)
 * ========================================================= */

Timer_t tim2;
Timer_t tim3;

/**
 * @brief Initializes system timers (TIM2 + TIM3).
 *
 * OOP-style kernel callback initializer.
 */
void cbTIM(void)
{
    Timer_Init(&tim2, TIM2, 63, 249);
    Timer_Init(&tim3, TIM3, 63, 999);

    Timer_Start(&tim2);
    Timer_Start(&tim3);
}