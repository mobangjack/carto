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
 
#ifndef __RC_H__
#define __RC_H__

#include "stm32util.h"

#define RC_USART USART1
#define RC_NVIC USART1_IRQn
#define RC_IRQ_HANDLER() IRQ_HANDLER(USART1)
#define RC_DMA_STREAM DMA2_Stream2
#define RC_DMA_CHANNEL DMA_Channel_4
#define RC_SIGNAL_PIN PB7

#define RC_FRAME_LEN 18u
#define RC_DMA_BUF_SIZE 36u

void RC_Config(void);

extern void RC_Callback(uint8_t* dbuf);

#endif
