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
 
#ifndef __COM_H__
#define __COM_H__

#include "stm32util.h"
#include "fifo.h"
#include <stdio.h>

/* COM Port, USE USART3 BY DEFAULT */

/*-----USART3_TX-----PB10-----*/
/*-----USART3_RX-----PB11-----*/
#define COM_TX_PIN PB10
#define COM_RX_PIN PB11
#define COM_USART USART3
#define COM_BR 115200
#define COM_WL 8
#define COM_PR 'N'
#define COM_SB 1
#define COM_FC 'N'

#define COM_NVIC USART3_IRQn
#define COM_NVIC_PRE_PRIORITY 1
#define COM_NVIC_SUB_PRIORITY 0

#define COM_IRQ_HANDLER IRQ_HANDLER(USART3)

#define COM_TX_FIFO_SIZE 256u

void COM_Config(void);

void COM_WriteByte(u8 byte);
void COM_Write(u8* pdata, u8 len);

void COM_Callback(u8 data);

#endif
