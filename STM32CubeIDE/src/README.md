# src/ - Project Specific Code

Cointains the specific code for this STM32 inverter
Not reusable - unique logic for this product

## structure
- APP/ - Application logic and main control
- Board/ - STM32 specific hardware abstraction
- EXTI/ - External communication (Modbus, CAN, SDLC, etc)

## What to put here
- main loop and device manager
- Specific control for inverter
- Hardware configurations
- External communication protocols