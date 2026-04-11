/**
 * @file gpio.c
 * @author Jesus Daniel Britoloaiza
 * @brief GPIO configuration for STM32G031 microcontroller, including analog, output, and alternate functions.
 *
 * This module provides a flexible macro-based GPIO initialization system for the STM32G031.
 * It configures pins for ADC inputs, TIM channels, UART, and general-purpose I/O,
 * and allows easy modification of mode, speed, output type, pull-up/pull-down, and alternate functions.
 *
 * @note This configuration is intended for the EVS32 motor control board, where certain pins
 *       are reserved for current sensing and PWM outputs.
 */
#include "stm32g031xx.h"
#include "KernelInterface.h"
#include "gpio.h"
/* gpio mode register values */
#define GPIO_MODE_INPUT			0x00 /* use port as input */
#define GPIO_MODE_OUTPUT		0x01 /* use port as output */
#define GPIO_MODE_AF			0x02 /* use port as alternate function */
#define GPIO_MODE_ANALOG		0x03 /* use port as analog */

/*gpio output type register values */
#define GPIO_OTYPE_PP			0x00 /* push-pull output */
#define GPIO_OTYPE_OD			0x01 /* open-drain output */

/*gpio output speed register values */
#define GPIO_SPEED_VERY_LOW	    0x00 /* low speed */
#define GPIO_SPEED_LOW			0x01 /* medium speed */
#define GPIO_SPEED_HIGH			0x02 /* high speed */
#define GPIO_SPEED_VERY_HIGH	0x03 /* very high speed */

/*gpio pull-up/pull-down register values */
#define GPIO_NOPULL				0x00 /* no pull-up, pull-down */
#define GPIO_PULLUP				0x01 /* pull-up */
#define GPIO_PULLDOWN			0x02 /* pull-down */

/*gpio pin state values */
#define GPIO_PIN_RESET			0x00 /* pin reset */
#define GPIO_PIN_SET				0x01 /* pin set */

/* alternative function defines*/
#define GPIO_AF0					0x00
#define GPIO_AF1					0x01
#define GPIO_AF2					0x02
#define GPIO_AF3					0x03
#define GPIO_AF4					0x04
#define GPIO_AF5					0x05
#define GPIO_AF6					0x06
#define GPIO_AF7					0x07
#define GPIO_AF8					0x08
#define GPIO_AF9					0x09
#define GPIO_AF10					0x0A
#define GPIO_AF11					0x0B
#define GPIO_AF12					0x0C
#define GPIO_AF13					0x0D
#define GPIO_AF14					0x0E
#define GPIO_AF15					0x0F

/* helper macros */
/*
* @brief  configure a GPIO pin with all parameters
* @param  port: where x can be (A..K) to select the GPIO peripheral
* @param  pin: specifies the GPIO pins to be configured.
* @param  mode: specifies the operating mode for the selected pins.
* @param  otype: specifies the output type for the selected pins.
* @param speed: specifies the speed for the selected pins.
* @param  pupd: specifies the Pull-up or Pull-Down activation for the selected
* @param af: specifies the alternate function value if mode is set to alternate function
*/
#define GPIO_CONFIG_PIN(port, pin, mode, otype, speed, pupd, af) \
    do{ \
        /*configure mode register*/ \
        (port)->MODER = ((port)->MODER & ~(0x3 << ((pin) * 2))) | ((mode) << ((pin) * 2)); \
        /*configure output type register*/ \
        (port)->OTYPER = ((port)->OTYPER & ~(0x1 << (pin))) | ((otype) << (pin)); \
        /*configure output speed register*/ \
        (port)->OSPEEDR = ((port)->OSPEEDR & ~(0x3 << ((pin) * 2))) | ((speed) << ((pin) * 2)); \
        /*configure pull-up/pull-down register*/ \
        (port)->PUPDR = ((port)->PUPDR & ~(0x3 << ((pin) * 2))) | ((pupd) << ((pin) * 2)); \
        /*configure alternate function register*/ \
        if (mode == GPIO_MODE_AF) { \
            uint8_t af_index = (pin < 8) ? 0 : 1; \
            uint32_t af_mask = 0xF << ((pin % 8) * 4); \
            (port)->AFR[af_index] = ((port)->AFR[af_index] & ~af_mask) | ((af) << ((pin % 8) * 4)); \
        } \
    }while(0)

/**
 * @brief Initializes all GPIO ports with predefined configuration.
 *
 * Configures each pin according to the EVS32 motor control board:
 *
 * @note Pins used for ADC, PWM, and UART are configured to avoid hardware conflicts.
 * @note Call this function before using any GPIO peripheral.
 */static void gpio_PortInit(void);

/* function implementations */
/*
* @brief  initialize GPIO ports
* @note   this function should be called before any GPIO configuration 
*/
static void gpio_PortInit(void) {
    /******************************************************************* PORT A *******************************************************************/
    /* PA0: ADC1_IN0 */      GPIO_CONFIG_PIN(GPIOA, 0,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA1: ADC1_IN1 */      GPIO_CONFIG_PIN(GPIOA, 1,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA2: ADC1_IN2 */      GPIO_CONFIG_PIN(GPIOA, 2,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA3: */               GPIO_CONFIG_PIN(GPIOA, 3,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA4: */               GPIO_CONFIG_PIN(GPIOA, 4,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA5: */               GPIO_CONFIG_PIN(GPIOA, 5,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA6: */               GPIO_CONFIG_PIN(GPIOA, 6,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA7: */               GPIO_CONFIG_PIN(GPIOA, 7,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA8: TIM1_CH1 */      GPIO_CONFIG_PIN(GPIOA, 8,  GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF2);
    /* PA9: TIM1_CH2 */      GPIO_CONFIG_PIN(GPIOA, 9,  GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF2);
    /* PA10: TIM1_CH3 */     GPIO_CONFIG_PIN(GPIOA, 10, GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF2);
    /* PA11: DEBUG_PIN*/     GPIO_CONFIG_PIN(GPIOA, 11, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA12: */	             GPIO_CONFIG_PIN(GPIOA, 12, GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    /* PA13: */	             GPIO_CONFIG_PIN(GPIOA, 13, GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_HIGH, GPIO_PULLUP,   GPIO_AF0);
    /* PA14: */	             GPIO_CONFIG_PIN(GPIOA, 14, GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_PULLDOWN, GPIO_AF0);
    /* PA15: */	             GPIO_CONFIG_PIN(GPIOA, 15, GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW,  GPIO_NOPULL,   GPIO_AF0);
    
    /******************************************************************* PORT B *******************************************************************/
    /* PB0: */               GPIO_CONFIG_PIN(GPIOB, 0,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB1: */               GPIO_CONFIG_PIN(GPIOB, 1,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB2: */               GPIO_CONFIG_PIN(GPIOB, 2,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB3: */               GPIO_CONFIG_PIN(GPIOB, 3,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB4: */               GPIO_CONFIG_PIN(GPIOB, 4,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB5: */               GPIO_CONFIG_PIN(GPIOB, 5,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB6: UART_TX*/        GPIO_CONFIG_PIN(GPIOB, 6,  GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB7: UART_RX*/        GPIO_CONFIG_PIN(GPIOB, 7,  GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB8: */               GPIO_CONFIG_PIN(GPIOB, 8,  GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB9: DEBUG_PIN */     GPIO_CONFIG_PIN(GPIOB, 9,  GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PB10: */              GPIO_CONFIG_PIN(GPIOB, 10, GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PA11: */              GPIO_CONFIG_PIN(GPIOB, 11, GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PA12: */	             GPIO_CONFIG_PIN(GPIOB, 12, GPIO_MODE_ANALOG, GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF0);
    /* PA13: TIM1_CH1N*/	 GPIO_CONFIG_PIN(GPIOB, 13, GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF2);
    /* PA14: TIM1_CH2N*/	 GPIO_CONFIG_PIN(GPIOB, 14, GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF2);
    /* PA15: TIM1_CH3N*/	 GPIO_CONFIG_PIN(GPIOB, 15, GPIO_MODE_AF,     GPIO_OTYPE_PP, GPIO_SPEED_VERY_LOW, GPIO_NOPULL, GPIO_AF2);

}

/**
 * @brief Initializes GPIO subsystem.
 *
 * Calls gpio_PortInit() to configure all ports and pins.
 * Should be called at system startup.
 */
void gpio_Init(void){
    gpio_PortInit();
}

/**
 * @brief GPIO callback function.
 *
 * Alias to GPIO_Init(), can be called as a callback or initialization routine.
 */
void cbGPIOS(void){
	gpio_Init();
	EnableDrivePinForMotorControl();
}

/**
 * @brief PWM callback function.
 *
 * Alias to PWM_Init(), can be called as a callback or initialization routine.
 */
void cbPWM(void){
	pwm_Init();
	pwm_Start();
}

