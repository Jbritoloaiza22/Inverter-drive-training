#include "rcc.h"
#include "KernelInterface.h"
#define FLASH_LATENCY_0                 0x00000000UL        /*!< FLASH Zero wait state */
#define FLASH_LATENCY_1                 FLASH_ACR_LATENCY_0 /*!< FLASH One wait state */
#define FLASH_LATENCY_2                 FLASH_ACR_LATENCY_1 /*!< FLASH Two wait states */
#define RCC_SYSCLKSOURCE_HSI           0x00000000U                       /*!< HSI selection as system clock */
#define RCC_SYSCLKSOURCE_HSE           RCC_CFGR_SW_0                     /*!< HSE selection as system clock */
#define RCC_SYSCLKSOURCE_PLLCLK        RCC_CFGR_SW_1                     /*!< PLL selection as system clock */
#define RCC_SYSCLKSOURCE_LSI           (RCC_CFGR_SW_1 | RCC_CFGR_SW_0)   /*!< LSI selection as system clock */
#define RCC_SYSCLKSOURCE_LSE           RCC_CFGR_SW_2                     /*!< LSE selection as system clock */
#define RCC_SYSCLK_DIV1                0x00000000U                                                             /*!< SYSCLK not divided */
#define RCC_HCLK_DIV1                  0x00000000U                                           /*!< HCLK not divided */

/**
 * @brief  Configures RCC oscillators (optimized, no parameters needed)
 * @retval None
 * @note   Optimized implementation for STM32G031 - predefined configuration
 */
static void RCC_ConfigureOscillators(void)
{
    uint32_t tmp_reg = 0U;
    
    /* HSE configuration - Enable HSE */
    tmp_reg = RCC->CR;
    tmp_reg &= ~RCC_CR_HSEON;  /* Disable HSE first */
    RCC->CR = tmp_reg;
    
    /* Wait for HSE to disable */
    while ((RCC->CR & RCC_CR_HSERDY) != 0U) {}
    
    /* Enable HSE */
    tmp_reg |= RCC_CR_HSEON;
    RCC->CR = tmp_reg;
    
    /* Wait for HSE to be stable */
    while ((RCC->CR & RCC_CR_HSERDY) == 0U) {}
    
    /* HSI configuration - Calibration */
    RCC->ICSCR = 0x406fU;  /* HSI calibration value */
    
    /* PLL configuration - Predefined for STM32G031 */
    tmp_reg = RCC->CR;
    tmp_reg &= ~RCC_CR_PLLON;  /* Disable PLL */
    RCC->CR = tmp_reg;
    
    /* Wait for PLL to be unlocked */
    while ((RCC->CR & RCC_CR_PLLRDY) != 0U) {}
    
    /* Configure PLL */
    RCC->PLLCFGR = 0x73021002U;  /* Predefined PLL configuration */
    
    /* Enable PLL */
    tmp_reg |= RCC_CR_PLLON;
    RCC->CR = tmp_reg;
    
    /* Wait for PLL to be stable */
    while ((RCC->CR & RCC_CR_PLLRDY) == 0U) {}
}

/**
 * @brief  Configure RCC clocks (optimized, no parameters needed)
 * @retval None
 * @note   Optimized implementation for STM32G031 - predefined configuration
 */
static void RCC_ConfigureClocks(void)
{
    uint32_t tickstart;
    
    /* Set FLASH latency for system clock speed */
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_LATENCY_1;
    
    /* Wait for latency setting */
    tickstart = 0U;
    while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_LATENCY_1)
    {
        if (++tickstart > 100U) break;
    }
    
    /* Set HCLK divider - No division */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_SYSCLK_DIV1);
    
    /* Select PLL as system clock source */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_SYSCLKSOURCE_PLLCLK);
    
    /* Wait for clock switch to complete */
    tickstart = 0U;
    while ((RCC->CFGR & RCC_CFGR_SWS) != (RCC_SYSCLKSOURCE_PLLCLK << 2U))
    {
        if (++tickstart > 100U) break;
    }
    
    /* Set APB1 prescaler - No division */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, RCC_HCLK_DIV1);
}

void RCC_Init(void)
{
    /* Configure oscillators */
    RCC_ConfigureOscillators();
    
    /* Configure clocks */
    RCC_ConfigureClocks();
    
    /* Clear and initialize interrupt flags */
    RCC->CIER   = 0x0U;  /* Disable all interrupts */
    RCC->CIFR   = 0x0U;  /* Clear interrupt flags */
    RCC->CICR   = 0x0U;  /* Clear interrupt causes */
    
    /* Reset all reset registers */
    RCC->IOPRSTR  = 0x0U;
    RCC->AHBRSTR  = 0x0U;
    RCC->APBRSTR1 = 0x0U;
    RCC->APBRSTR2 = 0x0U;
    
    /* Enable clocks for peripherals */
    RCC->IOPENR   = 0x3U;        /* GPIO A and B */
    RCC->AHBENR   = 0x100U;      /* DMA */
    RCC->APBENR1  = 0x18000003U; /* USART1, TIM2, TIM3 */
    RCC->APBENR2  = 0x104801U;   /* ADC, TIM1, SYSCFG */
    
    /* Sleep mode clock enables */
    RCC->IOPSMENR   = 0x2fU;       /* GPIO */
    RCC->AHBSMENR   = 0x51301U;    /* DMA, SRAM, Flash */
    RCC->APBSMENR1  = 0xd8724c03U; /* Peripherals */
    RCC->APBSMENR2  = 0x400000U;   /* ADC */
    
    /* Backup domain control */
    RCC->BDCR = 0x0U;
    
    /* Control and status register */
    RCC->CSR = 0xc000000U;
}

void cbRCC(void){
    RCC_Init();
}
