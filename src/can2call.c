/**
 * Copyright (c) 2011-2016, Jack Mo (mobangjack@foxmail.com).
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
 
#include "main.h"

Encoder_t CM1Encoder = {0};
Encoder_t CM2Encoder = {0};
Encoder_t CM3Encoder = {0};
Encoder_t CM4Encoder = {0};
Encoder_t GMYEncoder = {0};
Encoder_t GMPEncoder = {0};

void Can2Call(CanRxMsg* canRxMsg)
{   
	uint16_t value = (canRxMsg->Data[0]<<8) | canRxMsg->Data[1];
	switch(canRxMsg->StdId)
	{
		case MOTOR1_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&CM1Encoder, value);
		}break;
		case MOTOR2_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&CM2Encoder, value);
		}break;
		case MOTOR3_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&CM3Encoder, value); 
		}break;
		case MOTOR4_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&CM4Encoder, value);
		}break;
		case MOTOR5_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&GMYEncoder, value);
		}break;
		case MOTOR6_FEEDBACK_CAN_MSG_ID:
		{
			Encoder_Process(&GMPEncoder, value);
		}break;				
		default:
		{
		}
	}
}
