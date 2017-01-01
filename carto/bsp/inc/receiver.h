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
 
#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "stm32util.h"

#define RECEIVER_SIGNAL_PIN PB7
#define RECEIVER_USART USART1
#define RECEIVER_USART_BR 100000
#define RECEIVER_USART_WL 8
#define RECEIVER_USART_PA 'E'
#define RECEIVER_USART_SB 1
#define RECEIVER_USART_FC 'N'

#define RECEIVER_IRQ_HANDLER IRQ_HANDLER(USART1)
#define RECEIVER_NVIC USART1_IRQn
#define RECEIVER_NVIC_PRE_PRIORITY 0
#define RECEIVER_NVIC_SUB_PRIORITY 0
#define RECEIVER_DMA_STREAM DMA2_Stream2
#define RECEIVER_DMA_CHANNEL DMA_Channel_4

#define RECEIVER_FRAME_LEN 18u
#define RECEIVER_DMA_BUF_SIZE 36u

void Receiver_Config(void);

void Receiver_Callback(uint8_t* dbuf);

#endif
