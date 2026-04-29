/**
 * @file uart.h
 * @brief UART driver interface for STM32G0.
 *
 * This module provides a low-level UART driver following OOP patterns
 * for initialization, transmission, and reception using direct register
 * access .
 *
 * @author
 * Jesus Daniel Britoloaiza
 *
 * @copyright
 * Copyright (c) 2026 Jesus Daniel Britoloaiza
 *
 * @note
 * This is a abstraction layer intended for learning and
 * low-level control. It does not include full HAL features such as
 * interrupts, DMA, or advanced error handling.
 */

#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g031xx.h"
#include <stdint.h>

/* =========================================================
 * CONFIGURATION MACROS
 * ========================================================= */

/**
 * @brief UART baud rate setting for 115200 bps @ 64 MHz clock.
 */
#define dUART_BRR_115200_64MHZ 0x22B

/**
 * @brief Logical ON value.
 */
#define dOn 1U

/**
 * @brief Logical OFF value.
 */
#define dOff 0U

/* =========================================================
 * UART OBJECT
 * ========================================================= */

/**
 * @brief UART object structure.
 *
 * Encapsulates UART peripheral configuration and runtime state.
 *
 * @note This is a lightweight abstraction over STM32 USART peripherals.
 */
typedef struct {
  /**
   * @brief Pointer to hardware UART instance.
   *
   * Example:
   * - USART1
   * - USART2
   * - LPUART1
   */
  USART_TypeDef *Instance;

  /**
   * @brief Baud rate configuration value (BRR register).
   *
   * Depends on system clock frequency.
   */
  uint32_t BaudRate;

  /**
   * @brief Runtime enable flag.
   *
   * - 0: UART disabled
   * - 1: UART enabled
   */
  uint8_t enabled;

} UART_t;

/* =========================================================
 * PUBLIC API
 * ========================================================= */

/**
 * @brief Global UART object instance.
 *
 * This instance represents the UART "object" used by the system.
 * Initialized via cbUART() callback.
 *
 * @note Declared as extern for access from other modules.
 */
extern UART_t uart1;

/**
 * @brief Initialize UART peripheral.
 *
 * Configures the UART with:
 * - 8 bits data, no parity, 1 stop bit
 * - TX and RX enabled
 * - Specified baud rate
 * - Polling-based operation (no interrupts)
 *
 * @param[in,out] self Pointer to UART object instance
 * @param[in] Instance UART peripheral base (USART1, USART2, etc.)
 * @param[in] BaudRate Baud rate configuration (BRR value)
 */
void vUART_Init(UART_t *self, USART_TypeDef *Instance, uint32_t BaudRate);

/**
 * @brief Transmit data in blocking mode using polling.
 *
 * Waits until each byte is transmitted before sending the next.
 * This is a synchronous, blocking operation.
 *
 * @param[in,out] self Pointer to UART object instance
 * @param[in] pData Pointer to data buffer to transmit
 * @param[in] Size Number of bytes to transmit
 *
 * @return Number of bytes successfully transmitted
 */
uint16_t vUART_Transmit(UART_t *self, const uint8_t *pData, uint16_t Size);

/**
 * @brief Receive data in blocking mode using polling.
 *
 * Waits until each byte is received before reading the next.
 * This is a synchronous, blocking operation.
 *
 * @param[in,out] self Pointer to UART object instance
 * @param[out] pData Pointer to buffer for received data
 * @param[in] Size Maximum number of bytes to receive
 *
 * @return Number of bytes successfully received
 */
uint16_t vUART_Receive(UART_t *self, uint8_t *pData, uint16_t Size);

#ifdef __cplusplus
}
#endif

#endif /* __UART_H */