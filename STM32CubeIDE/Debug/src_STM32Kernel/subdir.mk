################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src_STM32Kernel/startup_stm32g031c8tx.s 

C_SRCS += \
../src_STM32Kernel/Core.c \
../src_STM32Kernel/Interrupt.c \
../src_STM32Kernel/Reset.c \
../src_STM32Kernel/Timer.c \
../src_STM32Kernel/kernel.c 

OBJS += \
./src_STM32Kernel/Core.o \
./src_STM32Kernel/Interrupt.o \
./src_STM32Kernel/Reset.o \
./src_STM32Kernel/Timer.o \
./src_STM32Kernel/kernel.o \
./src_STM32Kernel/startup_stm32g031c8tx.o 

S_DEPS += \
./src_STM32Kernel/startup_stm32g031c8tx.d 

C_DEPS += \
./src_STM32Kernel/Core.d \
./src_STM32Kernel/Interrupt.d \
./src_STM32Kernel/Reset.d \
./src_STM32Kernel/Timer.d \
./src_STM32Kernel/kernel.d 


# Each subdirectory must supply rules for building sources it contributes
src_STM32Kernel/%.o src_STM32Kernel/%.su src_STM32Kernel/%.cyclo: ../src_STM32Kernel/%.c src_STM32Kernel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -ISTM32CubeIDE/src -ISTM32CubeIDE/src_GFLib -ISTM32CubeIDE/src_libs -ISTM32CubeIDE/src_MCPara -I../src_STM32Kernel -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src_STM32Kernel/%.o: ../src_STM32Kernel/%.s src_STM32Kernel/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -ISTM32CubeIDE/src -ISTM32CubeIDE/src_GFLib -ISTM32CubeIDE/src_libs -ISTM32CubeIDE/src_MCPara -ISTM32CubeIDE/src_STM32Kernel -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-src_STM32Kernel

clean-src_STM32Kernel:
	-$(RM) ./src_STM32Kernel/Core.cyclo ./src_STM32Kernel/Core.d ./src_STM32Kernel/Core.o ./src_STM32Kernel/Core.su ./src_STM32Kernel/Interrupt.cyclo ./src_STM32Kernel/Interrupt.d ./src_STM32Kernel/Interrupt.o ./src_STM32Kernel/Interrupt.su ./src_STM32Kernel/Reset.cyclo ./src_STM32Kernel/Reset.d ./src_STM32Kernel/Reset.o ./src_STM32Kernel/Reset.su ./src_STM32Kernel/Timer.cyclo ./src_STM32Kernel/Timer.d ./src_STM32Kernel/Timer.o ./src_STM32Kernel/Timer.su ./src_STM32Kernel/kernel.cyclo ./src_STM32Kernel/kernel.d ./src_STM32Kernel/kernel.o ./src_STM32Kernel/kernel.su ./src_STM32Kernel/startup_stm32g031c8tx.d ./src_STM32Kernel/startup_stm32g031c8tx.o

.PHONY: clean-src_STM32Kernel

