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
 
#ifndef __SPINER_H__
#define __SPINER_H__

#include "stm32util.h"

// SPINER_PWM_PIN      ---PA2(TIM9_CH1)
// SPINER_ENCODER_PIN_A---PB4(TIM3_CH1)
// SPINER_ENCODER_PIN_B---PB5(TIM3_CH2)

#define SPINER_PWM_PIN PA2
#define SPINER_PWM_TIM TIM9
#define SPINER_PWM SPINER_PWM_TIM->CCR1

#define SPINER_ENCODER_PIN_A PB4
#define SPINER_ENCODER_PIN_B PB5
#define SPINER_ENCODER_TIM TIM3

#define SPINER_DIR 1
#define SPINER_ENCODER_OFFSET 0x7fff
#define SPINER_ENCODER_CNT() (SPINER_DIR?(SPINER_TIM->CNT-SPINER_OFFSET):(SPINER_OFFSET-SPINER_TIM->CNT))
#define SPINER_ENCODER_START() (SPINER_ENCODER_TIM->CNT = SPINER_ENCODER_OFFSET)

void Spinner_EncoderConfig(void);
void Spinner_PWMConfig(void);
void Spinner_Config(void);

#endif
