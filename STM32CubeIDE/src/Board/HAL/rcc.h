#include "stm32g031xx.h"
#include "stm32g0xx.h"

/**
 * @brief Initialize RCC (Reset and Clock Control module)
 * @note  Configures:
 *        - HSE oscillator
 *        - HSI calibration
 *        - PLL configuration
 *        - System clocks (HCLK, APB1)
 *        - Peripheral clocks
 *        - Sleep mode clocks
 * @retval None
 */
void RCC_Init(void);

/**
 * @brief RCC oscillator callback
 * @retval None
 */
void cbRCC(void);
