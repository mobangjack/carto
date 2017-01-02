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
 
#ifndef __SPINNER_H__
#define __SPINNER_H__

#include "stm32util.h"

#define SPINNER_PWM_PIN PA2
#define SPINNER_PWM_TIM TIM9
#define SPINNER_PWM SPINNER_PWM_TIM->CCR1

#define SPINNER_ENCODER_PIN_A PB4
#define SPINNER_ENCODER_PIN_B PB5
#define SPINNER_ENCODER_TIM TIM3

#define SPINNER_DIR 1
#define SPINNER_ENCODER_OFFSET 0x7fff
#define SPINNER_ENCODER_CNT() (SPINNER_DIR?(SPINNER_TIM->CNT-SPINNER_OFFSET):(SPINNER_OFFSET-SPINNER_TIM->CNT))
#define SPINNER_ENCODER_START() (SPINNER_ENCODER_TIM->CNT = SPINNER_ENCODER_OFFSET)

void Spinner_EncoderConfig(void);
void Spinner_PWMConfig(void);
void Spinner_Config(void);

#endif
