################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_GFLib/Math/Filter.c \
../src_GFLib/Math/Mathe.c \
../src_GFLib/Math/sqrt.c 

OBJS += \
./src_GFLib/Math/Filter.o \
./src_GFLib/Math/Mathe.o \
./src_GFLib/Math/sqrt.o 

C_DEPS += \
./src_GFLib/Math/Filter.d \
./src_GFLib/Math/Mathe.d \
./src_GFLib/Math/sqrt.d 


# Each subdirectory must supply rules for building sources it contributes
src_GFLib/Math/%.o src_GFLib/Math/%.su src_GFLib/Math/%.cyclo: ../src_GFLib/Math/%.c src_GFLib/Math/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../../Core/Inc -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_GFLib" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_libs" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_MCPara" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_STM32Kernel" -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src_GFLib-2f-Math

clean-src_GFLib-2f-Math:
	-$(RM) ./src_GFLib/Math/Filter.cyclo ./src_GFLib/Math/Filter.d ./src_GFLib/Math/Filter.o ./src_GFLib/Math/Filter.su ./src_GFLib/Math/Mathe.cyclo ./src_GFLib/Math/Mathe.d ./src_GFLib/Math/Mathe.o ./src_GFLib/Math/Mathe.su ./src_GFLib/Math/sqrt.cyclo ./src_GFLib/Math/sqrt.d ./src_GFLib/Math/sqrt.o ./src_GFLib/Math/sqrt.su

.PHONY: clean-src_GFLib-2f-Math

