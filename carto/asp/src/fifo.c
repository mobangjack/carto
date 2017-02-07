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

void FIFO_Init(FIFO_t* fifo, uint8_t* buf, uint32_t len)
{
	fifo->buf = buf;
	fifo->len = len;
	FIFO_Flush(fifo);
}

void FIFO_Flush(FIFO_t* fifo)
{
	memset(fifo->buf, 0, fifo->len * sizeof(uint8_t));
	fifo->r = 0;
	fifo->w = 0;
	fifo->n = 0;
}

void FIFO_Push(FIFO_t* fifo, uint8_t element)
{
	fifo->buf[fifo->w++] = element;
	if (fifo->w == fifo->len) fifo->w = 0;
	fifo->n++;
}

uint8_t FIFO_Pop(FIFO_t* fifo)
{
	uint8_t data = fifo->buf[fifo->r++];
	if (fifo->r == fifo->len) fifo->r = 0;
	fifo->n--;
	return data;
}

uint8_t FIFO_Peek(const FIFO_t* fifo)
{
	return fifo->buf[fifo->r];
}

uint8_t FIFO_IsFull(const FIFO_t* fifo)
{
	return fifo->n == fifo->len;
}

uint8_t FIFO_NotFull(const FIFO_t* fifo)
{
	return fifo->n != fifo->len;
}

uint8_t FIFO_IsEmpty(const FIFO_t* fifo)
{
	return fifo->n == 0;
}

uint8_t FIFO_NotEmpty(const FIFO_t* fifo)
{
	return fifo->n != 0;
}

uint32_t FIFO_GetSize(const FIFO_t* fifo)
{
	return fifo->len;
}

uint32_t FIFO_GetUsed(const FIFO_t* fifo)
{
	return fifo->n;
}

uint32_t FIFO_GetFree(const FIFO_t* fifo)
{
	return fifo->len - fifo->n;
}

FIFO_t* FIFO_Create(uint32_t len)
{
	FIFO_t* fifo = (FIFO_t*)malloc(sizeof(FIFO_t));
	if (fifo == NULL) return NULL;
	memset(fifo, 0, sizeof(FIFO_t));
	fifo->buf = (uint8_t*)malloc(len);
	if (fifo->buf == NULL)
	{
		free(fifo);
		fifo = NULL;
		return NULL;
	}
	fifo->len = len;
	FIFO_Flush(fifo);
	return fifo;
}

void FIFO_Destroy(FIFO_t* fifo)
{
	if (fifo != NULL) {
		if (fifo->buf != NULL) {
			free(fifo->buf);
			fifo->buf = NULL;
		}
		free(fifo);
		fifo = NULL;
	}

}

