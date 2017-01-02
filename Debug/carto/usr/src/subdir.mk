################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../carto/usr/src/main.c \
../carto/usr/src/syscalls.c 

OBJS += \
./carto/usr/src/main.o \
./carto/usr/src/syscalls.o 

C_DEPS += \
./carto/usr/src/main.d \
./carto/usr/src/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
carto/usr/src/%.o: ../carto/usr/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32F4 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/usr/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/app/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/srv/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/asp/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/bsp/inc" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/core" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/device" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


