################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp.c \
../src/can1.c \
../src/can1_task.c \
../src/can2.c \
../src/can2_task.c \
../src/control_task.c \
../src/crc16.c \
../src/dbus.c \
../src/dbus_task.c \
../src/delay.c \
../src/encoder.c \
../src/fifo.c \
../src/led.c \
../src/main.c \
../src/mecanum.c \
../src/motor.c \
../src/odom_task.c \
../src/pid.c \
../src/pwm.c \
../src/quad_encoder.c \
../src/ramp.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/timer.c \
../src/usart1.c \
../src/usart3.c \
../src/zgyro.c 

OBJS += \
./src/bsp.o \
./src/can1.o \
./src/can1_task.o \
./src/can2.o \
./src/can2_task.o \
./src/control_task.o \
./src/crc16.o \
./src/dbus.o \
./src/dbus_task.o \
./src/delay.o \
./src/encoder.o \
./src/fifo.o \
./src/led.o \
./src/main.o \
./src/mecanum.o \
./src/motor.o \
./src/odom_task.o \
./src/pid.o \
./src/pwm.o \
./src/quad_encoder.o \
./src/ramp.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/timer.o \
./src/usart1.o \
./src/usart3.o \
./src/zgyro.o 

C_DEPS += \
./src/bsp.d \
./src/can1.d \
./src/can1_task.d \
./src/can2.d \
./src/can2_task.d \
./src/control_task.d \
./src/crc16.d \
./src/dbus.d \
./src/dbus_task.d \
./src/delay.d \
./src/encoder.d \
./src/fifo.d \
./src/led.d \
./src/main.d \
./src/mecanum.d \
./src/motor.d \
./src/odom_task.d \
./src/pid.d \
./src/pwm.d \
./src/quad_encoder.d \
./src/ramp.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/timer.d \
./src/usart1.d \
./src/usart3.d \
./src/zgyro.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32F4 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib" -I"/home/bj/workspace/eclipse/stm32/car/inc" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/core" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/device" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


