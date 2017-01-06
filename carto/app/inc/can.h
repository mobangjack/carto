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

#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "clk.h"
#include "est.h"
#include "wdg.h"

#define MOTOR_NUM 6

#define ZGYRO_FDB_CAN_MSG_ID   0x401
#define MOTOR1_FDB_CAN_MSG_ID  0x201
#define MOTOR2_FDB_CAN_MSG_ID  0x202
#define MOTOR3_FDB_CAN_MSG_ID  0x203
#define MOTOR4_FDB_CAN_MSG_ID  0x204
#define MOTOR5_FDB_CAN_MSG_ID  0x205
#define MOTOR6_FDB_CAN_MSG_ID  0x206

#define MOTOR_ECD_ANGLE_FDB_MAX   8191
#define MOTOR_ECD_ANGLE_FDB_MOD   (MOTOR_ECD_ANGLE_FDB_MAX + 1)
#define MOTOR_ANGLE_RECIP (2 * PI / MOTOR_ECD_ANGLE_FDB_MOD)
#define MOTOR_SPEED_RECIP (MOTOR_ANGLE_RECIP * 1000) // Deprecated
#define MOTOR_ESC_CURRENT_FDB_MAX 13000
#define MOTOR_ESC_CURRENT_REF_MAX 5000

typedef struct
{
	/* ZGyro original data feedback */
	int32_t angle_fdb;    // ZGyro raw angle feedback
	/* ZGyro original data feedback */

	uint32_t timestamp;   // Timestamp in us
	int32_t period;       // Period in us
	uint8_t reset;        // ZGyro reset control flag
	float bias;           // ZGyro bias in radian
	float angle;          // ZGyro angle in radian
	float rate;           // ZGyro angle rate in rad/s
}ZGyro_t;

typedef struct
{
	/* Motor original data feedback */
	uint16_t angle_fdb[2];  // Motor encoder raw angle feedback, index 1 is the newest
	int32_t current_fdb;    // Motor electronic speed controller current feedback
	int32_t current_ref;    // Motor electronic speed controller current reference
	/* Motor original data feedback */

	uint32_t timestamp;   // Timestamp in us
	int32_t period;       // Period in us
	uint8_t reset;        // Motor encoder reset control flag
	int32_t rnd;          // Motor spinning rounds
	float bias;           // Motor encoder bias
	float angle;          // Motor encoder angle (continuous) in radian
	float rate;           // Motor encoder angle rate in rad/s
}Motor_t; // For EC60 & RM6025 Motor Encoder & ESC

uint8_t Can_Init();
void Can_Proc(uint32_t id, uint8_t* data);
void ZGyro_Reset();
void Motor_Reset(uint8_t i);

extern ZGyro_t ZGyro;
extern Motor_t motor[MOTOR_NUM]; // Motor group

#ifdef __cplusplus
}
#endif

#endif
