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

#ifndef __AHRS_H__
#define __AHRS_H__

#include <math.h>

typedef struct
{
	float ax;
	float ay;
	float az;
	float gx;
	float gy;
	float gz;
	float mx;
	float my;
	float mz;
	float ax_offset;
	float ay_offset;
	float az_offset;
	float gx_offset;
	float gy_offset;
	float gz_offset;
	float mx_offset;
	float my_offset;
	float mz_offset;
	float q[4];
	float kp;
	float ki;
	float dt;
	float exInt;
	float eyInt;
	float ezInt;
	float yaw;
	float pitch;
	float roll;
}AHRS_t;

void AHRS_Config(AHRS_t* ahrs);
void AHRS_Update(AHRS_t* ahrs, float* buf, float halfT);
void AHRS_Q2YPR(float* q, float* ypr);

#endif

