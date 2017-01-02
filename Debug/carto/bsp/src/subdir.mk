################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../carto/bsp/src/startup_stm32.s 

C_SRCS += \
../carto/bsp/src/bsp.c \
../carto/bsp/src/can1.c \
../carto/bsp/src/can2.c \
../carto/bsp/src/delay.c \
../carto/bsp/src/flash.c \
../carto/bsp/src/gun.c \
../carto/bsp/src/laser.c \
../carto/bsp/src/led.c \
../carto/bsp/src/motor.c \
../carto/bsp/src/mpu6050.c \
../carto/bsp/src/mpu6050_drv.c \
../carto/bsp/src/mpu6050_i2c.c \
../carto/bsp/src/mpu6050_int.c \
../carto/bsp/src/rcv.c \
../carto/bsp/src/spinner.c \
../carto/bsp/src/stm32util.c \
../carto/bsp/src/system_stm32f4xx.c \
../carto/bsp/src/tim.c \
../carto/bsp/src/tty.c \
../carto/bsp/src/zgyro.c 

OBJS += \
./carto/bsp/src/bsp.o \
./carto/bsp/src/can1.o \
./carto/bsp/src/can2.o \
./carto/bsp/src/delay.o \
./carto/bsp/src/flash.o \
./carto/bsp/src/gun.o \
./carto/bsp/src/laser.o \
./carto/bsp/src/led.o \
./carto/bsp/src/motor.o \
./carto/bsp/src/mpu6050.o \
./carto/bsp/src/mpu6050_drv.o \
./carto/bsp/src/mpu6050_i2c.o \
./carto/bsp/src/mpu6050_int.o \
./carto/bsp/src/rcv.o \
./carto/bsp/src/spinner.o \
./carto/bsp/src/startup_stm32.o \
./carto/bsp/src/stm32util.o \
./carto/bsp/src/system_stm32f4xx.o \
./carto/bsp/src/tim.o \
./carto/bsp/src/tty.o \
./carto/bsp/src/zgyro.o 

C_DEPS += \
./carto/bsp/src/bsp.d \
./carto/bsp/src/can1.d \
./carto/bsp/src/can2.d \
./carto/bsp/src/delay.d \
./carto/bsp/src/flash.d \
./carto/bsp/src/gun.d \
./carto/bsp/src/laser.d \
./carto/bsp/src/led.d \
./carto/bsp/src/motor.d \
./carto/bsp/src/mpu6050.d \
./carto/bsp/src/mpu6050_drv.d \
./carto/bsp/src/mpu6050_i2c.d \
./carto/bsp/src/mpu6050_int.d \
./carto/bsp/src/rcv.d \
./carto/bsp/src/spinner.d \
./carto/bsp/src/stm32util.d \
./carto/bsp/src/system_stm32f4xx.d \
./carto/bsp/src/tim.d \
./carto/bsp/src/tty.d \
./carto/bsp/src/zgyro.d 


# Each subdirectory must supply rules for building sources it contributes
carto/bsp/src/%.o: ../carto/bsp/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32F4 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/usr/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/app/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/srv/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/asp/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/bsp/inc" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/core" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/device" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

carto/bsp/src/%.o: ../carto/bsp/src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/usr/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/app/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/srv/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/asp/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/bsp/inc" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/core" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/device" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


