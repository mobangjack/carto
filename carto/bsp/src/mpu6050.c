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

#include "mpu6050.h"

void MPU6050_Config(void)
{
	while(!MPU6050_Init());
	while(!HMC5883_Init());
	MPU6050_INT_Config();
	MPU6050_INT_Enable();
}

#define PI 3.1415926f
void MPU6050INTCallback()
{
	float buf[8];
	int16_t raw[17];
	MPU6050_Read(raw);
	HMC5883_Read(raw + 14);
	buf[0] = raw[0] * MPU6050_ACC_G_RECIP; // Convert to m/s^2
	buf[1] = raw[1] * MPU6050_ACC_G_RECIP; // Convert to m/s^2
	buf[2] = raw[2] * MPU6050_ACC_G_RECIP; // Convert to m/s^2
	// buf[3] = raw[3] / 340.0f + 36.53f; // Ignore temperature measurement
	buf[3] = raw[4] * MPU6050_GYRO_RAD_RECIP; // Convert to rad/s
	buf[4] = raw[5] * MPU6050_GYRO_RAD_RECIP; // Convert to rad/s
	buf[5] = raw[6] * MPU6050_GYRO_RAD_RECIP; // Convert to rad/s
	buf[6] = raw[7] * MPU6050_MAG_UT_RECIP;
	buf[7] = raw[8] * MPU6050_MAG_UT_RECIP;
	buf[8] = raw[9] * MPU6050_MAG_UT_RECIP;
	MPU6050Callback(buf);
}
