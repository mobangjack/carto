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

#include "can_srv.h"

static void CAN_SRV(CanRxMsg* canRxMsg)
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
		ECD_PROC(0, data);
		break;
	case MOTOR2_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR2);
		ECD_PROC(1, data);
		break;
	case MOTOR3_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR3);
		ECD_PROC(2, data);
		break;
	case MOTOR4_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR4);
		ECD_PROC(3, data);
		break;
	case MOTOR5_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR5);
		ECD_PROC(4, data);
		break;
	case MOTOR6_FDB_CAN_MSG_ID:
		WDG_Feed(WDG_IDX_MOTOR6);
		ECD_PROC(5, data);
		break;
	default:
		break;
	}
}

void CAN1_RX_Callback(CanRxMsg* canRxMsg)
{
	CAN_SRV(canRxMsg);
}

void CAN2_RX_Callback(CanRxMsg* canRxMsg)
{
	CAN_SRV(canRxMsg);
}
