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
 
#include "com.h"

/***********************************/
/*          Communication          */
/***********************************/

static uint8_t buf[COM_RX_FIFO_SIZE];
static FIFO_t fifo;

void Com_Init()
{
	FIFO_Init(&fifo, buf, COM_RX_FIFO_SIZE);
}

void Com_Proc()
{
	uint32_t len = FIFO_GetUsed(&fifo);
	if (len > 0) {
		while (FIFO_NotEmpty(&fifo)) {
			Tty_WriteByte(FIFO_Pop(&fifo));
		}
	}
}

void Tty_Proc(uint8_t data)
{
	Wdg_Feed(WDG_IDX_COM);
	if (FIFO_NotFull(&fifo)) {
		FIFO_Push(&fifo, data);
	}
}
