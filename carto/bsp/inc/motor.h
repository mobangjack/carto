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
#include <string.h>

#define MOTOR_CAN CAN2
#define CM_CMD(c201,c202,c203,c204) EC60_Cmd(MOTOR_CAN,c201,c202,c203,c204)
#define GM_CMD(c205,c206) RM6025_Cmd(MOTOR_CAN,c205,c206)

#define MOTOR1_FDB_CAN_MSG_ID  0x201
#define MOTOR2_FDB_CAN_MSG_ID  0x202
#define MOTOR3_FDB_CAN_MSG_ID  0x203
#define MOTOR4_FDB_CAN_MSG_ID  0x204
#define MOTOR5_FDB_CAN_MSG_ID  0x205
#define MOTOR6_FDB_CAN_MSG_ID  0x206

#define CHASSIS_MOTOR_CMD_CAN_MSG_ID 0x200
#define PANTILT_MOTOR_CMD_CAN_MSG_ID 0x1ff

#define MOTOR_ECD_ANGLE_FDB_MAX   8191
#define MOTOR_ECD_ANGLE_FDB_MOD   (MOTOR_ECD_ANGLE_FDB_MAX + 1)
#define MOTOR_ECD_ANGLE_COEFF (2 * PI / MOTOR_ECD_ANGLE_FDB_MOD)
#define MOTOR_ECD_SPEED_COEFF (MOTOR_ECD_ANGLE_COEFF * 1000)
#define MOTOR_ESC_CURRENT_FDB_MAX 13000
#define MOTOR_ESC_CURRENT_REF_MAX 5000

typedef struct
{
	uint8_t ini_flag;        // initialization flag
	uint16_t angle_fdb[2];   // encoder raw angle feedback, index 1 is the newest
	int32_t speed_fdb;       // encoder speed feedback
	uint16_t bias;           // encoder bias
	int32_t rnd;             // round
	int16_t dif;             // raw angle difference
	float angle_coeff;       // angle_fdb to angle coefficient
	float speed_coeff;       // speed_fdb to speed coefficient
	float angle;             // continuous angle in radian
	float speed;             // speed in rad/ms
}Ecd_t; // For EC60 & RM6025 Encoder

typedef struct
{
	int32_t current_fdb;    // electric current feedback
	int32_t current_ref;    // electric current reference
}Esc_t; // For EC60 & RM6025 Electronic Speed Controller

typedef struct
{
	Ecd_t ecd;
	Esc_t esc;
}Motor_t; // For EC60 & RM6025 Motor

void Ecd_Proc(Ecd_t* ecd, uint8_t* data);
void Ecd_Reset(Ecd_t* ecd);
void Esc_Proc(Esc_t* esc, uint8_t* data);
void Motor_Proc(Motor_t* motor, uint8_t* data);
void EC60_Cmd(CAN_TypeDef *CANx, int16_t c201, int16_t c202, int16_t c203, int16_t c204);
void RM6025_Cmd(CAN_TypeDef *CANx, int16_t c205, int16_t c206);

#endif
