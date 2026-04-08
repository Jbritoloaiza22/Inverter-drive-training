################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Board/HAL/ADCControl.c \
../src/Board/HAL/GPIOControl.c \
../src/Board/HAL/PWMControl.c \
../src/Board/HAL/TimerControl.c 

OBJS += \
./src/Board/HAL/ADCControl.o \
./src/Board/HAL/GPIOControl.o \
./src/Board/HAL/PWMControl.o \
./src/Board/HAL/TimerControl.o 

C_DEPS += \
./src/Board/HAL/ADCControl.d \
./src/Board/HAL/GPIOControl.d \
./src/Board/HAL/PWMControl.d \
./src/Board/HAL/TimerControl.d 


# Each subdirectory must supply rules for building sources it contributes
src/Board/HAL/%.o src/Board/HAL/%.su src/Board/HAL/%.cyclo: ../src/Board/HAL/%.c src/Board/HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-Board-2f-HAL

clean-src-2f-Board-2f-HAL:
	-$(RM) ./src/Board/HAL/ADCControl.cyclo ./src/Board/HAL/ADCControl.d ./src/Board/HAL/ADCControl.o ./src/Board/HAL/ADCControl.su ./src/Board/HAL/GPIOControl.cyclo ./src/Board/HAL/GPIOControl.d ./src/Board/HAL/GPIOControl.o ./src/Board/HAL/GPIOControl.su ./src/Board/HAL/PWMControl.cyclo ./src/Board/HAL/PWMControl.d ./src/Board/HAL/PWMControl.o ./src/Board/HAL/PWMControl.su ./src/Board/HAL/TimerControl.cyclo ./src/Board/HAL/TimerControl.d ./src/Board/HAL/TimerControl.o ./src/Board/HAL/TimerControl.su

.PHONY: clean-src-2f-Board-2f-HAL

