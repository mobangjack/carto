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
#define TICK_TIM_NVIC IRQ(TIM2)
#define TICK_TIM_NVIC_PRE_PRIORITY 0
#define TICK_TIM_NVIC_SUB_PRIORITY 0
#define TICK_TIM_IRQ_HANDLER IRQ_HANDLER(TIM2)
#define TICK_US() TICK_TIM->CNT

// Sync timer
#define SYNC_TIM TIM6
#define SYNC_TIM_PS 83
#define SYNC_TIM_PD 1000
#define SYNC_TIM_NVIC IRQ(TIM6_DAC)
#define SYNC_TIM_NVIC_PRE_PRIORITY 1
#define SYNC_TIM_NVIC_SUB_PRIORITY 1
#define SYNC_TIM_IRQ_HANDLER IRQ_HANDLER(TIM6_DAC)

void TickTim_Config();
void TickTim_Start();
void TickTim_Stop();

void SyncTim_Config();
void SyncTim_Start();
void SyncTim_Stop();

void Tim_Config();
void Tim_Start();
void Tim_Stop();

void TickTimCallback();
void SyncTimCallback();

#endif /* __TIM_H__ */
