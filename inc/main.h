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

// chip series
#include "stm32f4xx.h"

// standard c libraries
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

// board supported packages
#include "bsp.h"
#include "led.h"
#include "pwm.h"
#include "can1.h"
#include "can2.h"
#include "tim2.h"
#include "tim6.h"
#include "usart1.h"
#include "usart3.h"
#include "quad_encoder.h"

// peripherals
#include "imu.h"
#include "motor.h"
#include "zgyro.h"

// kits
#include "pid.h"
#include "ramp.h"
#include "fifo.h"
#include "delay.h"
#include "crc16.h"
#include "encoder.h"
#include "mecanum.h"
#include "mafilter.h"

// codec
#include "rc_codec.h"
#include "hc_codec.h"
#include "dbus_codec.h"

// command sources
#include "sys_cmd.h"
#include "rc_cmd.h"
#include "hc_cmd.h"
#include "dbus_cmd.h"

// services and calls
#include "cali.h"
#include "odom.h"
#include "control.h"
#include "can1call.h"
#include "can2call.h"
#include "superviser.h"

// commonly used macros
#define PI 3.1415926f
#define PI2 6.2831855f
#define PIOVER180 (PI/180.f)
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)

#endif 
