/**
 * @file rcc.c
 * @brief RCC peripheral initialization for STM32G031 microcontroller.
 *
 * This module provides the configuration and initialization of the
 * Reset and Clock Control (RCC) peripheral required by the system.
 * It is responsible for enabling clocks for the core peripherals
 * and configuring the system clock sources used by the application.
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

#include "rcc.h"
#include "KernelInterface.h"

/* =========================================================
 * PRIVATE CONFIG
 * ========================================================= */

/**
 * @brief Timeout value used during clock stabilization loops.
 */
#define dtimeout 100U

/**
 * @brief Global RCC object instance.
 *
 * This instance represents the RCC "object" used by the system.
 */
static RCC_t rcc;

/* =========================================================
 * PRIVATE METHODS (ENCAPSULATED)
 * ========================================================= */

/**
 * @brief Configure oscillators (HSE + PLL).
 *
 * This function initializes and stabilizes the High-Speed External (HSE)
 * oscillator and configures the Phase-Locked Loop (PLL) to generate
 * the system clock.
 *
 * Steps performed:
 * - Disable HSE and wait until it is off
 * - Enable HSE and wait for readiness
 * - Apply HSI calibration
 * - Disable PLL before reconfiguration
 * - Configure PLL registers
 * - Enable PLL and wait for lock
 *
 * @param[in] self Pointer to RCC object (not used, kept for OOP consistency)
 */
static void vRCC_ConfigureOscillators(RCC_t *self)
{
    (void)self;

    uint32_t tmp = 0U;

    /* Disable HSE */
    tmp = RCC->CR;
    tmp &= ~RCC_CR_HSEON;
    RCC->CR = tmp;

    while (RCC->CR & RCC_CR_HSERDY) {}

    /* Enable HSE */
    tmp |= RCC_CR_HSEON;
    RCC->CR = tmp;

    while (!(RCC->CR & RCC_CR_HSERDY)) {}

    /* HSI calibration */
    RCC->ICSCR = 0x406FU;

    /* Disable PLL */
    tmp = RCC->CR;
    tmp &= ~RCC_CR_PLLON;
    RCC->CR = tmp;

    while (RCC->CR & RCC_CR_PLLRDY) {}

    /* Configure PLL */
    RCC->PLLCFGR = 0x73021002U;

    /* Enable PLL */
    tmp |= RCC_CR_PLLON;
    RCC->CR = tmp;

    while (!(RCC->CR & RCC_CR_PLLRDY)) {}
}

/**
 * @brief Configure system clocks.
 *
 * This function configures the system clock tree including:
 * - FLASH latency configuration
 * - AHB (HCLK) prescaler
 * - System clock source (PLL)
 * - APB prescaler
 *
 * It ensures proper synchronization and waits for clock switch completion.
 *
 * @param[in] self Pointer to RCC object (not used, kept for abstraction)
 */
static void vRCC_ConfigureClocks(RCC_t *self)
{
    (void)self;

    uint32_t tick = 0U;

    /* Configure FLASH latency */
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_0;

    while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_0)
    {
        if (++tick > dtimeout) break;
    }

    /* HCLK = SYSCLK (no prescaler) */
    RCC->CFGR &= ~RCC_CFGR_HPRE;

    /* Select PLL as system clock */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_1;

    tick = 0U;
    while ((RCC->CFGR & RCC_CFGR_SWS) != (RCC_CFGR_SW_1 << 2U))
    {
        if (++tick > dtimeout) break;
    }

    /* APB prescaler = 1 */
    RCC->CFGR &= ~RCC_CFGR_PPRE;
}

/* =========================================================
 * PUBLIC METHODS
 * ========================================================= */

/**
 * @brief Initialize RCC system.
 *
 * This function performs the complete RCC initialization sequence:
 * - Configures oscillators (HSE + PLL)
 * - Configures system clocks
 * - Clears interrupt flags
 * - Resets peripheral reset registers
 * - Enables required peripheral clocks
 *
 * After successful execution, the RCC object is marked as initialized.
 *
 * @param[in,out] self Pointer to RCC object instance
 */
void vRCC_Init(RCC_t *self)
{
    if (self == 0) return;

    vRCC_ConfigureOscillators(self);
    vRCC_ConfigureClocks(self);

    /* Reset interrupt registers */
    RCC->CIER = 0x0U;
    RCC->CIFR = 0x0U;
    RCC->CICR = 0x0U;

    /* Reset peripheral reset registers */
    RCC->IOPRSTR  = 0x0U;
    RCC->AHBRSTR  = 0x0U;
    RCC->APBRSTR1 = 0x0U;
    RCC->APBRSTR2 = 0x0U;

    /* Enable required peripherals */
    vRCC_EnablePeripherals(self);

    self->initialized = 1U;
}

/**
 * @brief Enable peripheral clocks.
 *
 * This function enables the clock signals for required peripherals:
 *
 * Enabled peripherals:
 * - GPIOA, GPIOB
 * - FLASH memory interface
 * - TIM1, TIM2, TIM3
 * - USART1
 * - ADC
 * - Power interface (PWR)
 *
 * @param[in] self Pointer to RCC object (not used internally)
 */
void vRCC_EnablePeripherals(RCC_t *self)
{
    (void)self;

    /* Enable GPIO clocks */
    RCC->IOPENR =
        (1U << 0) |  /* GPIOA */
        (1U << 1);   /* GPIOB */

    /* Enable AHB peripherals */
    RCC->AHBENR =
        (1U << 8);   /* FLASH */

    /* Enable APB1 peripherals */
    RCC->APBENR1 =
        (1U << 0) |  /* TIM2 */
        (1U << 1) |  /* TIM3 */
        (1U << 28);  /* PWR */

    /* Enable APB2 peripherals */
    RCC->APBENR2 =
        (1U << 11) | /* TIM1 */
        (1U << 14) | /* USART1 */
        (1U << 20);  /* ADC */
}

/* =========================================================
 * CALLBACK (KERNEL)
 * ========================================================= */

/**
 * @brief RCC initialization callback.
 *
 * This function is intended to be registered within the kernel
 * initialization sequence. It initializes the global RCC object
 * and configures the system clocks.
 *
 * Acts as the entry point for RCC setup during system startup.
 */
void cbRCC(void)
{
    vRCC_Init(&rcc);
}