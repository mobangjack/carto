################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include carto/usr/src/subdir.mk
-include carto/srv/src/subdir.mk
-include carto/bsp/src/subdir.mk
-include carto/asp/src/subdir.mk
-include carto/app/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: carto_alpha.elf

dependents:
	-cd /home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/Debug && $(MAKE) all

# Tool invocations
carto_alpha.elf: $(OBJS) $(USER_OBJS) /home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/Debug/libstm32f405rg_stdperiph_lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -L"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/Debug" -T"/home/bj/workspace/eclipse/stm32/carto_alpha/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "carto_alpha.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "carto_alpha.elf" "carto_alpha.bin"
	arm-none-eabi-size "carto_alpha.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/Debug/libstm32f405rg_stdperiph_lib.a:

-include ../makefile.targets
