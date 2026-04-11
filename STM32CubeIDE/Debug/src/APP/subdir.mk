################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/APP/AppProgFlow.c \
../src/APP/AppProgramFlow.c \
../src/APP/Datalog.c \
../src/APP/Debug.c \
../src/APP/Device.c \
../src/APP/Error.c \
../src/APP/LEDS.c \
../src/APP/SelfTest.c \
../src/APP/Variant.c 

OBJS += \
./src/APP/AppProgFlow.o \
./src/APP/AppProgramFlow.o \
./src/APP/Datalog.o \
./src/APP/Debug.o \
./src/APP/Device.o \
./src/APP/Error.o \
./src/APP/LEDS.o \
./src/APP/SelfTest.o \
./src/APP/Variant.o 

C_DEPS += \
./src/APP/AppProgFlow.d \
./src/APP/AppProgramFlow.d \
./src/APP/Datalog.d \
./src/APP/Debug.d \
./src/APP/Device.d \
./src/APP/Error.d \
./src/APP/LEDS.d \
./src/APP/SelfTest.d \
./src/APP/Variant.d 


# Each subdirectory must supply rules for building sources it contributes
src/APP/%.o src/APP/%.su src/APP/%.cyclo: ../src/APP/%.c src/APP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../src/Board/Interface -I../src_GFLib/uC/PC/CMSIS -I../src_GFLib/uC/PC -I../src_GFLib -I../src_libs -I../src_MCPara -I../src_STM32Kernel -I../src/Board/HAL/STM32G0xx -I../src/Board/HAL -I../src_STM32Kernel/HAL -I../src_GFLib/uC/ARM_CM0 -I../src_libs/BoardLib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-APP

clean-src-2f-APP:
	-$(RM) ./src/APP/AppProgFlow.cyclo ./src/APP/AppProgFlow.d ./src/APP/AppProgFlow.o ./src/APP/AppProgFlow.su ./src/APP/AppProgramFlow.cyclo ./src/APP/AppProgramFlow.d ./src/APP/AppProgramFlow.o ./src/APP/AppProgramFlow.su ./src/APP/Datalog.cyclo ./src/APP/Datalog.d ./src/APP/Datalog.o ./src/APP/Datalog.su ./src/APP/Debug.cyclo ./src/APP/Debug.d ./src/APP/Debug.o ./src/APP/Debug.su ./src/APP/Device.cyclo ./src/APP/Device.d ./src/APP/Device.o ./src/APP/Device.su ./src/APP/Error.cyclo ./src/APP/Error.d ./src/APP/Error.o ./src/APP/Error.su ./src/APP/LEDS.cyclo ./src/APP/LEDS.d ./src/APP/LEDS.o ./src/APP/LEDS.su ./src/APP/SelfTest.cyclo ./src/APP/SelfTest.d ./src/APP/SelfTest.o ./src/APP/SelfTest.su ./src/APP/Variant.cyclo ./src/APP/Variant.d ./src/APP/Variant.o ./src/APP/Variant.su

.PHONY: clean-src-2f-APP

