################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Board/HAL/TimerControl.c \
../src/Board/HAL/gpio.c \
../src/Board/HAL/pwm.c \
../src/Board/HAL/rcc.c \
../src/Board/HAL/tim.c 

OBJS += \
./src/Board/HAL/TimerControl.o \
./src/Board/HAL/gpio.o \
./src/Board/HAL/pwm.o \
./src/Board/HAL/rcc.o \
./src/Board/HAL/tim.o 

C_DEPS += \
./src/Board/HAL/TimerControl.d \
./src/Board/HAL/gpio.d \
./src/Board/HAL/pwm.d \
./src/Board/HAL/rcc.d \
./src/Board/HAL/tim.d 


# Each subdirectory must supply rules for building sources it contributes
src/Board/HAL/%.o src/Board/HAL/%.su src/Board/HAL/%.cyclo: ../src/Board/HAL/%.c src/Board/HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-Board-2f-HAL

clean-src-2f-Board-2f-HAL:
	-$(RM) ./src/Board/HAL/TimerControl.cyclo ./src/Board/HAL/TimerControl.d ./src/Board/HAL/TimerControl.o ./src/Board/HAL/TimerControl.su ./src/Board/HAL/gpio.cyclo ./src/Board/HAL/gpio.d ./src/Board/HAL/gpio.o ./src/Board/HAL/gpio.su ./src/Board/HAL/pwm.cyclo ./src/Board/HAL/pwm.d ./src/Board/HAL/pwm.o ./src/Board/HAL/pwm.su ./src/Board/HAL/rcc.cyclo ./src/Board/HAL/rcc.d ./src/Board/HAL/rcc.o ./src/Board/HAL/rcc.su ./src/Board/HAL/tim.cyclo ./src/Board/HAL/tim.d ./src/Board/HAL/tim.o ./src/Board/HAL/tim.su

.PHONY: clean-src-2f-Board-2f-HAL

