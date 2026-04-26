/**
 * @file uart.h
 * @brief UART interface definitions for STM32G0.
 *
 * This header provides a simplified UART handle structure and basic
 * function prototypes for initialization, transmission, and reception.
 *
 * @author
 * Jesus Daniel Britoloaiza
 *
 * @copyright
 * Copyright (c) 2026 Jesus Daniel Britoloaiza
 *
 * @note
 * This is a abstraction layer intended for learning and low-level
 * control. It does not include full HAL features such as interrupts,
 * DMA, or advanced error handling.
 */

#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g0xx_hal_def.h"

/**
 * @brief UART handle structure.
 *
 * This structure contains the base address of the USART peripheral.
 */
typedef struct __UART_HandleTypeDef
{
  USART_TypeDef *Instance;  /*!< UART registers base address */
} UART_HandleTypeDef;

/**
 * @brief Initialize the UART peripheral.
 *
 * @param huart Pointer to a UART handle structure.
 * @return HAL status.
 */
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);

/**
 * @brief Transmit data over UART in blocking mode.
 *
 * @param huart Pointer to a UART handle structure.
 * @param pData Pointer to data buffer.
 * @param Size Number of bytes to transmit.
 * @param Timeout Timeout duration.
 * @return HAL status.
 */
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart,
                                    const uint8_t *pData,
                                    uint16_t Size,
                                    uint32_t Timeout);

/**
 * @brief Receive data over UART in blocking mode.
 *
 * @param huart Pointer to a UART handle structure.
 * @param pData Pointer to data buffer.
 * @param Size Number of bytes to receive.
 * @param Timeout Timeout duration.
 * @return HAL status.
 */
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart,
                                   uint8_t *pData,
                                   uint16_t Size,
                                   uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* UART_H */