#include "defs.h"

HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{
 huart->Instance->CR1 = 0xd;
 huart->Instance->CR2 = 0;
 huart->Instance->CR3 = 0;
 huart->Instance->BRR = 0x221;
 huart->Instance->GTPR = 0;
 huart->Instance->ISR = 0x6000d0;
 huart->Instance->TDR = 0xa;
 huart->Instance->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
 huart->Instance->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
 huart->Instance->CR1 |= USART_CR1_UE;
  return (0);
}

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    for (uint16_t i = 0; i < Size; i++)
    {
        while (!(huart->Instance->ISR & USART_ISR_TXE_TXFNF));  // espera buffer vacío
        huart->Instance->TDR = pData[i];                   // escribe byte
    }

    while (!(huart->Instance->ISR & USART_ISR_TC));       // espera fin de transmisión
}


HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    for (uint16_t i = 0; i < Size; i++)
    {
        while (!(huart->Instance->ISR & USART_ISR_RXFF)); // espera dato recibido
        pData[i] = (uint8_t)(huart->Instance->RDR & 0xFF); // lee byte
    }
}

