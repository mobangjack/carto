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

Motor_t motor[MOTOR_NUM]; // Motor Group
Est_t* est[MOTOR_NUM];    // Estimator Group

#define EST_GAUSS_N   100u
#define EST_KALMAN_Q  0.1f

static void ECD_Proc(uint8_t i, uint8_t* data)
{
	if(est[i] == NULL) {
		est[i] = Est_Create(EST_GAUSS_N, EST_KALMAN_Q);
	}
	Motor_Proc(&motor[i], data);
	Est_Proc(est[i], motor[i].ecd.angle);
	encoder[i].angle = est[i]->value;
	encoder[i].speed = est[i]->delta;
}

void Can_Proc(CanRxMsg* canRxMsg)
{
	uint32_t id = canRxMsg->StdId;
	uint8_t* data = canRxMsg->Data;
	switch (id) {
	case ZGYRO_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_ZGYRO);
		ZGyro_GetAngle(&ZGyroAngle, data);
		break;
	case MOTOR1_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR1);
		ECD_Proc(0, data);
		break;
	case MOTOR2_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR2);
		ECD_Proc(1, data);
		break;
	case MOTOR3_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR3);
		ECD_Proc(2, data);
		break;
	case MOTOR4_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR4);
		ECD_Proc(3, data);
		break;
	case MOTOR5_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR5);
		ECD_Proc(4, data);
		break;
	case MOTOR6_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR6);
		ECD_Proc(5, data);
		break;
	default:
		break;
	}
}

void Encoder_Reset(uint8_t i)
{
	Est_Reset(est[i]);
	Ecd_Reset(&motor[i].ecd);
	memset(&encoder[i], 0, sizeof(Encoder_t));
}
