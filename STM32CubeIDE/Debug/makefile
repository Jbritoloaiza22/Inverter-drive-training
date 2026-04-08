################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src_libs/MainsLib/subdir.mk
-include src_libs/MCLib/subdir.mk
-include src_libs/BoardLib/subdir.mk
-include src_STM32Kernel/subdir.mk
-include src_GFLib/Math/ARM/subdir.mk
-include src_GFLib/Math/subdir.mk
-include src/EXTI/subdir.mk
-include src/Board/Interface/subdir.mk
-include src/Board/HAL/subdir.mk
-include src/Board/ClassB/subdir.mk
-include src/APP/Inverter/subdir.mk
-include src/APP/Interface/subdir.mk
-include src/APP/subdir.mk
-include STM32CubeIDE/Application/User/Startup/subdir.mk
-include STM32CubeIDE/Application/User/Core/subdir.mk
-include Drivers/STM32G0xx_HAL_Driver/Src/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := inverter_drive
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
inverter_drive.elf \

MAP_FILES += \
inverter_drive.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
inverter_drive.list \

OBJCOPY_HEX += \
inverter_drive.hex \

OBJCOPY_BIN += \
inverter_drive.bin \


# All Target
all: main-build

# Main-build Target
main-build: inverter_drive.elf secondary-outputs

# Tool invocations
inverter_drive.elf inverter_drive.map: $(OBJS) $(USER_OBJS) ../STM32G031C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "inverter_drive.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"../STM32G031C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="inverter_drive.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

inverter_drive.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "inverter_drive.list"
	@echo 'Finished building: $@'
	@echo ' '

inverter_drive.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "inverter_drive.hex"
	@echo 'Finished building: $@'
	@echo ' '

inverter_drive.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "inverter_drive.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout inverter_drive.bin inverter_drive.elf inverter_drive.hex inverter_drive.list inverter_drive.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
