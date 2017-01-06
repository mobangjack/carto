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

#include "can.h"

ZGyro_t ZGyro;
Motor_t motor[MOTOR_NUM];

#define EST_GAUSS_N   100u
#define EST_KALMAN_Q  0.1f

//static Est_t* est[MOTOR_NUM];    // Estimator Group

uint8_t Can_Init()
{
	/*
	static uint8_t ini_flag = 0;
	if (ini_flag == 1) {
		return 1;
	} else {
		uint8_t i = 0;
		for (; i < MOTOR_NUM; i++) {
			if(est[i] == NULL) {
				est[i] = Est_Create(EST_GAUSS_N, EST_KALMAN_Q);
				if (est[i] == NULL) {
					uint8_t j = 0;
					for (; j < i; j++) {
						Est_Destroy(est[i]);
					}
					return 0;
				}
			}
		}
		ini_flag = 1;
		return 1;
	}
	*/
	return 1;
}

#define CHECK_OVERFLOW(dt) do { if (dt < 0) dt += 0xFFFFFFFF; } while(0)
#define PI 3.1415926f
static void ZGyro_GetAngle(uint8_t* data)
{
	volatile float angle = 0;
	uint32_t us = Clk_GetUsTick();
	int32_t dt = us - ZGyro.timestamp;
	CHECK_OVERFLOW(dt);
	ZGyro.timestamp = us;
	ZGyro.period = dt;
	ZGyro.angle_fdb = ((int32_t)(data[0]<<24) | (int32_t)(data[1]<<16) | (int32_t)(data[2]<<8) | (int32_t)(data[3]));
	angle = -PI/180*0.01f*ZGyro.angle_fdb;
	if (ZGyro.reset) {
		ZGyro.bias = angle;
	}
	ZGyro.rate = (angle - ZGyro.angle) * 1e6 / dt;
	ZGyro.angle = angle - ZGyro.bias;
}

#define GAP 7500
static void Motor_Proc(uint8_t i, uint8_t* data)
{
	volatile float angle = 0;
	int16_t angle_fdb_dif = 0;

	uint32_t us = Clk_GetUsTick();
	int32_t dt = us - motor[i].timestamp;
	CHECK_OVERFLOW(dt);

	motor[i].timestamp = us;
	motor[i].period = dt;

	motor[i].angle_fdb[0] = motor[i].angle_fdb[1];
	motor[i].angle_fdb[1] = (data[0] << 8) | data[1];
	motor[i].current_fdb = (data[2] << 8) | data[3];
	motor[i].current_ref = (data[4] << 8) | data[5];

	angle = motor[i].angle_fdb[1] * MOTOR_ANGLE_RECIP;

	if (motor[i].reset) {
		motor[i].bias = angle;
		motor[i].rnd = 0;
		motor[i].reset = 0;
	}

	angle_fdb_dif = motor[i].angle_fdb[1] - motor[i].angle_fdb[0];

	if (angle_fdb_dif > GAP) {
		motor[i].rnd--;
		motor[i].rate = angle_fdb_dif - MOTOR_ECD_ANGLE_FDB_MOD;
	} else if (angle_fdb_dif < -GAP) {
		motor[i].rnd++;
		motor[i].rate = angle_fdb_dif + MOTOR_ECD_ANGLE_FDB_MOD;
	} else {
		motor[i].rate = angle_fdb_dif;
	}
	angle = (angle - motor[i].bias) + motor[i].rnd * 2 * PI;
	motor[i].rate = (angle - motor[i].angle) * 1e6 / dt;
	motor[i].angle = angle;
}

void Can_Proc(uint32_t id, uint8_t* data)
{
	switch (id) {
	case ZGYRO_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_ZGYRO);
		ZGyro_GetAngle(data);
		break;
	case MOTOR1_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR1);
		Motor_Proc(0, data);
		break;
	case MOTOR2_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR2);
		Motor_Proc(1, data);
		break;
	case MOTOR3_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR3);
		Motor_Proc(2, data);
		break;
	case MOTOR4_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR4);
		Motor_Proc(3, data);
		break;
	case MOTOR5_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR5);
		Motor_Proc(4, data);
		break;
	case MOTOR6_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR6);
		Motor_Proc(5, data);
		break;
	default:
		break;
	}
}

void ZGyro_Reset()
{
	ZGyro.reset = 1;
}

void Motor_Reset(uint8_t i)
{
	//Est_Reset(est[i]);
	motor[i].reset = 1;
}

