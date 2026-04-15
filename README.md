# Inverter Drive Firmware (STM32G0 + PMSM Control)

Firmware for a 3-phase inverter based on the **STSPIN32G0251 / EVSPIN32G02Q1S1 evaluation platform**, designed for PMSM motor control using Space Vector Modulation (SVM) as a foundation toward Field Oriented Control (FOC).

This project is built with a strong focus on **embedded software engineering practices**, including reproducible builds, modular architecture, MISRA-C style constraints, and CI/CD automation using Docker and GitHub Actions.

---

## Project Goals

- Implement and understand **Space Vector PWM (SVPWM)**
- Build from open-loop control → closed-loop FOC
- Study and implement:
  - Clarke Transform (αβ)
  - Park Transform (dq)
  - Inverse transforms
  - PWM modulation strategies
- Develop a **production-like embedded firmware architecture**
- Integrate modern software practices into embedded systems:
  - Docker-based toolchain
  - GitHub Actions CI/CD
  - Git Flow branching strategy
  - MISRA-C coding style
  - Unit testing and modular design
  - Doxygen documentation

---

## Technical Scope

### Control Theory
- Space Vector Modulation (SVM)
- Sinusoidal PWM (SPWM)
- Open-loop motor control
- Field Oriented Control (FOC) roadmap
- Clarke & Park transformations
- Voltage vector synthesis in αβ plane

### Embedded System
- STM32G031 (Cortex-M0+)
- STSPIN32G0251 inverter driver
- TIM1 advanced PWM (center-aligned mode)
- ADC-based feedback (current/voltage sensing)
- ISR-based control loop execution

### Firmware Architecture
- Modular layered design:
  - `Board/` → Hardware abstraction
  - `APP/` → Application logic
  - `MCLib/` → Motor control algorithms
  - `GFLib/` → Math utilities
  - `STM32Kernel/` → Low-level drivers

---

## Space Vector PWM (SVM)

The implemented SVM algorithm:

- Converts αβ voltage references into 3-phase duty cycles
- Uses sector detection (1–6)
- Computes switching times T1 and T2
- Applies centered PWM modulation

Key idea:

\[
V_{\alpha\beta} \rightarrow V_{abc} \rightarrow Duty Cycles
\]

This allows:

- Reduced harmonic distortion
- Better DC bus utilization
- Higher efficiency vs SPWM

---

## Docker Toolchain (Reproducible Build)

This project includes a fully reproducible ARM embedded toolchain using Docker.

### Build image:
```bash
docker build -t stm32-make ./docker