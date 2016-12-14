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
 
#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stdint.h>

#define ENCODER_VALUE_MAX 8191
#define ENCODER_VALUE_MOD 8192
#define ENCODER_VALUE_DIFF_MAX 7500
#define ENCODER_RATE_BUF_SIZE 10
#define ENCODER_INIT_FRAME_CNT 50
#define ENCODER_DIFF_MAX 5.7524281f

#define ENCODER_VALUE_TO_RAD(value) ((value)*PI2/ENCODER_VALUE_MOD)

typedef struct
{
	uint16_t value;
	uint16_t init_frame_cnt;
	float angle;
	float last_angle;
	float bias;
	int32_t round;
	float rate_buf[ENCODER_RATE_BUF_SIZE];
	uint8_t rate_cnt;
	uint8_t rate_ptr;
	int32_t rate_sum;
	float rate;
}Encoder_t;

void Encoder_Process(Encoder_t* encoder, uint16_t value);
uint8_t Encoder_IsOk(Encoder_t* encoder);
void Encoder_Reset(Encoder_t* encoder);

#endif
