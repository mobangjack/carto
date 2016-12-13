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
 
#include "main.h"
/*-PWM1---(PA0---TIM5_CH1)--*/
/*-PWM2---(PA1---TIM5_CH2)--*/

void PWM_Config(void)
{
    GPIO_InitTypeDef          gpio;
    TIM_TimeBaseInitTypeDef   tim;
    TIM_OCInitTypeDef         oc;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA ,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   //PCLK1=42MHz,TIM5 clk =84MHz
	
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	
	// TIM5
	tim.TIM_Prescaler = 84-1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 2500;   //2.5ms
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&tim);

	oc.TIM_OCMode = TIM_OCMode_PWM2;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OutputNState = TIM_OutputState_Disable;
	oc.TIM_Pulse = 1000;
	oc.TIM_OCPolarity = TIM_OCPolarity_Low;
	oc.TIM_OCNPolarity = TIM_OCPolarity_High;
	oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
	
	TIM_OC1Init(TIM5,&oc);
	TIM_OC2Init(TIM5,&oc);
	
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	
	TIM_Cmd(TIM5,ENABLE);
	
	SET_PWM(PWM_OFF);

}
