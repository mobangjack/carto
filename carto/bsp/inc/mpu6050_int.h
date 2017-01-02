/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
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

#ifndef __MPU6050_INT_H__
#define __MPU6050_INT_H__

#include "stm32util.h"

#define MPU6050_INT_PIN PA4
#define MPU6050_NVIC EXTI4_IRQn
#define MPU6050_NVIC_PRE_PRIORITY 2
#define MPU6050_NVIC_SUB_PRIORITY 0
#define MPU6050_EXTI_LINE GPIO_PIN_MSK(MPU6050_INT_PIN)
#define MPU6050_IRQ_HANDLER IRQ_HANDLER(EXTI4)

void MPU6050_INT_Config(void);

void MPU6050_INT_Callback();

#endif
