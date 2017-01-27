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

void StaInit(Sta_t* sta, float* buf, uint32_t len)
{
	sta->buf = buf;
	sta->len = len;
	StaReset(sta);
}

void StaUpdate(Sta_t* sta, float v)
{
	float avg = sta->avg;
	float del = v - sta->buf[sta->i];
	sta->avg += del / sta->len;
	sta->var += del * (sta->buf[sta->i] - avg + v - sta->avg) / sta->len;
	sta->buf[sta->i] = v;
	sta->i = (sta->i == sta->len) ? 0 : sta->i + 1;
}

void StaReset(Sta_t* sta)
{
	memset(sta->buf, 0, sta->len * sizeof(float));
	sta->i = 0;
	sta->avg = 0;
	sta->var = 0;
}

Sta_t* StaCreate(uint32_t n)
{
	Sta_t* sta = (Sta_t*)malloc(sizeof(Sta_t));
	if (sta == NULL) {
		return NULL;
	}
	sta->buf = (float*)malloc(n * sizeof(float));
	if (sta->buf == NULL) {
		free(sta);
		sta = NULL;
		return NULL;
	}
	sta->len = n;
	StaReset(sta);
	return sta;
}

void StaDestroy(Sta_t* sta)
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
