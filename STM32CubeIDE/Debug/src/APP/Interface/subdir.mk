################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/APP/Interface/AppInterface.c 

OBJS += \
./src/APP/Interface/AppInterface.o 

C_DEPS += \
./src/APP/Interface/AppInterface.d 


# Each subdirectory must supply rules for building sources it contributes
src/APP/Interface/%.o src/APP/Interface/%.su src/APP/Interface/%.cyclo: ../src/APP/Interface/%.c src/APP/Interface/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -ISTM32CubeIDE/src -ISTM32CubeIDE/src_GFLib -ISTM32CubeIDE/src_libs -ISTM32CubeIDE/src_MCPara -I../src_STM32Kernel -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-APP-2f-Interface

clean-src-2f-APP-2f-Interface:
	-$(RM) ./src/APP/Interface/AppInterface.cyclo ./src/APP/Interface/AppInterface.d ./src/APP/Interface/AppInterface.o ./src/APP/Interface/AppInterface.su

.PHONY: clean-src-2f-APP-2f-Interface

