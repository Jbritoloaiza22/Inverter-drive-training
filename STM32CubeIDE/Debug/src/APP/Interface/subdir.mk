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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -I../src_libs/BoardLib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-APP-2f-Interface

clean-src-2f-APP-2f-Interface:
	-$(RM) ./src/APP/Interface/AppInterface.cyclo ./src/APP/Interface/AppInterface.d ./src/APP/Interface/AppInterface.o ./src/APP/Interface/AppInterface.su

.PHONY: clean-src-2f-APP-2f-Interface

