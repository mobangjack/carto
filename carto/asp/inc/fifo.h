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
 
#ifndef __FIFO_H__
#define __FIFO_H__

#ifdef __cpluplus
extern "C" {
#endif
	
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
	
typedef struct FIFO
{
	uint8_t* buf;
	uint32_t len;
	uint32_t r;
	uint32_t w;
	uint32_t n;
}FIFO_t;

void FIFO_Init(FIFO_t* fifo, uint8_t* buf, uint32_t len);
void FIFO_Flush(FIFO_t* fifo);
void FIFO_Push(FIFO_t* fifo, uint8_t element);
uint8_t FIFO_Pop(FIFO_t* fifo);
uint8_t FIFO_Peek(const FIFO_t* fifo);
uint8_t FIFO_IsFull(const FIFO_t* fifo);
uint8_t FIFO_NotFull(const FIFO_t* fifo);
uint8_t FIFO_IsEmpty(const FIFO_t* fifo);
uint8_t FIFO_NotEmpty(const FIFO_t* fifo);
uint32_t FIFO_GetSize(const FIFO_t* fifo);
uint32_t FIFO_GetUsed(const FIFO_t* fifo);
uint32_t FIFO_GetFree(const FIFO_t* fifo);

FIFO_t* FIFO_Create(uint32_t len);
void FIFO_Destroy(FIFO_t* fifo);

#ifdef __cpluplus
}
#endif
	
#endif
