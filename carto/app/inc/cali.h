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

#ifndef __CALI_H__
#define __CALI_H__

#include "flash.h"

#define CALI_FLASH_DATA_START_ADDRESS 	FLASH_SECTOR_11_ADDR

#define VERSION_A		1u
#define VERSION_B		6u
#define VERSION_C		4u
#define VERSION_D		0u
#define VERSION			(VERSION_A<<24)|(VERSION_B<<16)|(VERSION_C<<8)|(VERSION_D)

typedef uint32_t Version_t;
typedef uint32_t CaliFlag_t;

#define CALI_FLAG_PITCH_MAX 		(((uint32_t)1)<<0)
#define CALI_FLAG_PITCH_MIN 		(((uint32_t)1)<<1)
#define CALI_FLAG_PITCH_OFFSET 		(((uint32_t)1)<<2)
#define CALI_FLAG_YAW_MAX 			(((uint32_t)1)<<3)
#define CALI_FLAG_YAW_MIN 			(((uint32_t)1)<<4)
#define CALI_FLAG_YAW_OFFSET	 	(((uint32_t)1)<<5)
#define CALI_FLAG_PITCH_PID 		(((uint32_t)1)<<6)
#define CALI_FLAG_YAW_PID 			(((uint32_t)1)<<7)
#define CALI_FLAG_CHASSIS_PID 		(((uint32_t)1)<<8)

#define CALI_FLAG_NONE   0x00
#define CALI_FLAG_DONE   0x5A

typedef struct
{
	int16_t max;
	int16_t min;
	int16_t offset;
}PosCali_t;

typedef struct
{
	float kp;
	float ki;
	float kd;
}PIDCali_t;

typedef struct
{
	Version_t version;
	CaliFlag_t caliFlag;
	PosCali_t pitch;
	PosCali_t yaw;
	PIDCali_t pitchPosPID;
	PIDCali_t pitchSpdPID;
	PIDCali_t yawPosPID;
	PIDCali_t yawSpdPID;
}Cali_t;

void Cali_Get(Cali_t* cali);
uint8_t Cali_Set(Cali_t* cali);

#endif

