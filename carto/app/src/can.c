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

/*********************************************/
/*          Controller Area Network          */
/*********************************************/

ZGyro_t zgyro;
Motor_t motor[MOTOR_NUM];

#define EST_GAUSS_N   100u
#define EST_KALMAN_Q  0.1f

static Est_t* est[MOTOR_NUM];    // Estimator Group

uint8_t Can_Init()
{
	static uint8_t ini_flag[MOTOR_NUM];
	uint8_t i = 0;
	for (; i < MOTOR_NUM; i++) {
		if(est[i] == NULL) {
			est[i] = EstCreate(EST_GAUSS_N, EST_KALMAN_Q);
			if (est[i] != NULL) {
				ini_flag[i] = 1;
			} else {
				return 0;
			}
		}
	}
	return 1;
}

#define PI 3.1415926f
static void ZGyro_GetAngle(uint8_t* data)
{
	volatile float angle = 0;
	zgyro.angle_fdb = ((int32_t)(data[0]<<24) | (int32_t)(data[1]<<16) | (int32_t)(data[2]<<8) | (int32_t)(data[3]));
	angle = -ZGYRO_ANGLE_RECIP * zgyro.angle_fdb;
	if (zgyro.reset) {
		zgyro.bias = angle;
		zgyro.reset = 0;
	}
	zgyro.rate = (angle - zgyro.angle) * ZGYRO_SPEED_RECIP;
	zgyro.angle = angle - zgyro.bias;
}

#define GAP 7500
#define PIx2 6.2831855f
static void Motor_Proc(uint8_t i, uint8_t* data)
{
	volatile float angle = 0;
	int16_t angle_fdb_dif = 0;

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
		motor[i].rate = angle_fdb_dif - MOTOR_ANGLE_FDB_MOD;
	} else if (angle_fdb_dif < -GAP) {
		motor[i].rnd++;
		motor[i].rate = angle_fdb_dif + MOTOR_ANGLE_FDB_MOD;
	} else {
		motor[i].rate = angle_fdb_dif;
	}
	angle = (angle - motor[i].bias) + motor[i].rnd * PIx2;
	//motor[i].rate = (angle - motor[i].angle) * MOTOR_SPEED_RECIP;
	//motor[i].angle = angle;
	EstProc(est[i], angle);
	motor[i].angle = est[i]->value;
	motor[i].rate = est[i]->delta * MOTOR_SPEED_RECIP;
}

void Can_Proc(uint32_t id, uint8_t* data)
{
	switch (id) {
	case ZGYRO_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_ZGYRO);
		ZGyro_GetAngle(data);
		break;
	case MOTOR1_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR1);
		Motor_Proc(0, data);
		break;
	case MOTOR2_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR2);
		Motor_Proc(1, data);
		break;
	case MOTOR3_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR3);
		Motor_Proc(2, data);
		break;
	case MOTOR4_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR4);
		Motor_Proc(3, data);
		break;
	case MOTOR5_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR5);
		Motor_Proc(4, data);
		break;
	case MOTOR6_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR6);
		Motor_Proc(5, data);
		break;
	default:
		break;
	}
}

void ZGyro_Reset()
{
	zgyro.reset = 1;
}

void Motor_Reset(uint8_t i)
{
	EstReset(est[i]);
	motor[i].reset = 1;
}

void Can_Reset()
{
	ZGyro_Reset();
	Motor_Reset(0);
	Motor_Reset(1);
	Motor_Reset(2);
	Motor_Reset(3);
	Motor_Reset(4);
	Motor_Reset(5);
}
