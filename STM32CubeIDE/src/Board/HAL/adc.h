/**
 * @file adc.h
 * @brief Analog-to-Digital Converter (ADC) driver interface.
 *
 * This header defines the public interface for the ADC driver used in the
 * system. It provides initialization, configuration, and data acquisition
 * functions to interact with the ADC peripheral in a hardware-abstracted
 * manner.
 *
 * The driver is designed to support different sampling strategies such as
 * single conversion, continuous mode, and trigger-based acquisition (e.g.,
 * timer-triggered). It can be used in polling, interrupt, or DMA modes
 * depending on system requirements.
 *
 * Responsibilities:
 * - Initialize and configure ADC peripheral parameters (resolution, channels,
 * sampling time)
 * - Start and stop ADC conversions
 * - Retrieve conversion results
 * - Interface with low-level hardware or HAL drivers
 * - Support synchronization with control loops (e.g., motor control, FOC)
 *
 * @note
 * ADC sampling time and trigger configuration must be carefully selected
 * to ensure accurate signal acquisition, especially in high-speed control
 * applications.
 *
 * @warning
 * Misconfiguration of ADC parameters (e.g., sampling time, trigger source)
 * may result in inaccurate readings or missed conversions.
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

#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g031xx.h"

/**
 * @brief ADC object structure.
 *
 * This structure represents the ADC module instance.
 * It stores the internal state of the ADC driver.
 *
 * @note This is a lightweight abstraction since hardware
 *       registers are globally accessible.
 */
typedef struct {
  /**
   * @brief Initialization flag.
   *
   * Indicates whether the ADC has been successfully initialized.
   * - 0: Not initialized
   * - 1: Initialized
   */
  uint8_t ui8initialized;
  uint8_t ui8channel;

} ADC_t;

/**
 * @brief Initializes the ADC peripheral.
 *
 * Configures ADC clock, resolution, alignment, and basic operating mode.
 * This function must be called before any other ADC operation.
 */
void vADC_Init(ADC_t *self);

/**
 * @brief Performs ADC self-calibration.
 *
 * Runs the internal calibration routine to improve conversion accuracy.
 * This should be executed once after initialization and before enabling the
 * ADC.
 */
void vADC_Calibrate(void);

/**
 * @brief Enables the ADC peripheral.
 *
 * Powers up the ADC and prepares it for conversions.
 * The ADC must be calibrated before calling this function.
 */
void vADC_Enable(void);

/**
 * @brief Disables the ADC peripheral.
 *
 * Safely stops the ADC and powers it down.
 */
void vADC_Disable(void);

int16_t vADC_i16Read(void);

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */