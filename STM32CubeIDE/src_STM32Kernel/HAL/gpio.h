#include "gpio_driver.h"

void GPIO_Init(void);

static inline void ToggleDebugPin(void)
{
	GPIO_TogglePin(GPIOB, GPIO_PIN_9);
}
