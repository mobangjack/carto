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

const uint32_t LOST_COUNTER[LOST_COUNTER_NUM] = {
		LOST_COUNTER_NUM_RC,
		LOST_COUNTER_NUM_CALI,
		LOST_COUNTER_NUM_API,
		LOST_COUNTER_NUM_IMU,
		LOST_COUNTER_NUM_ZGYRO,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
};

uint32_t lost_counter[LOST_COUNTER_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t err_code = 0xFFFFFFFF;

void Supervise(void)
{
	int i = 0;
	for(i = 0; i < LOST_COUNTER_NUM; i++)
	{
		if(lost_counter[i] >= LOST_COUNTER[i])
		{
			err_code |= (uint32_t)(1 << i); //set the error bit

		}
		else
		{
			err_code &= ~(uint32_t)(1 << i); //clear the error bit
			lost_counter[i]++;			     //add 1 each time
		}
	}
}

void Superviser_Feed(uint8_t i)
{
	lost_counter[i] = 0;
}

uint32_t Superviser_GetErrorCode(void)
{
	return err_code;
}

uint8_t Superviser_IsErrorSet(uint32_t mask)
{
	return (err_code & mask) == mask;
}

