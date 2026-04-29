/**
 * @file uart.c
 * @brief UART driver implementation for STM32G0 (OOP style).
 *
 * This module provides low-level UART configuration and communication
 * using direct register access (bare-metal style) following object-oriented
 * patterns in C.
 *
 * Supports basic polling-based transmission and reception. Does not include
 * interrupts, DMA, or advanced error handling.
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

#include "uart.h"
#include "KernelInterface.h"

/* =========================================================
 * GLOBAL STATE
 * ========================================================= */

/**
 * @brief Global UART object instance.
 *
 * This instance represents the UART "object" used by the system.
 * Declared as global to be accessible via extern declaration.
 */
UART_t uart1;

/* =========================================================
 * INIT
 * ========================================================= */

/**
 * @brief Initialize UART peripheral with basic configuration.
 *
 * Configures the UART with:
 * - 8 bits data
 * - No parity
 * - 1 stop bit
 * - TX and RX enabled
 * - Specified baud rate
 * - Polling-based operation
 *
 * Disables advanced modes such as:
 * - LIN mode
 * - Clock output
 * - Smartcard mode
 * - Half-duplex mode
 * - IrDA mode
 *
 * @param[in,out] self Pointer to UART object instance
 * @param[in] Instance UART peripheral base address (USART1, USART2, etc.)
 * @param[in] BaudRate Baud rate configuration (BRR register value)
 */
void vUART_Init(UART_t *self, USART_TypeDef *Instance, uint32_t BaudRate) {
  self->Instance = Instance;
  self->BaudRate = BaudRate;
  self->enabled = 0U;

  /* Reset configuration */
  Instance->CR1 = 0U;
  Instance->CR2 = 0U;
  Instance->CR3 = 0U;

  /* Configure: 8 bits, no parity, TX + RX enabled, NO INTERRUPTS YET */
  Instance->CR1 = USART_CR1_TE | /* Transmitter enable */
                  USART_CR1_RE;  /* Receiver enable */

  /* Configure baudrate */
  Instance->BRR = BaudRate;

  /* No prescaler / guard time */
  Instance->GTPR = 0U;

  /* Disable advanced modes */
  Instance->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
  Instance->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

  /* Enable USART */
  Instance->CR1 |= USART_CR1_UE | USART_CR1_RXNEIE_RXFNEIE;
  self->enabled = 1U;
}

/* =========================================================
 * TRANSMIT / RECEIVE
 * ========================================================= */

/**
 * @brief Transmit data in blocking mode using polling.
 *
 * Polls the TXE (Transmit Data Register Empty) flag to ensure each
 * byte can be safely written before transmission. After all bytes
 * are written, waits for TC (Transmission Complete) flag.
 *
 * This is a synchronous, blocking operation.
 *
 * @param[in,out] self Pointer to UART object instance
 * @param[in] pData Pointer to data buffer to transmit
 * @param[in] Size Number of bytes to transmit
 *
 * @return Number of bytes successfully transmitted (equals Size on success)
 */
uint16_t vUART_Transmit(UART_t *self, const uint8_t *pData, uint16_t Size) {
  uint16_t ui16Transmitted = 0U;

  for (uint16_t i = 0U; i < Size; i++) {
    /* Wait until transmit data register is empty */
    while (!(self->Instance->ISR & USART_ISR_TXE_TXFNF)) {
      /* Polling */
    }

    /* Write data */
    self->Instance->TDR = pData[i];
    ui16Transmitted++;
  }

  /* Wait until transmission complete */
  while (!(self->Instance->ISR & USART_ISR_TC)) {
    /* Polling */
  }

  return ui16Transmitted;
}

/**
 * @brief Receive data in blocking mode using polling.
 *
 * Polls the RXNE (Receive Data Register Not Empty) flag to wait for
 * incoming data. Once data is available, reads it from the RDR register.
 *
 * This is a synchronous, blocking operation.
 *
 * @param[in,out] self Pointer to UART object instance
 * @param[out] pData Pointer to buffer for received data
 * @param[in] Size Maximum number of bytes to receive
 *
 * @return Number of bytes successfully received
 */
uint16_t vUART_Receive(UART_t *self, uint8_t *pData, uint16_t Size) {
  uint16_t ui16Received = 0U;

  for (uint16_t i = 0U; i < Size; i++) {
    /* Wait until data is received */
    while (!(self->Instance->ISR & USART_ISR_RXNE_RXFNE)) {
      /* Polling */
    }

    /* Read data */
    pData[i] = (uint8_t)(self->Instance->RDR & 0xFFU);
    ui16Received++;
  }

  return ui16Received;
}

/* =========================================================
 * CALLBACK (KERNEL LAYER)
 * ========================================================= */

/**
 * @brief UART initialization callback.
 *
 * This function is intended to be used by the KernelInterface
 * as part of the system initialization sequence.
 *
 * It initializes the UART object with default parameters suitable
 * for system communication (115200 bps @ 64 MHz clock).
 */
void cbUART(void) {
  vUART_Init(&uart1, USART1, dUART_BRR_115200_64MHZ);

  /* Test transmission to verify UART is working */
  uint8_t test_msg[] = "UART initialized successfully\r\n";
  vUART_Transmit(&uart1, test_msg, sizeof(test_msg) - 1);
}