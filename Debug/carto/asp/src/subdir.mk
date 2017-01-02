################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../carto/asp/src/crc16.c \
../carto/asp/src/dbus.c \
../carto/asp/src/fifo.c \
../carto/asp/src/gauss.c \
../carto/asp/src/kalman.c \
../carto/asp/src/mafilter.c \
../carto/asp/src/mecanum.c \
../carto/asp/src/pid.c \
../carto/asp/src/ramp.c 

OBJS += \
./carto/asp/src/crc16.o \
./carto/asp/src/dbus.o \
./carto/asp/src/fifo.o \
./carto/asp/src/gauss.o \
./carto/asp/src/kalman.o \
./carto/asp/src/mafilter.o \
./carto/asp/src/mecanum.o \
./carto/asp/src/pid.o \
./carto/asp/src/ramp.o 

C_DEPS += \
./carto/asp/src/crc16.d \
./carto/asp/src/dbus.d \
./carto/asp/src/fifo.d \
./carto/asp/src/gauss.d \
./carto/asp/src/kalman.d \
./carto/asp/src/mafilter.d \
./carto/asp/src/mecanum.d \
./carto/asp/src/pid.d \
./carto/asp/src/ramp.d 


# Each subdirectory must supply rules for building sources it contributes
carto/asp/src/%.o: ../carto/asp/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32F4 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/usr/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/app/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/srv/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/asp/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/bsp/inc" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/core" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/device" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


