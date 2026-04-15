#/**
# * @file    project firmware
# * @brief   inverter drive firmware for STM32G031C8T6
# *
# * @copyright
# * Copyright (c) 2026 Jesus Daniel Britoloaiza
# * All rights reserved.
#*/
# ================= TOOLCHAIN =================
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# ================= PROJECT =================
TARGET = inverter_drive
MCU = cortex-m0plus

LINKER_SCRIPT = ../src/Board/HAL/STM32G0xx/STM32G031C8TX_FLASH.ld

# ================= FLAGS =================
CFLAGS = -mcpu=$(MCU) -mthumb -std=gnu11 \
         -O0 -g3 \
         -ffunction-sections -fdata-sections \
         -Wall -Wextra -fno-common \
         -DUSE_HAL_DRIVER -DSTM32G031xx \
         -mfloat-abi=soft

LDFLAGS = -mcpu=$(MCU) -mthumb \
          -T$(LINKER_SCRIPT) \
          -Wl,--gc-sections \
          -Wl,-Map=$(TARGET).map \
          --specs=nano.specs \
          --specs=nosys.specs \
          -mfloat-abi=soft

# ================= INCLUDE PATHS =================
INCLUDES = \
-I../src \
-I../src/APP \
-I../src/Board \
-I../src/Board/BoardApp \
-I../src/Board/HAL \
-I../src/Board/Interface \
-I../src_STM32Kernel \
-I../src_STM32Kernel/HAL \
-I../src_STM32Kernel/Device/STM32G0xx/Include \
-I../src_STM32Kernel/CMSIS/Core/Include \
-I../src_libs \
-I../src_libs/BoardLib \
-I../src_GFLib \
-I../src_GFLib/Math \
-I../src_GFLib/uC/PC \
-I../src_GFLib/uC/PC/CMSIS \
-I../src_GFLib/uC/ARM_CM0 \
-I../src/EXTI

# ================= SOURCES =================
C_SRCS := $(shell find ../src -type f -name "*.c")
C_SRCS += $(shell find ../src_STM32Kernel -type f -name "*.c")
C_SRCS += $(shell find ../src_libs -type f -name "*.c")
C_SRCS += $(shell find ../src_GFLib -type f -name "*.c")

S_SRCS := $(shell find ../src_STM32Kernel -type f -name "*.s")

# remove duplicates sources
OBJS := $(sort $(C_SRCS:.c=.o) $(S_SRCS:.s=.o))

# ================= BUILD =================
all: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	@echo "Linking firmware..."
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

# ================= COMPILE =================
%.o: %.c
	@echo "CC $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.s
	@echo "ASM $<"
	$(CC) -x assembler-with-cpp $(CFLAGS) -c $< -o $@

# ================= OUTPUT =================
bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $(TARGET).bin

hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $(TARGET).hex

# ================= CLEAN =================
clean:
	rm -rf $(OBJS) \
	       $(TARGET).elf \
	       $(TARGET).bin \
	       $(TARGET).hex \
	       $(TARGET).map

.PHONY: all clean bin hex