################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../carto/app/src/aci.c \
../carto/app/src/act.c \
../carto/app/src/app.c \
../carto/app/src/can.c \
../carto/app/src/cfg.c \
../carto/app/src/clk.c \
../carto/app/src/cmd.c \
../carto/app/src/com.c \
../carto/app/src/ctl.c \
../carto/app/src/hci.c \
../carto/app/src/ins.c \
../carto/app/src/odo.c \
../carto/app/src/pwr.c \
../carto/app/src/rci.c \
../carto/app/src/wdg.c 

OBJS += \
./carto/app/src/aci.o \
./carto/app/src/act.o \
./carto/app/src/app.o \
./carto/app/src/can.o \
./carto/app/src/cfg.o \
./carto/app/src/clk.o \
./carto/app/src/cmd.o \
./carto/app/src/com.o \
./carto/app/src/ctl.o \
./carto/app/src/hci.o \
./carto/app/src/ins.o \
./carto/app/src/odo.o \
./carto/app/src/pwr.o \
./carto/app/src/rci.o \
./carto/app/src/wdg.o 

C_DEPS += \
./carto/app/src/aci.d \
./carto/app/src/act.d \
./carto/app/src/app.d \
./carto/app/src/can.d \
./carto/app/src/cfg.d \
./carto/app/src/clk.d \
./carto/app/src/cmd.d \
./carto/app/src/com.d \
./carto/app/src/ctl.d \
./carto/app/src/hci.d \
./carto/app/src/ins.d \
./carto/app/src/odo.d \
./carto/app/src/pwr.d \
./carto/app/src/rci.d \
./carto/app/src/wdg.d 


# Each subdirectory must supply rules for building sources it contributes
carto/app/src/%.o: ../carto/app/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32F4 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/usr/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/app/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/srv/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/asp/inc" -I"/home/bj/workspace/eclipse/stm32/carto_alpha/carto/bsp/inc" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/core" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/CMSIS/device" -I"/home/bj/workspace/eclipse/stm32/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


