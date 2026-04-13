################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/EXTI/Comm.c \
../src/EXTI/CustomComm.c 

OBJS += \
./src/EXTI/Comm.o \
./src/EXTI/CustomComm.o 

C_DEPS += \
./src/EXTI/Comm.d \
./src/EXTI/CustomComm.d 


# Each subdirectory must supply rules for building sources it contributes
src/EXTI/%.o src/EXTI/%.su src/EXTI/%.cyclo: ../src/EXTI/%.c src/EXTI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -I../src_libs/BoardLib -I../src/Board/BoardApp -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-EXTI

clean-src-2f-EXTI:
	-$(RM) ./src/EXTI/Comm.cyclo ./src/EXTI/Comm.d ./src/EXTI/Comm.o ./src/EXTI/Comm.su ./src/EXTI/CustomComm.cyclo ./src/EXTI/CustomComm.d ./src/EXTI/CustomComm.o ./src/EXTI/CustomComm.su

.PHONY: clean-src-2f-EXTI

