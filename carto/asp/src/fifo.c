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
	fifo->r = 0;
	fifo->w = 0;
	fifo->n = 0;
}

FIFO_t* FIFO_Create(uint32_t len)
{
	FIFO_t* fifo = (FIFO_t*)malloc(sizeof(FIFO_t));
	if (fifo == NULL) return NULL;
	fifo->buf = (uint8_t*)malloc(len);
	if (fifo->buf == NULL)
	{
		free(fifo);
		fifo = NULL;
		return NULL;
	}
	fifo->len = len;
	fifo->r = 0;
	fifo->w = 0;
	fifo->n = 0;
	return fifo;
}

void FIFO_Flush(FIFO_t* fifo)
{
	fifo->r = 0;
	fifo->w = 0;
	fifo->n = 0;
}

void FIFO_Push(FIFO_t* fifo, uint8_t element)
{
	fifo->buf[fifo->w] = element;
	fifo->w = (fifo->w == fifo->len) ? 0 :  fifo->w + 1;
	fifo->n++;
}

uint8_t FIFO_Pop(FIFO_t* fifo)
{
	uint8_t data = fifo->buf[fifo->r];
	fifo->r = (fifo->r == fifo->len-1) ? 0 :  fifo->r + 1;
	fifo->n--;
	return data;
}

uint8_t FIFO_Peek(FIFO_t* fifo)
{
	return fifo->buf[fifo->r];
}

uint8_t FIFO_IsFull(FIFO_t* fifo)
{
	return fifo->n == fifo->len;
}

uint8_t FIFO_NotFull(FIFO_t* fifo)
{
	return fifo->n != fifo->len;
}

uint8_t FIFO_IsEmpty(FIFO_t* fifo)
{
	return fifo->n == 0;
}

uint8_t FIFO_NotEmpty(FIFO_t* fifo)
{
	return fifo->n != 0;
}

uint32_t FIFO_GetUsed(FIFO_t* fifo)
{
	return fifo->n;
}

uint32_t FIFO_GetFree(FIFO_t* fifo)
{
	return fifo->len - fifo->n;
}

void FIFO_Destroy(FIFO_t* fifo)
{
	free(fifo);
	fifo = NULL;
}

