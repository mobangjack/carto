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

#include "wdg.h"

const uint32_t WDG[WDG_NUM] = {
		WDG_OVERFLOW_CNT_RC,
		WDG_OVERFLOW_CNT_CALI,
		WDG_OVERFLOW_CNT_API,
		WDG_OVERFLOW_CNT_IMU,
		WDG_OVERFLOW_CNT_ZGYRO,
		WDG_OVERFLOW_CNT_MOTOR,
		WDG_OVERFLOW_CNT_MOTOR,
		WDG_OVERFLOW_CNT_MOTOR,
		WDG_OVERFLOW_CNT_MOTOR,
		WDG_OVERFLOW_CNT_MOTOR,
		WDG_OVERFLOW_CNT_MOTOR,
};

uint32_t wdg[WDG_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t err = 0xFFFFFFFF;

void WDG_SRV(void)
{
	int i = 0;
	for(i = 0; i < WDG_NUM; i++)
	{
		if(wdg[i] >= WDG[i])
		{
			err |= (uint32_t)(1 << i); //set the error bit

		}
		else
		{
			err &= ~(uint32_t)(1 << i); //clear the error bit
			wdg[i]++;			     //add 1 each time
		}
	}
}

void WDG_Feed(uint8_t i)
{
	wdg[i] = 0;
}

uint32_t WDG_GetErr(void)
{
	return err;
}

uint8_t WDG_IsErrSet(uint32_t mask)
{
	return (err & mask) == mask;
}

