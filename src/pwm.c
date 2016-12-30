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
 
#include "pwm.h"

void PWM_Config(void)
{
    GPIO_AF(PWM_PIN_1, PWM_GPIO_AF);
    GPIO_AF(PWM_PIN_2, PWM_GPIO_AF);

    TIM_Config(PWM_TIM, 83, TIM_CounterMode_Up, 2500, TIM_CKD_DIV1);
    TIM_OC_Config(PWM_TIM, 0xff, TIM_OCMode_PWM2, 1000);
	
	TIM_ARRPreloadConfig(PWM_TIM, ENABLE);
	
	PWM_OFF();
}
