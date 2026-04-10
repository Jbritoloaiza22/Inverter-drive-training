/**
 * @file rcc.c
 * @brief RCC peripheral initialization for STM32G031 microcontroller
 * @author Jesus Daniel Britoloaiza
 */

#include "rcc.h"
#include "KernelInterface.h"

#define dtimeout 100U
/**
 * @brief  Configures RCC oscillators (optimized, no parameters needed)
 * @retval None
 * @note   Optimized implementation for STM32G031 - predefined configuration
 * @author Jesus Daniel Britoloaiza
 */
static void RCC_ConfigureOscillators(void)
{
    uint32_t ui32tmp_reg = 0U;
    
    /* HSE configuration - Enable HSE */
    ui32tmp_reg = RCC->CR;
    ui32tmp_reg &= ~RCC_CR_HSEON;  /* Disable HSE first */
    RCC->CR = ui32tmp_reg;
    
    /* Wait for HSE to disable */
    while ((RCC->CR & RCC_CR_HSERDY)) {}
    
    /* Enable HSE */
    ui32tmp_reg |= RCC_CR_HSEON;
    RCC->CR = ui32tmp_reg;
    
    /* Wait for HSE to be stable */
    while (!(RCC->CR & RCC_CR_HSERDY)) {}
    
    /* HSI configuration - Calibration */
    RCC->ICSCR = 0x406fU;  /* HSI calibration value */
    
    /* PLL configuration - Predefined for STM32G031 */
    ui32tmp_reg = RCC->CR;
    ui32tmp_reg &= ~RCC_CR_PLLON;  /* Disable PLL */
    RCC->CR = ui32tmp_reg;
    
    /* Wait for PLL to be unlocked */
    while ((RCC->CR & RCC_CR_PLLRDY)) {}
    
    /* Configure PLL */
    RCC->PLLCFGR = 0x73021002U;  /* Predefined PLL configuration */
    
    /* Enable PLL */
    ui32tmp_reg |= RCC_CR_PLLON;
    RCC->CR = ui32tmp_reg;
    
    /* Wait for PLL to be stable */
    while (!(RCC->CR & RCC_CR_PLLRDY)) {}
}

/**
 * @brief  Configure RCC clocks (optimized, no parameters needed)
 * @retval None
 * @note   Optimized implementation for STM32G031 - predefined configuration
 */
static void RCC_ConfigureClocks(void)
{
    uint32_t ui32tickstart;
    
    /* Set FLASH latency for system clock speed */
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_0;
    
    /* Wait for latency setting */
    ui32tickstart = 0U;
    while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_0)
    {
        if (++ui32tickstart > dtimeout) 
        {
            break;
        }
        else
        {
            /* nothing to do */
        }

    }
    
    /* Set HCLK divider - No division */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_HPRE) | 0x0U;
    
    /* Select PLL as system clock source */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_1;
    
    /* Wait for clock switch to complete */
    ui32tickstart = 0U;
    while ((RCC->CFGR & RCC_CFGR_SWS) != (RCC_CFGR_SW_1 << 2U))
    {
        if (++ui32tickstart > dtimeout) 
        {
            break;
        }
        else
        {
            /* nothing to do */
        }
    }
    
    /* Set APB1 prescaler - No division */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_PPRE) | 0x0U;
}

