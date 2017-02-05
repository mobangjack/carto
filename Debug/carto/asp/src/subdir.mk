################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../carto/asp/src/ahrs.c \
../carto/asp/src/cbus.c \
../carto/asp/src/crc16.c \
../carto/asp/src/dbus.c \
../carto/asp/src/est.c \
../carto/asp/src/fifo.c \
../carto/asp/src/gauss.c \
../carto/asp/src/gdf.c \
../carto/asp/src/imu.c \
../carto/asp/src/kalman.c \
../carto/asp/src/mafilter.c \
../carto/asp/src/mag.c \
../carto/asp/src/mecanum.c \
../carto/asp/src/pid.c \
../carto/asp/src/ramp.c \
../carto/asp/src/sta.c \
../carto/asp/src/stack.c 

OBJS += \
./carto/asp/src/ahrs.o \
./carto/asp/src/cbus.o \
./carto/asp/src/crc16.o \
./carto/asp/src/dbus.o \
./carto/asp/src/est.o \
./carto/asp/src/fifo.o \
./carto/asp/src/gauss.o \
./carto/asp/src/gdf.o \
./carto/asp/src/imu.o \
./carto/asp/src/kalman.o \
./carto/asp/src/mafilter.o \
./carto/asp/src/mag.o \
./carto/asp/src/mecanum.o \
./carto/asp/src/pid.o \
./carto/asp/src/ramp.o \
./carto/asp/src/sta.o \
./carto/asp/src/stack.o 

C_DEPS += \
./carto/asp/src/ahrs.d \
./carto/asp/src/cbus.d \
./carto/asp/src/crc16.d \
./carto/asp/src/dbus.d \
./carto/asp/src/est.d \
./carto/asp/src/fifo.d \
./carto/asp/src/gauss.d \
./carto/asp/src/gdf.d \
./carto/asp/src/imu.d \
./carto/asp/src/kalman.d \
./carto/asp/src/mafilter.d \
./carto/asp/src/mag.d \
./carto/asp/src/mecanum.d \
./carto/asp/src/pid.d \
./carto/asp/src/ramp.d \
./carto/asp/src/sta.d \
./carto/asp/src/stack.d 


# Each subdirectory must supply rules for building sources it contributes
carto/asp/src/%.o: ../carto/asp/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32F4 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/usr/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/app/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/srv/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/asp/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/bsp/inc" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/core" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/device" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


