/**
 * @file adc.h
 * @brief Analog-to-Digital Converter (ADC) driver interface.
 *
 * This header defines the public interface for the ADC driver used in the system.
 * It provides initialization, configuration, and data acquisition functions
 * to interact with the ADC peripheral in a hardware-abstracted manner.
 *
 * The driver is designed to support different sampling strategies such as
 * single conversion, continuous mode, and trigger-based acquisition (e.g., timer-triggered).
 * It can be used in polling, interrupt, or DMA modes depending on system requirements.
 *
 * Responsibilities:
 * - Initialize and configure ADC peripheral parameters (resolution, channels, sampling time)
 * - Start and stop ADC conversions
 * - Retrieve conversion results
 * - Interface with low-level hardware or HAL drivers
 * - Support synchronization with control loops (e.g., motor control, FOC)
 *
 * @note
 * ADC sampling time and trigger configuration must be carefully selected
 * to ensure accurate signal acquisition, especially in high-speed control applications.
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

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */