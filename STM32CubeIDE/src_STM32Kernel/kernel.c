/**
 * @file kernel.c
 * @brief Main application entry point.
 *
 * This file contains the main program flow and peripheral initialization
 * routines for the STM32G031 microcontroller. The application initializes
 * the system, configures peripherals such as UART and ADC, enables timer
 * interrupts, and executes the main control loop.
 *
 * The system also relies on callback-based initialization functions
 * defined in the kernel interface to configure clocks, GPIOs, PWM,
 * and timers before enabling interrupts.
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

#include "kernel.h"
#include "KernelInterface.h"
#include "stm32g0xx_hal_uart.h"
#define dBAUDRATEUART 115200

/** @brief ADC handle structure */
ADC_HandleTypeDef hadc1;

/** @brief UART handle structure */
UART_HandleTypeDef huart1;

/* Private function prototypes */
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);

/** @brief Example counter used for PWM related tasks */
uint32_t ui32counter = 0;

/**
 * @brief Increment internal PWM counter.
 *
 * This function increments a global counter that may be used
 * for waveform indexing or periodic PWM related operations.
 */
void incCountertopwmDebug(void)
{
	ui32counter++;
}

/**
 * @brief Main program entry point.
 *
 * Initializes the HAL library, configures system peripherals,
 * enables timer interrupts, and runs the main application loop.
 *
 * @retval int Program return status (never returns in embedded systems)
 */
int main(void)
{
  HAL_Init();

  /* Initialize system components before enabling interrupts */
  vKernelInterface_initBeforeInterruptEnable();

  /* Initialize peripherals */
  MX_USART1_UART_Init();
  MX_ADC1_Init();

  /*enable user interrupts */
  vKernelInterface_enableInterruptsForAllPeripherals();

  while (1)
  {
    vKernelInterface_SetPhaseADuty((uint32_t)1999/2);
    vKernelInterface_SetPhaseBDuty((uint32_t)1999/3);
    vKernelInterface_SetPhaseCDuty((uint32_t)1999/7);
  }

}

/**
  * @brief ADC1 Initialization Function
  *
  * Configures the ADC peripheral with a single conversion channel
  * and 12-bit resolution. The ADC is configured for software-triggered
  * conversions without DMA.
  */
static void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;

  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  else
  {
    /*do nothing*/
  }
  /** Configure ADC Regular Channel */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;

  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  else
  {
    /*do nothing*/
  }
}

/**
  * @brief USART1 Initialization Function
  *
  * Configures USART1 for serial communication with the following
  * parameters:
  * - Baudrate: 115200
  * - 8 data bits
  * - 1 stop bit
  * - No parity
  */
static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;

  huart1.Init.BaudRate = dBAUDRATEUART;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  else
  {
    /*do nothing*/
  }
}

/**
  * @brief Error handler function.
  *
  * This function is executed whenever a HAL error occurs.
  * The system disables interrupts and enters an infinite loop.
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

/***************************************************************************
 * Custom initialization functions
 ***************************************************************************/

/**
 * @brief Initialize system modules before enabling interrupts.
 *
 * This function executes a sequence of callback functions responsible
 * for configuring the system clock, GPIOs, PWM modules, and timers.
 *
 * The callbacks are defined in the kernel interface layer to allow
 * hardware abstraction and modular configuration.
 */
void vKernelInterface_initBeforeInterruptEnable(void)
{
	cbRCC();
	cbGPIOS();
	cbPWM();
	cbTIM();
}

/**
 * @brief Enable interrupts for all configured peripherals.
 *
 * Configures and enables the Nested Vector Interrupt Controller (NVIC)
 * for the timers used in the application. Each interrupt is assigned
 * a priority level before being enabled.
 *
 * The following interrupts are enabled:
 * - TIM2 update interrupt
 * - TIM3 update interrupt
 */
void vKernelInterface_enableInterruptsForAllPeripherals(void)
{
  /* Enable TIM2 interrupt */
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);

  /* Enable TIM3 interrupt */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
}
