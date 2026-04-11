################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Board/ClassB/MotorCurrentPlausability.c \
../src/Board/ClassB/SafetyMonitor.c \
../src/Board/ClassB/TemperatureMonitor.c 

OBJS += \
./src/Board/ClassB/MotorCurrentPlausability.o \
./src/Board/ClassB/SafetyMonitor.o \
./src/Board/ClassB/TemperatureMonitor.o 

C_DEPS += \
./src/Board/ClassB/MotorCurrentPlausability.d \
./src/Board/ClassB/SafetyMonitor.d \
./src/Board/ClassB/TemperatureMonitor.d 


# Each subdirectory must supply rules for building sources it contributes
src/Board/ClassB/%.o src/Board/ClassB/%.su src/Board/ClassB/%.cyclo: ../src/Board/ClassB/%.c src/Board/ClassB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -I../src_libs/BoardLib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-Board-2f-ClassB

clean-src-2f-Board-2f-ClassB:
	-$(RM) ./src/Board/ClassB/MotorCurrentPlausability.cyclo ./src/Board/ClassB/MotorCurrentPlausability.d ./src/Board/ClassB/MotorCurrentPlausability.o ./src/Board/ClassB/MotorCurrentPlausability.su ./src/Board/ClassB/SafetyMonitor.cyclo ./src/Board/ClassB/SafetyMonitor.d ./src/Board/ClassB/SafetyMonitor.o ./src/Board/ClassB/SafetyMonitor.su ./src/Board/ClassB/TemperatureMonitor.cyclo ./src/Board/ClassB/TemperatureMonitor.d ./src/Board/ClassB/TemperatureMonitor.o ./src/Board/ClassB/TemperatureMonitor.su

.PHONY: clean-src-2f-Board-2f-ClassB

