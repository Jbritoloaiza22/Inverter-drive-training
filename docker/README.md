# 🐳 Docker Build Environment

This directory contains the Docker configuration used to create a **reproducible build environment** for the STM32 inverter firmware.

---

## Purpose

The Docker container provides all required tools to build the firmware without relying on STM32CubeIDE.

This ensures:

- Reproducible builds
- No dependency on local machine setup
- Consistent toolchain across environments
- Ready for CI/CD integration

---

## Included Tools

- Ubuntu 22.04
- GNU Arm Embedded Toolchain (12.2)
- GCC, Make, CMake
- Git
- Python3

---

## Build the Image

From the root of the repository:

#bash
docker build -t stm32-make docker