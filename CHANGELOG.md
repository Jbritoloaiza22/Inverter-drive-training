# Changelog

All notable changes to this project will be documented here.

---

## [v1.0.0] - 2026-04-15

### Added
- Space vector PWM open-loop control implemented
- TIM1 PWM driver
- TIM2 timer to 250us
- TIM3 timer to 1ms
- Motor startup sequence
- Docker
- Git action CI/CD
- Object pattern

### Fixed
- Interrupt timing stability
- Kernel interface includes
- Remove STM32CubeIDE files generated automatically
- Coding standard (MISRA C)

### Notes
- First functional motor rotation achieved in open-loop mode
- it must be debug with STM32CubeIDE with only elf file 