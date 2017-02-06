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

#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint32_t PeriphsState_t; // Peripherals Functional State

#define FS_LED_GREEN      	(((uint32_t)1)<<0)
#define FS_LED_RED        	(((uint32_t)1)<<1)
#define FS_GUN      		(((uint32_t)1)<<2)
#define FS_LASER    		(((uint32_t)1)<<3)
#define FS_SPINNER  		(((uint32_t)1)<<4)
#define FS_ALL      		(FS_LED_GREEN|FS_LED_RED|FS_GUN|FS_LASER|FS_SPINNER)
#define FS_NON       		((uint32_t)0)

typedef struct
{
	float y;
	float p;
}PantiltState_t;

typedef struct
{
	float x;
	float y;
	float z;
}ChassisState_t;

typedef struct
{
	float w1;
	float w2;
	float w3;
	float w4;
}MecanumState_t;

PeriphsState_t FS_Get(PeriphsState_t* fs, PeriphsState_t msk);
void FS_Set(PeriphsState_t* fs, PeriphsState_t msk);
void FS_Clr(PeriphsState_t* fs, PeriphsState_t msk);
void FS_Tog(PeriphsState_t* fs, PeriphsState_t msk);
void CS_Set(ChassisState_t* cs, float x, float y, float z);
void GS_Set(PantiltState_t* gs, float y, float p);
void MS_Set(MecanumState_t* ms, float w1, float w2, float w3, float w4);

#ifdef __cplusplus
}
#endif

#endif

