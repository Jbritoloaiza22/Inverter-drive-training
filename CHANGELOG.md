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

## [v1.1.0] - 2026-05-02

### Added
- Custom UART driver (register-level implementation)
- UART interrupt-based communication
- Serial GUI interface for real-time interaction
- Cooperative scheduler implementation
- Custom ADC driver synchronized with PWM (TIM1) for DC-link current measurement
- FOC pipeline documentation (single-shunt control flow definition)
- Auto-format integration (coding style enforcement)
- CI integration for formatting validation

### Improved
- Integration of UART module with system architecture
- Modularization of peripheral drivers
- Development workflow with CI checks

### Notes
- ADC is externally triggered by PWM for deterministic sampling
- Foundation for closed-loop current control (FOC) established
- System ready for incremental implementation of current reconstruction and control stages