################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Jesus\ Daniel\ B/OneDrive/Documentos/Drives\ from\ scratch/firmware/inverter_drive/Core/Src/system_stm32g0xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32g0xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32g0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32g0xx.o: C:/Users/Jesus\ Daniel\ B/OneDrive/Documentos/Drives\ from\ scratch/firmware/inverter_drive/Core/Src/system_stm32g0xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../../Core/Inc -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_GFLib" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_libs" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_MCPara" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_STM32Kernel" -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/CMSIS/system_stm32g0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32g0xx.cyclo ./Drivers/CMSIS/system_stm32g0xx.d ./Drivers/CMSIS/system_stm32g0xx.o ./Drivers/CMSIS/system_stm32g0xx.su

.PHONY: clean-Drivers-2f-CMSIS

