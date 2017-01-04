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

#ifndef __CFG_H__
#define __CFG_H__

#include "flash.h"

#define CFG_DATA_START_ADDRESS 	FLASH_SECTOR_11_ADDR

#define VERSION_A		1u
#define VERSION_B		6u
#define VERSION_C		4u
#define VERSION_D		0u
#define VERSION			(VERSION_A<<24)|(VERSION_B<<16)|(VERSION_C<<8)|(VERSION_D)

typedef uint32_t Version_t;
typedef uint32_t CfgFlag_t;

#define CFG_FLAG_YAW_MAX 			(((uint32_t)1)<<1)
#define CFG_FLAG_YAW_MIN 			(((uint32_t)1)<<2)
#define CFG_FLAG_YAW_MID	 	    (((uint32_t)1)<<3)
#define CFG_FLAG_PIT_MAX 		    (((uint32_t)1)<<4)
#define CFG_FLAG_PIT_MIN 		    (((uint32_t)1)<<5)
#define CFG_FLAG_PIT_MID 		    (((uint32_t)1)<<6)
#define CFG_FLAG_YAW_PID 			(((uint32_t)1)<<7)
#define CFG_FLAG_PIT_PID 		    (((uint32_t)1)<<8)
#define CFG_FLAG_CHASSIS_PID 		(((uint32_t)1)<<9)

#define CFG_FLAG_NO   0x00
#define CFG_FLAG_OK   0x5A

typedef struct
{
	int16_t max;
	int16_t min;
	int16_t mid;
}PosCfg_t;

typedef struct
{
	float kp;
	float ki;
	float kd;
}PIDCfg_t;

typedef struct
{
	Version_t version;
	CfgFlag_t cfgFlag;
	PosCfg_t pitch;
	PosCfg_t yaw;
	PIDCfg_t pitchPosPID;
	PIDCfg_t pitchSpdPID;
	PIDCfg_t yawPosPID;
	PIDCfg_t yawSpdPID;
}Cfg_t;

void Cfg_Get(Cfg_t* cfg);
uint8_t Cfg_Set(Cfg_t* cfg);
uint8_t Cfg_Save(Cfg_t* cfg);

#endif

