/**
 * @file uart.c
 * @brief UART driver implementation for STM32G0.
 *
 * This file provides basic UART initialization, transmission,
 * and reception using direct register access (bare-metal style).
 *
 * @author
 * Jesus Daniel Britoloaiza
 *
 * @copyright
 * Copyright (c) 2026 Jesus Daniel Britoloaiza
 *
 * @note
 * This implementation is simplified and intended for learning purposes.
 * It does not include full error handling, interrupts, or DMA support.
 */

#include "defs.h"

#define UART_BRR_115200_64MHZ 0x22B
/**
 * @brief Initialize UART peripheral with basic configuration.
 *
 * @param huart Pointer to UART handle.
 * @return HAL status.
 */
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{
  /* Reset configuration */
  huart->Instance->CR1 = 0;
  huart->Instance->CR2 = 0;
  huart->Instance->CR3 = 0;

  /* Configure: 8 bits, no parity, TX + RX enabled */
  huart->Instance->CR1 =
      USART_CR1_TE |   /* Transmitter enable */
      USART_CR1_RE;    /* Receiver enable */
 
  /* Configure baudrate (ejemplo: 115200 @ 64MHz → BRR ≈ 0x22B) */
  huart->Instance->BRR = UART_BRR_115200_64MHZ;

   /* No prescaler / guard time */
  huart->Instance->GTPR = 0;

  /* Disable advanced modes */
  huart->Instance->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
  huart->Instance->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

  /* Enable USART */
  huart->Instance->CR1 |= USART_CR1_UE;

  return HAL_OK;
}

/**
 * @brief Transmit data in blocking mode using polling.
 *
 * @param huart Pointer to UART handle.
 * @param pData Pointer to data buffer.
 * @param Size Number of bytes to transmit.
 * @param Timeout Unused (kept for compatibility).
 * @return HAL status.
 */
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart,
                                    const uint8_t *pData,
                                    uint16_t Size,
                                    uint32_t Timeout)
{
  (void)Timeout; /* Unused */

  for (uint16_t i = 0; i < Size; i++)
  {
    /* Wait until transmit data register is empty */
    while (!(huart->Instance->ISR & USART_ISR_TXE_TXFNF));

    /* Write data */
    huart->Instance->TDR = pData[i];
  }

  /* Wait until transmission complete */
  while (!(huart->Instance->ISR & USART_ISR_TC));

  return HAL_OK;
}

/**
 * @brief Receive data in blocking mode using polling.
 *
 * @param huart Pointer to UART handle.
 * @param pData Pointer to data buffer.
 * @param Size Number of bytes to receive.
 * @param Timeout Unused (kept for compatibility).
 * @return HAL status.
 */
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart,
                                   uint8_t *pData,
                                   uint16_t Size,
                                   uint32_t Timeout)
{
  (void)Timeout; /* Unused */

  for (uint16_t i = 0; i < Size; i++)
  {
    /* Wait until data is received */
    while (!(huart->Instance->ISR & USART_ISR_RXNE_RXFNE));

    /* Read data */
    pData[i] = (uint8_t)(huart->Instance->RDR & 0xFF);
  }

  return HAL_OK;
}