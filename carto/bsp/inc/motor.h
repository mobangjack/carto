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

#define CM_CMD(c201,c202,c203,c204) EC60_CMD(CAN2,c201,c202,c203,c204)
#define GM_CMD(c205,c206) RM6025_CMD(CAN2,c205,c206)

#define MOTOR1_FDB_CAN_MSG_ID  0x201
#define MOTOR2_FDB_CAN_MSG_ID  0x202
#define MOTOR3_FDB_CAN_MSG_ID  0x203
#define MOTOR4_FDB_CAN_MSG_ID  0x204
#define MOTOR5_FDB_CAN_MSG_ID  0x205
#define MOTOR6_FDB_CAN_MSG_ID  0x206

#define CHASSIS_MOTOR_CMD_CAN_MSG_ID 0x200
#define PANTILT_MOTOR_CMD_CAN_MSG_ID 0x1ff

#define MOTOR_ANGLE_FDB_MAX   8191
#define MOTOR_CURRENT_FDB_MAX 13000
#define MOTOR_CURRENT_REF_MAX 5000

typedef struct
{
	uint16_t raw; // raw value
	int32_t rnd;  // round
	int32_t con;  // continuous value
	int32_t exp;  // expected value
	float deg;    // expected value in degree
	float rad;    // expected value in radian
	int32_t dif;  // difference
	float vel;    // velocity
}ECD_t;

typedef struct
{
	int angle_fdb;    // angle feedback
	int current_fdb;  // electric current feedback
	int current_ref;  // electric current reference
}Motor_t; // For EC60 & RM6025 Electronic Speed Controller

void Motor_Proc(Motor_t* motor, uint8_t* data);
void EC60_CMD(CAN_TypeDef *CANx, int16_t c201, int16_t c202, int16_t c203, int16_t c204);
void RM6025_CMD(CAN_TypeDef *CANx, int16_t c205, int16_t c206);

#endif
