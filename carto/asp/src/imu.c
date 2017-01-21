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

#include "imu.h"

void IMU_Config(IMU_t* imu,
		        float ax_offset, float ay_offset, float az_offset,
		        float gx_offset, float gy_offset, float gz_offset)
{
	imu->ax_offset = ax_offset;
	imu->ay_offset = ay_offset;
	imu->az_offset = az_offset;
	imu->gx_offset = gx_offset;
	imu->gy_offset = gy_offset;
	imu->gz_offset = gz_offset;
}

void IMU_Proc(IMU_t* imu, float* buf)
{
	float ax = buf[0];
	float ay = buf[1];
	float az = buf[2];
	float gx = buf[3];
	float gy = buf[4];
	float gz = buf[5];

	imu->ax = ax + imu->ax_offset;
	imu->ay = ay + imu->ay_offset;
	imu->az = az + imu->az_offset;
	imu->gx = gx + imu->gx_offset;
	imu->gy = gy + imu->gy_offset;
	imu->gz = gz + imu->gz_offset;
}
