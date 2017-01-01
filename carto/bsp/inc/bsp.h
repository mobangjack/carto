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
 
#ifndef __BSP_H__
#define __BSP_H__

#include "can1.h"
#include "can2.h"
#include "delay.h"
#include "flash.h"
#include "gun.h"
#include "laser.h"
#include "led.h"
#include "motor.h"
#include "mpu6050.h"
#include "rcv.h"
#include "spiner.h"
#include "zgyro.h"
#include "tim.h"
#include "tty.h"

void BSP_Config(void);

#endif

