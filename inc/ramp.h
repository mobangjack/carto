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
 
#ifndef __RAMP_H__
#define __RAMP_H__

#ifdef __cpluplus
extern "C" {
#endif

#include <stdint.h>

#define RAMP_SCALE_DEFAULT 4000
	
typedef struct
{
	uint32_t count;
	uint32_t scale;
	float output;
	void (*Init)(struct Ramp_t* ramp, uint32_t scale);
	float (*Calc)(struct Ramp_t* ramp);
	void (*SetCounter)(struct Ramp_t* ramp, uint32_t count);
	void (*ResetCounter)(struct Ramp_t* ramp);
	void (*SetScale)(struct Ramp_t* ramp, uint32_t scale);
	uint8_t (*IsOverflow)(struct Ramp_t* ramp);
}Ramp_t;

void Ramp_Init(Ramp_t* ramp, uint32_t scale);
float Ramp_Calc(Ramp_t* ramp);
void Ramp_SetCounter(Ramp_t* ramp, uint32_t count);
void Ramp_ResetCounter(Ramp_t* ramp);
void Ramp_SetScale(Ramp_t* ramp, uint32_t scale);
uint8_t Ramp_IsOverflow(Ramp_t* ramp);

#define RAMP_DEFAULT { \
	.count = 0, \
	.scale = RAMP_SCALE_DEFAULT, \
	.output = 0, \
	.Init = &Ramp_Init, \
	.Calc = &Ramp_Calc, \
	.SetCounter = &Ramp_SetCounter, \
	.ResetCounter = &Ramp_ResetCounter, \
	.SetScale = &Ramp_SetScale, \
	.IsOverflow = Ramp_IsOverflow, \
} \
	
#ifdef __cpluplus
}
#endif

#endif

