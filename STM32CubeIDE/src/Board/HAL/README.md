# Board/HAL/ - Hardware abstraction layer

High-level drivers for STM32 peripherals.

## Typical files:
- PWMControl.c - PWM control (TIM1, TIM2, etc)
- ADCControl.c - ADC readings (currents, voltages)
- GPIOControl.c - GPIO control (relays, enables, LEDs)
- TimerControl.c - Timers for scheduling

## What to put here
- Specific wrappers over HAÑ_TIM, HAL_ADC, HAL_PWM, etc
- Complex peripheral configurations
- ISRs (interrupt Service Routines)
- DMA configurations
- Calibrations and analog conversions
