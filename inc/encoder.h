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
 
#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "stm32util.h"

//INPUT_A---PB4(TIM3_CH1)
//INPUT_B---PB5(TIM3_CH2)

#define ENCODER_PIN_A PB4
#define ENCODER_PIN_B PB5
#define ENCODER_TIM TIM3

#define ENCODER_DIR 1
#define ENCODER_OFFSET 0x7fff
#define ENCODER_CNT() (ENCODER_DIR?(ENCODER_TIM->CNT-ENCODER_OFFSET):(ENCODER_OFFSET-ENCODER_TIM->CNT))
#define ENCODER_START() (ENCODER_TIM->CNT = ENCODER_OFFSET)

void Encoder_Config(void);

#endif
