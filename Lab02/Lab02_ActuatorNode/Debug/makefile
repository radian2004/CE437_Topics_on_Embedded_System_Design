################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
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


BUILD_ARTIFACT_NAME := Lab02_ActuatorNode
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Lab02_ActuatorNode.elf \

MAP_FILES += \
Lab02_ActuatorNode.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lab02_ActuatorNode.list \

OBJCOPY_HEX += \
Lab02_ActuatorNode.hex \

OBJCOPY_BIN += \
Lab02_ActuatorNode.bin \


# All Target
all: main-build

# Main-build Target
main-build: Lab02_ActuatorNode.elf secondary-outputs

# Tool invocations
Lab02_ActuatorNode.elf Lab02_ActuatorNode.map: $(OBJS) $(USER_OBJS) D:\STUDY\Embedded\STM32\CE437.P11.1_Topics\ on\ Embedded\ System\ Design\Lab02\Lab02_ActuatorNode\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Lab02_ActuatorNode.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\STUDY\Embedded\STM32\CE437.P11.1_Topics on Embedded System Design\Lab02\Lab02_ActuatorNode\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lab02_ActuatorNode.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lab02_ActuatorNode.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lab02_ActuatorNode.list"
	@echo 'Finished building: $@'
	@echo ' '

Lab02_ActuatorNode.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Lab02_ActuatorNode.hex"
	@echo 'Finished building: $@'
	@echo ' '

Lab02_ActuatorNode.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Lab02_ActuatorNode.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Lab02_ActuatorNode.bin Lab02_ActuatorNode.elf Lab02_ActuatorNode.hex Lab02_ActuatorNode.list Lab02_ActuatorNode.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
