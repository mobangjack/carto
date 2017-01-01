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
 
#ifndef __TTY_H__
#define __TTY_H__

#include "stm32util.h"
#include "fifo.h"
#include <stdio.h>

#define TTY_TX_PIN PB10
#define TTY_RX_PIN PB11
#define TTY_USART USART3
#define TTY_USART_BR 115200
#define TTY_USART_WL 8
#define TTY_USART_PA 'N'
#define TTY_USART_SB 1
#define TTY_USART_FC 'N'

#define TTY_IRQ_HANDLER IRQ_HANDLER(USART3)
#define TTY_NVIC USART3_IRQn
#define TTY_NVIC_PRE_PRIORITY 1
#define TTY_NVIC_SUB_PRIORITY 0

#define TTY_TX_FIFO_SIZE 256u

void TTY_Config(void);

void TTY_WriteByte(u8 byte);
void TTY_Write(u8* pdata, u8 len);

void TTY_RX_Callback(u8 data);

#endif
