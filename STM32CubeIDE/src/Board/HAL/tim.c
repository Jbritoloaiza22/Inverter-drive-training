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
 * GLOBAL TIMER OBJECTS
 * ========================================================= */

/**
 * @brief Timer object for TIM2.
 */
Timer_t tim2;

/**
 * @brief Timer object for TIM3.
 */
Timer_t tim3;

/* =========================================================
 * INIT
 * ========================================================= */

/**
 * @brief Initialize a timer instance.
 *
 * This function configures a hardware timer and associates it
 * with a Timer_t object.
 *
 * Configuration includes:
 * - Prescaler (PSC)
 * - Auto-reload register (ARR)
 * - Counter mode (up-counting)
 * - Interrupt enable (update event)
 *
 * @param[in,out] self Pointer to Timer object
 * @param[in] instance Pointer to TIM peripheral (TIM2, TIM3, etc.)
 * @param[in] psc Prescaler value
 * @param[in] arr Auto-reload value (period)
 */
void Timer_Init(Timer_t *self, TIM_TypeDef *instance,
                uint32_t psc, uint32_t arr)
{
    self->instance = instance;
    self->psc = psc;
    self->arr = arr;
    self->enabled = 0U;

    /* Reset timer configuration */
    instance->CR1  = 0U;
    instance->CR2  = 0U;
    instance->SMCR = 0U;
    instance->DIER = 0U;

    /* Set timing parameters */
    instance->PSC = psc;
    instance->ARR = arr;

    /* Configure counter mode: up-counting */
    instance->CR1 &= ~TIM_CR1_DIR;

    /* No clock division */
    instance->CR1 &= ~TIM_CR1_CKD;

    /* Enable update interrupt */
    instance->DIER |= TIM_DIER_UIE;

    /* Reset counter */
    instance->CNT = 0U;

    /* Generate update event to apply configuration */
    instance->EGR = TIM_EGR_UG;
}

/* =========================================================
 * START / STOP
 * ========================================================= */

/**
 * @brief Start timer.
 *
 * Enables the timer counter and begins counting.
 *
 * @param[in,out] self Pointer to Timer object
 */
void Timer_Start(Timer_t *self)
{
    self->instance->CR1 |= TIM_CR1_CEN;
    self->enabled = 1U;
}

/**
 * @brief Stop timer.
 *
 * Disables the timer counter.
 *
 * @param[in,out] self Pointer to Timer object
 */
void Timer_Stop(Timer_t *self)
{
    self->instance->CR1 &= ~TIM_CR1_CEN;
    self->enabled = 0U;
}

/* =========================================================
 * IRQ HANDLING
 * ========================================================= */

/**
 * @brief Clear timer interrupt flag.
 *
 * Checks if the update interrupt flag (UIF) is set and clears it.
 *
 * This function should be called inside the ISR handler.
 *
 * @param[in,out] self Pointer to Timer object
 */
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

/**
 * @brief Timer initialization callback.
 *
 * This function is intended to be called by the KernelInterface
 * during system initialization.
 *
 * It initializes and starts:
 * - TIM2 (e.g. fast control loop)
 * - TIM3 (e.g. slower tasks)
 *
 * Timer configuration:
 * - TIM2: PSC = 63, ARR = 249
 * - TIM3: PSC = 63, ARR = 999
 */
void cbTIM(void)
{
    Timer_Init(&tim2, TIM2, 63U, 249U);
    Timer_Init(&tim3, TIM3, 63U, 999U);

    Timer_Start(&tim2);
    Timer_Start(&tim3);
}