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
 
#include "fifo.h"

FIFO* FIFO_Create(uint32_t len)
{
	FIFO* fifo = (FIFO*)malloc(sizeof(FIFO));
	if (fifo == NULL) return NULL;
	fifo->buf = (uint8_t*)malloc(len);
	if (fifo->buf == NULL)
	{
		free(fifo);
		fifo = NULL;
		return NULL;
	}
	fifo->len = len;
	fifo->r = fifo->buf;
	fifo->w = fifo->buf;
	fifo->cnt = 0;
	return fifo;
}

uint8_t FIFO_Push(FIFO* fifo, uint8_t element)
{
	if (fifo->cnt == fifo->len) {
		return 0;
	}
	*fifo->w = element;
	fifo->w = (fifo->w == (fifo->buf+fifo->len-1)) ? fifo->buf :  fifo->w + 1;
	fifo->cnt++;
	return 1;
}

uint8_t FIFO_Pop(FIFO* fifo)
{
	if (fifo->cnt == 0) {
		return 0;
	} else {
		uint8_t data = *fifo->r;
		fifo->r = (fifo->r == (fifo->buf+fifo->len-1)) ? fifo->buf :  fifo->r + 1;
		fifo->cnt--;
		return data;
	}

}

uint8_t FIFO_Peek(FIFO* fifo)
{
	if (fifo->cnt == 0) {
		return 0;
	}
	return *fifo->r;
}

uint8_t FIFO_IsFull(FIFO* fifo)
{
	return fifo->cnt == fifo->len;
}

uint8_t FIFO_IsEmpty(FIFO* fifo)
{
	return fifo->cnt == 0;
}

uint32_t FIFO_GetUsed(FIFO* fifo)
{
	return fifo->cnt;
}

uint32_t FIFO_GetFree(FIFO* fifo)
{
	return fifo->len - fifo->cnt;
}

void FIFO_Destroy(FIFO* fifo)
{
	free(fifo);
	fifo = NULL;
}

