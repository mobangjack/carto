/**
 * Copyright (c) 2011-2016, Jack Mo (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef __MAIN_H__
#define __MAIN_H__

// chip support
#include "stm32f4xx.h"

// standard c libraries
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

// board related headers
#include "bsp.h"
#include "led.h"
#include "pwm.h"
#include "imu.h"
#include "can1.h"
#include "can2.h"
#include "tim2.h"
#include "tim6.h"
#include "usart1.h"
#include "usart3.h"
#include "quad_encoder.h"

// peripherals
#include "motor.h"
#include "zgyro.h"
#include "encoder.h"

// kits
#include "pid.h"
#include "ramp.h"
#include "fifo.h"
#include "dbus.h"
#include "delay.h"
#include "crc16.h"
#include "mecanum.h"

// services and callbacks
#include "can1call.h"
#include "can2call.h"
#include "dbuscall.h"
#include "control.h"
#include "odom.h"
#include "superviser.h"

// commonly used macros
#define PI 3.1415926f
#define PI2 6.2831855f
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)

#endif 
