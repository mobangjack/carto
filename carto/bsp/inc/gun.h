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
 
#ifndef __GUN_H__
#define __GUN_H__

#include "stm32util.h"

#define GUN_PWM_PIN_1 PA0
#define GUN_PWM_PIN_2 PA1

#define GUN_PWM_TIM TIM5
#define GUN_PWM_TIM_PS 83
#define GUN_PWM_TIM_PD 2500
#define GUN_PWM_TIM_PW 1000

#define GUN_PWM1 GUN_PWM_TIM->CCR1
#define GUN_PWM2 GUN_PWM_TIM->CCR2

#define GUN_PWM_H 1800
#define GUN_PWM_L 1000

#define GUN_SET_PWM(pwm) (GUN_PWM1=GUN_PWM2=pwm)
#define GUN_ON()     GUN_SET_PWM(GUN_PWM_H)
#define GUN_OFF()    GUN_SET_PWM(GUN_PWM_L)

void Gun_Config(void);

#endif

