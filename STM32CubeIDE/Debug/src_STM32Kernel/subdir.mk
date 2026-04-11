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
../src_STM32Kernel/kernel.c \
../src_STM32Kernel/syscalls.c \
../src_STM32Kernel/sysmem.c 

OBJS += \
./src_STM32Kernel/Core.o \
./src_STM32Kernel/Interrupt.o \
./src_STM32Kernel/Reset.o \
./src_STM32Kernel/kernel.o \
./src_STM32Kernel/startup_stm32g031c8tx.o \
./src_STM32Kernel/syscalls.o \
./src_STM32Kernel/sysmem.o 

S_DEPS += \
./src_STM32Kernel/startup_stm32g031c8tx.d 

C_DEPS += \
./src_STM32Kernel/Core.d \
./src_STM32Kernel/Interrupt.d \
./src_STM32Kernel/Reset.d \
./src_STM32Kernel/kernel.d \
./src_STM32Kernel/syscalls.d \
./src_STM32Kernel/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
src_STM32Kernel/%.o src_STM32Kernel/%.su src_STM32Kernel/%.cyclo: ../src_STM32Kernel/%.c src_STM32Kernel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -I../src_libs/BoardLib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src_STM32Kernel/%.o: ../src_STM32Kernel/%.s src_STM32Kernel/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -I../src -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL -I../src/Board/HAL/STM32G0xx -I../src_STM32Kernel/HAL -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-src_STM32Kernel

clean-src_STM32Kernel:
	-$(RM) ./src_STM32Kernel/Core.cyclo ./src_STM32Kernel/Core.d ./src_STM32Kernel/Core.o ./src_STM32Kernel/Core.su ./src_STM32Kernel/Interrupt.cyclo ./src_STM32Kernel/Interrupt.d ./src_STM32Kernel/Interrupt.o ./src_STM32Kernel/Interrupt.su ./src_STM32Kernel/Reset.cyclo ./src_STM32Kernel/Reset.d ./src_STM32Kernel/Reset.o ./src_STM32Kernel/Reset.su ./src_STM32Kernel/kernel.cyclo ./src_STM32Kernel/kernel.d ./src_STM32Kernel/kernel.o ./src_STM32Kernel/kernel.su ./src_STM32Kernel/startup_stm32g031c8tx.d ./src_STM32Kernel/startup_stm32g031c8tx.o ./src_STM32Kernel/syscalls.cyclo ./src_STM32Kernel/syscalls.d ./src_STM32Kernel/syscalls.o ./src_STM32Kernel/syscalls.su ./src_STM32Kernel/sysmem.cyclo ./src_STM32Kernel/sysmem.d ./src_STM32Kernel/sysmem.o ./src_STM32Kernel/sysmem.su

.PHONY: clean-src_STM32Kernel

