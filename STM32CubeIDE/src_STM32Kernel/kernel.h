/**
 * @file kernel.h
 * @brief Declarations for the STM32 application kernel.
 *
 * This header defines the entry point and initialization routines
 * for the custom application kernel. The CubeMX-generated main.c
 * should call STM32Kernel_Main() to start the architecture defined here.
 */
#ifndef KERNEL_H
#define KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Entry point for the application kernel.
 *
 * This function organizes hardware and application initialization
 * and runs the main control loop.
 */
void STM32Kernel_Main(void);

#ifdef __cplusplus
}
#endif

#endif /* KERNEL_H */
