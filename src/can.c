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

float ZGyroAngle = 0;

ESC_t ESC1;
ESC_t ESC2;
ESC_t ESC3;
ESC_t ESC4;
ESC_t ESC5;
ESC_t ESC6;

void CAN_RX_Callback(CanRxMsg* canRxMsg)
{
	switch(canRxMsg->StdId)
	{
		case ZGYRO_FEEDBACK_CAN_MSG_ID:
		{
			Superviser_Feed(LOST_COUNTER_INDEX_ZGYRO);
			ZGyro_GetAngle(&ZGyroAngle, canRxMsg->Data);
		}break;
		case ESC1_FEEDBACK_CAN_MSG_ID:
		{
			Superviser_Feed(LOST_COUNTER_INDEX_MOTOR1);
			ESC_Process(&ESC1, canRxMsg->Data);
		}break;
		case ESC2_FEEDBACK_CAN_MSG_ID:
		{
			Superviser_Feed(LOST_COUNTER_INDEX_MOTOR2);
			ESC_Process(&ESC2, canRxMsg->Data);
		}break;
		case ESC3_FEEDBACK_CAN_MSG_ID:
		{
			Superviser_Feed(LOST_COUNTER_INDEX_MOTOR3);
			ESC_Process(&ESC3, canRxMsg->Data);
		}break;
		case ESC4_FEEDBACK_CAN_MSG_ID:
		{
			Superviser_Feed(LOST_COUNTER_INDEX_MOTOR4);
			ESC_Process(&ESC4, canRxMsg->Data);
		}break;
		case ESC5_FEEDBACK_CAN_MSG_ID:
		{
			Superviser_Feed(LOST_COUNTER_INDEX_MOTOR5);
			ESC_Process(&ESC5, canRxMsg->Data);
		}break;
		case ESC6_FEEDBACK_CAN_MSG_ID:
		{
			Superviser_Feed(LOST_COUNTER_INDEX_MOTOR6);
			ESC_Process(&ESC6, canRxMsg->Data);
		}break;
		default:
		{
		}
	}
}


