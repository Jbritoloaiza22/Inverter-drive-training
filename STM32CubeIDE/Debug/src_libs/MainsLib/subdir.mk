################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_libs/MainsLib/pll.c 

OBJS += \
./src_libs/MainsLib/pll.o 

C_DEPS += \
./src_libs/MainsLib/pll.d 


# Each subdirectory must supply rules for building sources it contributes
src_libs/MainsLib/%.o src_libs/MainsLib/%.su src_libs/MainsLib/%.cyclo: ../src_libs/MainsLib/%.c src_libs/MainsLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src_libs-2f-MainsLib

clean-src_libs-2f-MainsLib:
	-$(RM) ./src_libs/MainsLib/pll.cyclo ./src_libs/MainsLib/pll.d ./src_libs/MainsLib/pll.o ./src_libs/MainsLib/pll.su

.PHONY: clean-src_libs-2f-MainsLib

