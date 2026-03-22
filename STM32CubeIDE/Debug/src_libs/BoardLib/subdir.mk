################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_libs/BoardLib/Itrip.c \
../src_libs/BoardLib/Temperature.c 

OBJS += \
./src_libs/BoardLib/Itrip.o \
./src_libs/BoardLib/Temperature.o 

C_DEPS += \
./src_libs/BoardLib/Itrip.d \
./src_libs/BoardLib/Temperature.d 


# Each subdirectory must supply rules for building sources it contributes
src_libs/BoardLib/%.o src_libs/BoardLib/%.su src_libs/BoardLib/%.cyclo: ../src_libs/BoardLib/%.c src_libs/BoardLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../../Core/Inc -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_GFLib" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_libs" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_MCPara" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_STM32Kernel" -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src_libs-2f-BoardLib

clean-src_libs-2f-BoardLib:
	-$(RM) ./src_libs/BoardLib/Itrip.cyclo ./src_libs/BoardLib/Itrip.d ./src_libs/BoardLib/Itrip.o ./src_libs/BoardLib/Itrip.su ./src_libs/BoardLib/Temperature.cyclo ./src_libs/BoardLib/Temperature.d ./src_libs/BoardLib/Temperature.o ./src_libs/BoardLib/Temperature.su

.PHONY: clean-src_libs-2f-BoardLib

