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
 
#include "encoder.h"

//INPUT_A---PB4(TIM3_CH1)
//INPUT_B---PB5(TIM3_CH2)

void Encoder_Config(void)
{
	GPIO_Encoder(
			ENCODER_PIN_A,
			ENCODER_PIN_B,
			ENCODER_TIM,
			TIM_EncoderMode_TI12,
			TIM_ICPolarity_Falling,
			TIM_ICPolarity_Falling
			);
	
	ENCODER_START();
}

