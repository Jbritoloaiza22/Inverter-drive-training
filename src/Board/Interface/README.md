# Board/Interface/ - Main BoardInterface

Main interface for hardware access

## Key files
- BoardInterface.h/.c - Unified interface
- copiler_defs.h - compiler definitions

## What to put here:
- BoardInterface namespace with all APIs
- Base constants (maximum voltage, current, power)
- Unified APIs: PWM, ADC, GPIO, Timers
- Abstraction that hide STM32 HAL details
- Hardware initilization functions
