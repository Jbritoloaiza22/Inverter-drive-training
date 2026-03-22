################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/APP/Inverter/InverterControl.c \
../src/APP/Inverter/InverterJob.c \
../src/APP/Inverter/InverterOperation.c \
../src/APP/Inverter/MotorControl.c 

OBJS += \
./src/APP/Inverter/InverterControl.o \
./src/APP/Inverter/InverterJob.o \
./src/APP/Inverter/InverterOperation.o \
./src/APP/Inverter/MotorControl.o 

C_DEPS += \
./src/APP/Inverter/InverterControl.d \
./src/APP/Inverter/InverterJob.d \
./src/APP/Inverter/InverterOperation.d \
./src/APP/Inverter/MotorControl.d 


# Each subdirectory must supply rules for building sources it contributes
src/APP/Inverter/%.o src/APP/Inverter/%.su src/APP/Inverter/%.cyclo: ../src/APP/Inverter/%.c src/APP/Inverter/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../../Core/Inc -ISTM32CubeIDE/src -ISTM32CubeIDE/src_GFLib -ISTM32CubeIDE/src_libs -ISTM32CubeIDE/src_MCPara -ISTM32CubeIDE/src_STM32Kernel -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-APP-2f-Inverter

clean-src-2f-APP-2f-Inverter:
	-$(RM) ./src/APP/Inverter/InverterControl.cyclo ./src/APP/Inverter/InverterControl.d ./src/APP/Inverter/InverterControl.o ./src/APP/Inverter/InverterControl.su ./src/APP/Inverter/InverterJob.cyclo ./src/APP/Inverter/InverterJob.d ./src/APP/Inverter/InverterJob.o ./src/APP/Inverter/InverterJob.su ./src/APP/Inverter/InverterOperation.cyclo ./src/APP/Inverter/InverterOperation.d ./src/APP/Inverter/InverterOperation.o ./src/APP/Inverter/InverterOperation.su ./src/APP/Inverter/MotorControl.cyclo ./src/APP/Inverter/MotorControl.d ./src/APP/Inverter/MotorControl.o ./src/APP/Inverter/MotorControl.su

.PHONY: clean-src-2f-APP-2f-Inverter

