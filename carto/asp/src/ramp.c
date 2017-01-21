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
 
#include "ramp.h"

void Ramp_Config(Ramp_t* ramp, uint32_t scale)
{
	ramp->scale = scale;
}

float Ramp_Calc(Ramp_t* ramp)
{
	if(ramp->count < ramp->scale)
	{
		ramp->count++;
		return ramp->count / (float)ramp->scale;
	}
	return 1;
}

void Ramp_Reset(Ramp_t* ramp)
{
	ramp->count = 0;
}

uint8_t Ramp_IsOverflow(const Ramp_t* ramp)
{
	return ramp->count >= ramp->scale;
}
