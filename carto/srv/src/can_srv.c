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

void CAN_SRV(CanRxMsg* canRxMsg)
{
	uint32_t id = canRxMsg->StdId;
	uint8_t* data = canRxMsg->Data;
	switch (id) {
	case ZGYRO_FEEDBACK_CAN_MSG_ID:
		Superviser_Feed(LOST_COUNTER_INDEX_ZGYRO);
		ZGyroAngle = -0.01f*((int32_t)(data[0]<<24)|(int32_t)(data[1]<<16) | (int32_t)(data[2]<<8) | (int32_t)(data[3]));
		break;
	case MOTOR1_FEEDBACK_CAN_MSG_ID:
		Superviser_Feed(LOST_COUNTER_INDEX_ZGYRO);
		ZGyro_GetAngle(&ZGyroAngle, canRxMsg->Data);
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
