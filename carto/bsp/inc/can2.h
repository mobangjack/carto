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
 
#ifndef __CAN2_H__
#define __CAN2_H__

#include "stm32util.h"

#define CAN2_RX_PIN PB12
#define CAN2_TX_PIN PB13
#define CAN2_RX_IRQ_HANDLER IRQ_HANDLER(CAN2_RX0)
#define CAN2_RX_NVIC IRQ(CAN2_RX0)
#define CAN2_RX_NVIC_PRE_PRIORITY 1
#define CAN2_RX_NVIC_SUB_PRIORITY 0
#define CAN2_TX_IRQ_HANDLER IRQ_HANDLER(CAN2_TX)
#define CAN2_TX_NVIC IRQ(CAN2_TX)
#define CAN2_TX_NVIC_PRE_PRIORITY 0
#define CAN2_TX_NVIC_SUB_PRIORITY 1

void Can2_Config();

void Can2RxCallback(uint32_t id, uint8_t* data);

#endif 
