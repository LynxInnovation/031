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
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
031-516-202.lss \

FLASH_IMAGE += \
031-516-202.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: 031-516-202.elf secondary-outputs

# Tool invocations
031-516-202.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,031-516-202.map -mmcu=atmega644p -o "031-516-202.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

031-516-202.lss: 031-516-202.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 031-516-202.elf  >"031-516-202.lss"
	@echo 'Finished building: $@'
	@echo ' '

031-516-202.hex: 031-516-202.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex 031-516-202.elf  "031-516-202.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 031-516-202.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega644p 031-516-202.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 031-516-202.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
