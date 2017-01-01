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
 
#include "spiner.h"

void Spinner_EncoderConfig(void)
{
	Encoder_Bind(
			SPINER_ENCODER_PIN_A,
			SPINER_ENCODER_PIN_B,
			SPINER_ENCODER_TIM,
			TIM_EncoderMode_TI12,
			TIM_ICPolarity_Falling,
			TIM_ICPolarity_Falling
			);
	TIM_Cmd(SPINER_ENCODER_TIM, ENABLE);
	SPINER_ENCODER_START();
}

void Spinner_PWMConfig(void)
{
	PWM_Bind(SPINER_PWM_TIM, 0, 0, 0, SPINER_PWM_TIM, 167, 1000, 0);
	TIM_Cmd(SPINER_PWM_TIM, ENABLE);
}

void Spinner_Config(void)
{
	Spinner_EncoderConfig();
	Spinner_PWMConfig();
}
