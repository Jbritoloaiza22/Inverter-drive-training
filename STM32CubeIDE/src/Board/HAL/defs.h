/**
  ******************************************************************************
  * @file    stm32g0xx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics. 
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G0xx_HAL_H
#define STM32G0xx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal_adc.h"
#include "stm32g0xx_hal_adc_ex.h"
#include "stm32g0xx_hal_uart.h"

#include "cortex.h"
#define  TICK_INT_PRIORITY            3U /*!< tick interrupt priority */
#define HSI_VALUE    (16000000UL)            /*!< Value of the Internal oscillator in Hz*/
#define LSE_VALUE    (32768UL)               /*!< Value of the External oscillator in Hz*/
void assert_failed(uint8_t *file, uint32_t line);


typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;


HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
void HAL_IncTick(void);
uint32_t HAL_GetTick(void);

#ifdef __cplusplus
}
#endif

#endif /* STM32G0xx_HAL_H */


