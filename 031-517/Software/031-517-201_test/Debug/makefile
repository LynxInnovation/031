################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
031-517-201_test.lss \

FLASH_IMAGE += \
031-517-201_test.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: 031-517-201_test.elf secondary-outputs

# Tool invocations
031-517-201_test.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,031-517-201_test.map -mmcu=atmega48 -o "031-517-201_test.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

031-517-201_test.lss: 031-517-201_test.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 031-517-201_test.elf  >"031-517-201_test.lss"
	@echo 'Finished building: $@'
	@echo ' '

031-517-201_test.hex: 031-517-201_test.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex 031-517-201_test.elf  "031-517-201_test.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 031-517-201_test.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega48 031-517-201_test.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) 031-517-201_test.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
