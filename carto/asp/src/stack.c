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

#include "stack.h"

void Stack_Init(Stack_t* stack, uint8_t* buf, uint32_t size)
{
	stack->buf = buf;
	stack->size = size;
	Stack_Dump(stack);
}

void Stack_Dump(Stack_t* stack)
{
	memset(stack->buf, 0, stack->size * sizeof(uint8_t));
	stack->p = 0;
}

void Stack_Push(Stack_t* stack, uint8_t element)
{
	stack->buf[stack->p++] = element;
}

uint8_t Stack_Pop(Stack_t* stack)
{
	return stack->buf[stack->p--];
}

uint8_t Stack_Peek(const Stack_t* stack)
{
	return stack->buf[stack->p];
}

uint8_t Stack_GetSize(const Stack_t* stack)
{
	return stack->size;
}

uint32_t Stack_GetUsed(const Stack_t* stack)
{
	return stack->p;
}

uint32_t Stack_GetFree(const Stack_t* stack)
{
	return stack->size - stack->p;
}

uint8_t Stack_IsFull(const Stack_t* stack)
{
	return stack->p == stack->size;
}

uint8_t Stack_NotFull(const Stack_t* stack)
{
	return stack->p < stack->size;
}

uint8_t Stack_IsEmpty(const Stack_t* stack)
{
	return stack->p == 0;
}

uint8_t Stack_NotEmpty(const Stack_t* stack)
{
	return stack->p != 0;
}

Stack_t* Stack_Create(uint32_t size)
{
	Stack_t* stack = (Stack_t*)malloc(sizeof(Stack_t));
	if (stack == NULL) {
		return NULL;
	}
	stack->buf = (uint8_t*)malloc(size);
	if (stack->buf == NULL) {
		free(stack);
		stack = NULL;
		return NULL;
	}
	stack->size = size;
	stack->p = 0;
	return stack;
}

void Stack_Destroy(Stack_t* stack)
{
	if (stack != NULL) {
		if (stack->buf != NULL) {
			free(stack->buf);
			stack->buf = NULL;
		}
		free(stack);
		stack = NULL;
	}
}
