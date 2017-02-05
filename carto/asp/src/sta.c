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

#include "sta.h"

void Sta_Init(Sta_t* sta, float* buf, uint32_t len)
{
	sta->buf = buf;
	sta->len = len;
	Sta_Reset(sta);
}

void Sta_Calc(Sta_t* sta, float v)
{
	float avg = sta->avg;
	float del = v - sta->buf[sta->i];
	sta->avgd = del / sta->len;
	sta->avg += sta->avgd;
	sta->vard = del * (sta->buf[sta->i] - avg + v - sta->avg) / sta->len;
	sta->var += sta->vard;
	sta->buf[sta->i] = v;
	sta->i = (sta->i == sta->len) ? 0 : sta->i + 1;
}

void Sta_Reset(Sta_t* sta)
{
	memset(sta->buf, 0, sta->len * sizeof(float));
	sta->i = 0;
	sta->avg = 0;
	sta->var = 0;
	sta->avgd = 0;
	sta->vard = 0;
}

Sta_t* Sta_Create(uint32_t len)
{
	Sta_t* sta = (Sta_t*)malloc(sizeof(Sta_t));
	if (sta == NULL) {
		return NULL;
	}
	memset(sta, 0, sizeof(Sta_t));
	sta->buf = (float*)malloc(len * sizeof(float));
	if (sta->buf == NULL) {
		free(sta);
		sta = NULL;
		return NULL;
	}
	Sta_Reset(sta);
	return sta;
}

void Sta_Destroy(Sta_t* sta)
{
	if (sta != NULL) {
		if (sta->buf != NULL) {
			free(sta->buf);
			sta->buf = NULL;
		}
		free(sta);
		sta = NULL;
	}
}
