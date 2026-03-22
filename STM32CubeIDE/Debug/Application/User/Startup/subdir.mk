################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/User/Startup/startup_stm32g031c8tx.s 

OBJS += \
./Application/User/Startup/startup_stm32g031c8tx.o 

S_DEPS += \
./Application/User/Startup/startup_stm32g031c8tx.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Startup/%.o: ../Application/User/Startup/%.s Application/User/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_GFLib" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_libs" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_MCPara" -I"C:/Users/Jesus Daniel B/OneDrive/Documentos/Drives from scratch/firmware/inverter_drive/STM32CubeIDE/src_STM32Kernel" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Application-2f-User-2f-Startup

clean-Application-2f-User-2f-Startup:
	-$(RM) ./Application/User/Startup/startup_stm32g031c8tx.d ./Application/User/Startup/startup_stm32g031c8tx.o

.PHONY: clean-Application-2f-User-2f-Startup

