/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
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

#ifndef __MAFILTER_H__
#define __MAFILTER_H__

#ifdef __cpluplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct MAFilter_t
{
	float* buf;
	uint32_t len;
	uint32_t i;
	float delta;
	float sum;
	float out;
}MAFilter_t;

void MAFilter_Init(MAFilter_t* mafilter, float* buf, uint32_t len);
MAFilter_t* MAFilter_Create(uint32_t len);
float MAFilter_Calc(MAFilter_t* mafilter, float v);
void MAFilter_Reset(MAFilter_t* mafilter);
void MAFilter_Destroy(MAFilter_t* mafilter);

#ifdef __cpluplus
}
#endif

#endif /* __MAFILTER_H__ */
