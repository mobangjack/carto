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

typedef struct
{
	uint32_t scale;
	uint32_t count;
}Ramp_t;

void Ramp_Config(Ramp_t* ramp, uint32_t scale);
float Ramp_Calc(Ramp_t* ramp);
void Ramp_Reset(Ramp_t* ramp);
uint8_t Ramp_IsOverflow(const Ramp_t* ramp);

#define RAMP(SCALE) { \
	.scale = SCALE, \
	.count = 0, \
}
	
#ifdef __cpluplus
}
#endif

#endif

