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

#ifndef __TIM_H__
#define __TIM_H__

#include "stm32util.h"

// Tick timer
#define TICK_TIM TIM2
#define TICK_TIM_PS 83
#define TICK_TIM_PD 0xFFFFFFFF
#define TICK_TIM_NVIC TIM6_DAC_IRQn
#define TICK_TIM_NVIC_PRE_PRIORITY 0
#define TICK_TIM_NVIC_SUB_PRIORITY 0
#define TICK_TIM_IRQ_HANDLER IRQ_HANDLER(TIM2)
#define TICK_US() TICK_TIM->CNT

// Sync timer
#define SYNC_TIM TIM6
#define SYNC_TIM_PS 83
#define SYNC_TIM_PD 1000
#define SYNC_TIM_NVIC TIM6_DAC_IRQn
#define SYNC_TIM_NVIC_PRE_PRIORITY 1
#define SYNC_TIM_NVIC_SUB_PRIORITY 0
#define SYNC_TIM_IRQ_HANDLER IRQ_HANDLER(TIM6_DAC)

void TickTim_Config(void);
void TickTim_Start(void);
void TickTim_Stop(void);

void SyncTim_Config(void);
void SyncTim_Start(void);
void SyncTim_Stop(void);

void Tim_Config(void);
void Tim_Start(void);
void Tim_Stop(void);

void TickTim_Callback(void);
void SyncTim_Callback(void);

#endif /* __TIM_H__ */
