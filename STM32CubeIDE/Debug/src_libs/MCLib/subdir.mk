################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_libs/MCLib/CurrentControl.c \
../src_libs/MCLib/FOC.c \
../src_libs/MCLib/MotorObserver.c \
../src_libs/MCLib/SpeedControl.c 

OBJS += \
./src_libs/MCLib/CurrentControl.o \
./src_libs/MCLib/FOC.o \
./src_libs/MCLib/MotorObserver.o \
./src_libs/MCLib/SpeedControl.o 

C_DEPS += \
./src_libs/MCLib/CurrentControl.d \
./src_libs/MCLib/FOC.d \
./src_libs/MCLib/MotorObserver.d \
./src_libs/MCLib/SpeedControl.d 


# Each subdirectory must supply rules for building sources it contributes
src_libs/MCLib/%.o src_libs/MCLib/%.su src_libs/MCLib/%.cyclo: ../src_libs/MCLib/%.c src_libs/MCLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -ISTM32CubeIDE/src -ISTM32CubeIDE/src_GFLib -ISTM32CubeIDE/src_libs -ISTM32CubeIDE/src_MCPara -I../src_STM32Kernel -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src_libs-2f-MCLib

clean-src_libs-2f-MCLib:
	-$(RM) ./src_libs/MCLib/CurrentControl.cyclo ./src_libs/MCLib/CurrentControl.d ./src_libs/MCLib/CurrentControl.o ./src_libs/MCLib/CurrentControl.su ./src_libs/MCLib/FOC.cyclo ./src_libs/MCLib/FOC.d ./src_libs/MCLib/FOC.o ./src_libs/MCLib/FOC.su ./src_libs/MCLib/MotorObserver.cyclo ./src_libs/MCLib/MotorObserver.d ./src_libs/MCLib/MotorObserver.o ./src_libs/MCLib/MotorObserver.su ./src_libs/MCLib/SpeedControl.cyclo ./src_libs/MCLib/SpeedControl.d ./src_libs/MCLib/SpeedControl.o ./src_libs/MCLib/SpeedControl.su

.PHONY: clean-src_libs-2f-MCLib