/**
 * @brief  Initializes the Reset and Clock Control (RCC) peripheral
 * @retval None
 * @note   Configures oscillators, clocks, peripheral clock enables, sleep modes,
 *         interrupt flags, reset registers, backup domain, and control/status registers
 *         for STM32G031 microcontroller with predefined configuration.
 */
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
    RCC->IOPENR = (
        /* GPIO_A_CLOCK_EN */ dRCC_IOPENR_GPIOAEN(dOn)       |
        /* GPIO_B_CLOCK_EN */ dRCC_IOPENR_GPIOBEN(dOn)       |
        /* GPIO_C_CLOCK_EN */ dRCC_IOPENR_GPIOCEN(dOff)      |
        /* GPIO_D_CLOCK_EN */ dRCC_IOPENR_GPIODEN(dOff)      |
        /* GPIO_E_CLOCK_EN */ dRCC_IOPENR_GPIOEEN(dOff)      |
        /* GPIO_F_CLOCK_EN */ dRCC_IOPENR_GPIOFEN(dOff)
    );

    /* Enable AHB peripheral clock enable register */
    RCC->AHBENR = (
        /* DMA1_CLOCK_EN */   dRCC_AHBENR_DMA1EN(dOff)       |
        /* DMA2_CLOCK_EN */   dRCC_AHBENR_DMA2EN(dOff)       |
        /* FLASH_CLOCK_EN */  dRCC_AHBENR_FLASHEN(dOn)       |
        /* CRC_CLOCK_EN */    dRCC_AHBENR_CRCEN(dOff) 
    );

    /* APB peripheral clock enable register */
    RCC->APBENR1 = (
        /* TIM2_CLOCK_EN */   dRCC_APBENR1_TIM2EN(dOn)        |
        /* TIM3_CLOCK_EN */   dRCC_APBENR1_TIM3EN(dOn)        |
        /* TIM4_CLOCK_EN */   dRCC_APBENR1_TIM4EN(dOff)       |
        /* TIM6_CLOCK_EN */   dRCC_APBENR1_TIM6EN(dOff)       |
        /* TIM7_CLOCK_EN */   dRCC_APBENR1_TIM7EN(dOff)       |
        /* RTCAPB_CLOCK_EN */ dRCC_APBENR1_RTCAPBEN(dOff)     |
        /* WWDG_CLOCK_EN */   dRCC_APBENR1_WWDGEN(dOff)       |
        /* SPI2EN */          dRCC_APBENR1_SPI2EN(dOff)       |
        /* USART2EN */        dRCC_APBENR1_USART2EN(dOff)     |
        /* LPUART1EN */       dRCC_APBENR1_LPUART1EN(dOff)    |
        /* I2C1EN */          dRCC_APBENR1_I2C1EN(dOff)       |
        /* I2C2EN */          dRCC_APBENR1_I2C2EN(dOff)       |
        /* DBGEN */           dRCC_APBENR1_DBGEN(dOn)         |
        /* PWREN */           dRCC_APBENR1_PWREN(dOn)         |
        /* LPTIM2EN */        dRCC_APBENR1_LPTIM2EN(dOff)     |
        /* LPTIM1EN */        dRCC_APBENR1_LPTIM1EN(dOff)

    );
    RCC->APBENR2  = (
        /* SYSCFGEN */        dRCC_APBENR2_SYSCFGEN(dOn)      |
        /* TIM1EN*/           dRCC_APBENR2_TIM1EN(dOn)        |  
        /* ADCEN */           dRCC_APBENR2_SPI1EN(dOff)       |
        /* USART1EN */        dRCC_APBENR2_USART1EN(dOn)      |
        /* TIM14EN */         dRCC_APBENR2_TIM14EN(dOff)      |
        /* TIM16EN */         dRCC_APBENR2_TIM16EN(dOff)      |
        /* TIM17EN */         dRCC_APBENR2_TIM17EN(dOff)      |      
        /* ADCEN */           dRCC_APBENR2_ADCEN(dOn)
    );   
    
    /* Sleep mode clock enables */
    RCC->IOPSMENR = (
        /* GPIOAEN */         dRCC_IOPSMENR_GPIOASMEN(dOn)     | 
        /* GPIOBEN */         dRCC_IOPSMENR_GPIOBSMEN(dOn)     |  
        /* GPIOCEN */         dRCC_IOPSMENR_GPIOCSMEN(dOff)    |  
        /* GPIODEN */         dRCC_IOPSMENR_GPIODSMEN(dOff)    |  
        /* GPIOFEN */         dRCC_IOPSMENR_GPIOFSMEN(dOff)    
    );       

    /* AHB sleep mode clock enable register */
    RCC->AHBSMENR = (
        /* DMA1EN */         dRCC_AHBSMENR_DMA1SMEN(dOff)      | 
        /* DMA2EN */         dRCC_AHBSMENR_DMA2SMEN(dOff)      |   
        /* FLASHEN */        dRCC_AHBSMENR_FLASHSMEN(dOff)     |  
        /* SRAMEN */         dRCC_AHBSMENR_SRAMSMEN(dOff)      |  
        /* CRCEN */          dRCC_AHBSMENR_CRCSMEN(dOff)      
    );  

    /* APB sleep mode clock enable register 1 */
    RCC->APBSMENR1 = (
        /* TIM2EN */          dRCC_APBSMENR1_TIM2SMEN(dOn)     |   
        /* TIM3EN */          dRCC_APBSMENR1_TIM3SMEN(dOn)     |  
        /* RTCAPBEN */        dRCC_APBSMENR1_RTCAPBSMEN(dOff)  |  
        /* WWDGEN */          dRCC_APBSMENR1_WWDGSMEN(dOff)    |  
        /* SPI2EN */          dRCC_APBSMENR1_SPI2SMEN(dOff)    |  
        /* USART2EN */        dRCC_APBSMENR1_USART2SMEN(dOff)  |  
        /* LPUART1EN */       dRCC_APBSMENR1_LPUART1SMEN(dOff) |  
        /* I2C1EN */          dRCC_APBSMENR1_I2C1SMEN(dOff)    |  
        /* I2C2EN */          dRCC_APBSMENR1_I2C2SMEN(dOff)    |  
        /* DebugEN */         dRCC_APBSMENR1_DBGSMEN(dOff)     |  
        /* PWREN */           dRCC_APBSMENR1_PWRSMEN(dOff)     |  
        /* LPTIM2EN */        dRCC_APBSMENR1_LPTIM2SMEN(dOff)  |  
        /* LPTIM1EN */        dRCC_APBSMENR1_LPTIM1SMEN(dOff)   
    ); 

    /* APB sleep mode clock enable register 2 */
    RCC->APBSMENR2 =(
        /* ADCEN */          dRCC_APBSMENR2_ADCSMEN(dOff)     |  
        /*TIM1SMEN*/         dRCC_APBSMENR2_TIM1SMEN(dOff)    |  
        /* SYSCFGEN */       dRCC_APBSMENR2_SPI1SMEN(dOff)    |  
        /*USART1SMEN*/       dRCC_APBSMENR2_USART1SMEN(dOff)  |
        /*TIM14SMEN*/        dRCC_APBSMENR2_TIM14SMEN(dOff)   |
        /*TIM16SMEN*/        dRCC_APBSMENR2_TIM16SMEN(dOff)   |
        /*TIM17SMEN*/        dRCC_APBSMENR2_TIM17SMEN(dOff)   |
        /*ADCSMEN*/          dRCC_APBSMENR2_ADCSMEN(dOn)
    );
    
    /* Backup domain control */
    RCC->BDCR = 0x0U;
    
    /* Control and status register */
    RCC->CSR = 0xc000000U;
}

void cbRCC(void){
    RCC_Init();
}
