################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_GFLib/Math/ARM/CosSinTable.c 

OBJS += \
./src_GFLib/Math/ARM/CosSinTable.o 

C_DEPS += \
./src_GFLib/Math/ARM/CosSinTable.d 


# Each subdirectory must supply rules for building sources it contributes
src_GFLib/Math/ARM/%.o src_GFLib/Math/ARM/%.su src_GFLib/Math/ARM/%.cyclo: ../src_GFLib/Math/ARM/%.c src_GFLib/Math/ARM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -I../src_libs/BoardLib -I../src/Board/BoardApp -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src_GFLib-2f-Math-2f-ARM

clean-src_GFLib-2f-Math-2f-ARM:
	-$(RM) ./src_GFLib/Math/ARM/CosSinTable.cyclo ./src_GFLib/Math/ARM/CosSinTable.d ./src_GFLib/Math/ARM/CosSinTable.o ./src_GFLib/Math/ARM/CosSinTable.su

.PHONY: clean-src_GFLib-2f-Math-2f-ARM

