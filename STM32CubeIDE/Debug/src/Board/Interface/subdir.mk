################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Board/Interface/BoardInterface.c \
../src/Board/Interface/stm32g0xx_hal_msp.c \
../src/Board/Interface/stm32g0xx_it.c \
../src/Board/Interface/system_stm32g0xx.c 

OBJS += \
./src/Board/Interface/BoardInterface.o \
./src/Board/Interface/stm32g0xx_hal_msp.o \
./src/Board/Interface/stm32g0xx_it.o \
./src/Board/Interface/system_stm32g0xx.o 

C_DEPS += \
./src/Board/Interface/BoardInterface.d \
./src/Board/Interface/stm32g0xx_hal_msp.d \
./src/Board/Interface/stm32g0xx_it.d \
./src/Board/Interface/system_stm32g0xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/Board/Interface/%.o src/Board/Interface/%.su src/Board/Interface/%.cyclo: ../src/Board/Interface/%.c src/Board/Interface/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -I../src_libs/BoardLib -I../src/Board/BoardApp -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-Board-2f-Interface

clean-src-2f-Board-2f-Interface:
	-$(RM) ./src/Board/Interface/BoardInterface.cyclo ./src/Board/Interface/BoardInterface.d ./src/Board/Interface/BoardInterface.o ./src/Board/Interface/BoardInterface.su ./src/Board/Interface/stm32g0xx_hal_msp.cyclo ./src/Board/Interface/stm32g0xx_hal_msp.d ./src/Board/Interface/stm32g0xx_hal_msp.o ./src/Board/Interface/stm32g0xx_hal_msp.su ./src/Board/Interface/stm32g0xx_it.cyclo ./src/Board/Interface/stm32g0xx_it.d ./src/Board/Interface/stm32g0xx_it.o ./src/Board/Interface/stm32g0xx_it.su ./src/Board/Interface/system_stm32g0xx.cyclo ./src/Board/Interface/system_stm32g0xx.d ./src/Board/Interface/system_stm32g0xx.o ./src/Board/Interface/system_stm32g0xx.su

.PHONY: clean-src-2f-Board-2f-Interface

