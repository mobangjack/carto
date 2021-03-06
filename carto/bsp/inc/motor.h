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
 
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "platform.h"

#define MOTOR1_FEEDBACK_CAN_MSG_ID  0x201
#define MOTOR2_FEEDBACK_CAN_MSG_ID  0x202
#define MOTOR3_FEEDBACK_CAN_MSG_ID  0x203
#define MOTOR4_FEEDBACK_CAN_MSG_ID  0x204
#define MOTOR5_FEEDBACK_CAN_MSG_ID  0x205
#define MOTOR6_FEEDBACK_CAN_MSG_ID  0x206

#define CHASSIS_MOTOR_CMD_CAN_MSG_ID 0x200
#define GIMBAL_MOTOR_CMD_CAN_MSG_ID  0x1ff

#define ESC_ANGLE_FDB_MAX 8191
#define ESC_CURRENT_FDB_MAX 13000
#define ESC_CURRENT_REF_MAX 5000

/*
 * EC60 & RM6025 Electronic Speed Controller
 */
typedef struct
{
	uint16_t angle_fdb;    // angle feedback
	uint16_t current_fdb;  // electric current feedback
	uint16_t current_ref;  // electric current reference
}ESC_t;

void ESC_Proc(ESC_t* esc, uint8_t* data);
void EC60_CMD(CAN_TypeDef *CANx, int16_t c201, int16_t c202, int16_t c203, int16_t c204);
void RM6025_CMD(CAN_TypeDef *CANx, int16_t c205, int16_t c206);

#endif
