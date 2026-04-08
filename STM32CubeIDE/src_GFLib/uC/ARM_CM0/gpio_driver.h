

#include "stm32g031xx.h"

#define GPIO_NUMBER 16u
/**
 * @brief   Writes a value to a GPIO pin.
 *
 * This function sets or resets the specified GPIO pin by directly
 * manipulating the GPIO port's BSRR/BRR registers.
 *
 * @param   GPIOx      Pointer to the GPIO port (e.g., GPIOA, GPIOB)
 * @param   GPIO_Pin   GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1)
 * @param   PinState   Desired pin state: GPIO_PIN_SET or GPIO_PIN_RESET
 *
 * @note    This function bypasses the HAL and manipulates registers directly.
 */
static inline void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	  if (PinState != GPIO_PIN_RESET)
	  {
	    GPIOx->BSRR = (uint32_t)GPIO_Pin;
	  }
	  else
	  {
	    GPIOx->BRR = (uint32_t)GPIO_Pin;
	  }
}

/**
 * @brief   Toggles the state of a GPIO pin.
 *
 * This function inverts the current output level of the specified GPIO pin
 * by reading the Output Data Register (ODR) and setting/resetting the pin
 * accordingly.
 *
 * @param   GPIOx      Pointer to the GPIO port (e.g., GPIOA, GPIOB)
 * @param   GPIO_Pin   GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1)
 *
 * @note    GPIO_NUMBER must be defined as the bit position of the pin.
 */
static inline void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	  uint32_t odr;

	  /* get current Output Data Register value */
	  odr = GPIOx->ODR;

	  /* Set selected pins that were at low level, and reset ones that were high */
	  GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);

}

/**
 * @brief   Reads the state of a GPIO pin.
 *
 * This function returns the current input level of the specified GPIO pin
 * by reading the Input Data Register (IDR).
 *
 * @param   GPIOx      Pointer to the GPIO port (e.g., GPIOA, GPIOB)
 * @param   GPIO_Pin   GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1)
 * @return  GPIO_PinState   GPIO_PIN_SET if the pin is high, GPIO_PIN_RESET if low
 */
static inline uint16_t GPIO_ReadPin(GPIO_TypeDef const *GPIOx, uint16_t GPIO_Pin)
{
	  GPIO_PinState bitstatus;

	  if ((GPIOx->IDR & GPIO_Pin) != 0x00u)
	  {
	    bitstatus = GPIO_PIN_SET;
	  }
	  else
	  {
	    bitstatus = GPIO_PIN_RESET;
	  }
	  return bitstatus;
}
