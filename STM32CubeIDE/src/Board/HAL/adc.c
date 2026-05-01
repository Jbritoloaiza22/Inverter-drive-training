/**
 * @file adc.c
 * @brief ADC configuration and control for STM32G031 microcontroller.
 *
 * This module implements the ADC driver for the STM32G031, providing
 * initialization, calibration, and data acquisition functionalities.
 * It supports single-shunt current sensing and other analog measurements
 * required for motor control applications.
 *
 * The driver is designed to work with timer-triggered conversions to ensure
 * precise synchronization with PWM signals, which is critical for accurate
 * current reconstruction in FOC algorithms.
 *
 * Features:
 * - ADC initialization and calibration sequence
 * - Configurable channel selection and sampling time
 * - Timer-triggered conversion support (e.g., synchronized with PWM)
 * - Interrupt-based end-of-conversion handling
 * - Optional DMA support for efficient data transfer
 *
 * @note
 * This configuration is tailored for the EVS32 motor control board,
 * where the ADC is primarily used for single-shunt current measurement
 * and DC bus voltage sensing.
 *
 * @warning
 * Incorrect trigger configuration or sampling time may lead to
 * distorted current measurements, directly affecting control stability.
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