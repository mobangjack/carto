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

/****************************************/
/*        Moving Average Filter         */
/****************************************/

#include "mafilter.h"

void MAFilter_Init(MAFilter_t* mafilter, float* buf, uint32_t len)
{
	mafilter->buf = buf;
	mafilter->len = len;
	mafilter->i = 0;
	mafilter->delta = 0;
	mafilter->sum = 0;
	mafilter->out = 0;
}

MAFilter_t* MAFilter_Create(uint32_t len)
{
	MAFilter_t* mafilter = (MAFilter_t*)malloc(sizeof(MAFilter_t));
	if(mafilter == NULL) return NULL;
	mafilter->buf = (float*)malloc(sizeof(float)*len);
	if(mafilter->buf == NULL) {
		free(mafilter);
		mafilter = NULL;
		return NULL;
	}
	mafilter->len = len;
	for(mafilter->i = 0; mafilter->i < mafilter->len; mafilter->i++) {
		mafilter->buf[mafilter->i] = 0;
	}
	mafilter->i = 0;
	mafilter->delta = 0;
	mafilter->sum = 0;
	mafilter->out = 0;
	return mafilter;
}

float MAFilter_Calc(MAFilter_t* mafilter, float v)
{
	mafilter->delta = v - mafilter->buf[mafilter->i];
	mafilter->sum += mafilter->delta;
	mafilter->out = mafilter->sum / mafilter->len;
	mafilter->buf[mafilter->i++] = v;
	if(mafilter->i == mafilter->len) {
		mafilter->i = 0;
	}
	return mafilter->out;
}

void MAFilter_Reset(MAFilter_t* mafilter)
{
	for(mafilter->i = 0; mafilter->i < mafilter->len; mafilter->i++) {
		mafilter->buf[mafilter->i] = 0;
	}
	mafilter->i = 0;
	mafilter->sum = 0;
	mafilter->out = 0;
}

void MAFilter_Destroy(MAFilter_t* mafilter)
{
	if (mafilter != NULL) {
		if (mafilter->buf != NULL) {
			free(mafilter->buf);
			mafilter->buf = NULL;
		}
		free(mafilter);
		mafilter = NULL;
	}
}


