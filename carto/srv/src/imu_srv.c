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

#include "imu_srv.h"

float buf[9];
int16_t raw[17];
void MPU6050_INT_Callback()
{
	MPU6050_Read(raw);
	HMC5883_Read(raw + 14);

	buf[0] = raw[0] / ACC_SENSITIVITY;
	buf[1] = raw[1] / ACC_SENSITIVITY;
	buf[2] = raw[2] / ACC_SENSITIVITY;
	// buf[3] = raw[3] / 340.0f + 36.53f;
	buf[3] = raw[4] / GYRO_SENSITIVITY;
	buf[4] = raw[5] / GYRO_SENSITIVITY;
	buf[5] = raw[6] / GYRO_SENSITIVITY;
	buf[6] = raw[7] / MAG_SENSITIVITY;
	buf[7] = raw[8] / MAG_SENSITIVITY;
	buf[8] = raw[9] / MAG_SENSITIVITY;

	IMU_Proc(buf);
}

