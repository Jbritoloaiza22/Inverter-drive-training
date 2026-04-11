################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_libs/BoardLib/Itrip.c \
../src_libs/BoardLib/Temperature.c \
../src_libs/BoardLib/svm.c 

OBJS += \
./src_libs/BoardLib/Itrip.o \
./src_libs/BoardLib/Temperature.o \
./src_libs/BoardLib/svm.o 

C_DEPS += \
./src_libs/BoardLib/Itrip.d \
./src_libs/BoardLib/Temperature.d \
./src_libs/BoardLib/svm.d 


# Each subdirectory must supply rules for building sources it contributes
src_libs/BoardLib/%.o src_libs/BoardLib/%.su src_libs/BoardLib/%.cyclo: ../src_libs/BoardLib/%.c src_libs/BoardLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -I../src_libs/BoardLib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src_libs-2f-BoardLib

clean-src_libs-2f-BoardLib:
	-$(RM) ./src_libs/BoardLib/Itrip.cyclo ./src_libs/BoardLib/Itrip.d ./src_libs/BoardLib/Itrip.o ./src_libs/BoardLib/Itrip.su ./src_libs/BoardLib/Temperature.cyclo ./src_libs/BoardLib/Temperature.d ./src_libs/BoardLib/Temperature.o ./src_libs/BoardLib/Temperature.su ./src_libs/BoardLib/svm.cyclo ./src_libs/BoardLib/svm.d ./src_libs/BoardLib/svm.o ./src_libs/BoardLib/svm.su

.PHONY: clean-src_libs-2f-BoardLib

