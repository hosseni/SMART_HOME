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
SmartHome_SlaveCode.lss \

FLASH_IMAGE += \
SmartHome_SlaveCode.hex \

EEPROM_IMAGE += \
SmartHome_SlaveCode.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: SmartHome_SlaveCode.elf secondary-outputs

# Tool invocations
SmartHome_SlaveCode.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SmartHome_SlaveCode.map -mmcu=atmega32 -o "SmartHome_SlaveCode.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SmartHome_SlaveCode.lss: SmartHome_SlaveCode.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SmartHome_SlaveCode.elf  >"SmartHome_SlaveCode.lss"
	@echo 'Finished building: $@'
	@echo ' '

SmartHome_SlaveCode.hex: SmartHome_SlaveCode.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SmartHome_SlaveCode.elf  "SmartHome_SlaveCode.hex"
	@echo 'Finished building: $@'
	@echo ' '

SmartHome_SlaveCode.eep: SmartHome_SlaveCode.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SmartHome_SlaveCode.elf  "SmartHome_SlaveCode.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SmartHome_SlaveCode.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SmartHome_SlaveCode.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SmartHome_SlaveCode.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
