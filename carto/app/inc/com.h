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

/***********************************/
/*          Communication          */
/***********************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tty.h"
#include "wdg.h"

#define COM_RX_FIFO_SIZE 256u

typedef struct
{
	uint8_t header;
	uint8_t length;
	uint16_t crc;
}ComFmt_t;

#define COM_FMT_ACI \
{ \
	.header = 0xab, \
	.length = 16, \
	.crc = 0xabcd, \
}

#define COM_MSG_ACI 0
#define COM_MOD_CFG 0x01
#define COM_MOD_API 0x01

void Com_Init();
void Com_Proc();

void Tty_Proc(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif
