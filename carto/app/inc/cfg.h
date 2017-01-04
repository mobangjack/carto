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

#define CFG_FLAG_IMU 		        (((uint32_t)1)<<1)
#define CFG_FLAG_MAG 		        (((uint32_t)1)<<2)
#define CFG_FLAG_YAW 			    (((uint32_t)1)<<3)
#define CFG_FLAG_PIT 			    (((uint32_t)1)<<4)
#define CFG_FLAG_CHA 		        (((uint32_t)1)<<11)

#define CFG_FLAG_NO   0x00
#define CFG_FLAG_OK   0x5A

typedef struct
{
	float ax_offset;
	float ay_offset;
	float az_offset;
	float gx_offset;
	float gy_offset;
	float gz_offset;
}ImuCfg_t; // IMU offset Configuration

typedef struct
{
	float mx_offset;
	float my_offset;
	float mz_offset;
}MagCfg_t; // MAG offset Configuration

typedef struct
{
	float max;
	float min;
	float mid;
}PosCfg_t; // Position Configuration

typedef struct
{
	float kp;
	float ki;
	float kd;
	float Pmax;
	float Imax;
	float Dmax;
	float outmax;
}PIDCfg_t; // PID Configuration

typedef struct
{
	PosCfg_t posCfg;
	PIDCfg_t posPID;
	PIDCfg_t spdPID;
}GimCfg_t; // Gimbal Configuration

typedef struct
{
	float x;
	float y;
}DimCfg_t; // Dimension Configuration

typedef struct
{
	DimCfg_t dim;
	PIDCfg_t pid;
}ChaCfg_t; // Chassis Configuration

typedef struct
{
	Version_t version;
	CfgFlag_t flag;
	ImuCfg_t imu;
	MagCfg_t mag;
	GimCfg_t yaw;
	GimCfg_t pit;
	ChaCfg_t cha;
}Cfg_t;

#define CFG_SIZE() sizeof(Cfg_t)

#define IMU_CFG_DEFAULT \
{ \
	.ax_offset = 0, \
	.ay_offset = 0, \
	.az_offset = 0, \
	.gx_offset = 0, \
	.gy_offset = 0, \
	.gz_offset = 0, \
}

#define MAG_CFG_DEFAULT \
{ \
	.mx_offset = 0, \
	.my_offset = 0, \
	.mz_offset = 0, \
}

#define YAW_POS_CFG_DEFAULT \
{ \
	.max = 0, \
	.min = 0, \
	.mid = 0, \
}

#define PIT_POS_CFG_DEFAULT \
{ \
	.max = 0, \
	.min = 0, \
	.mid = 0, \
}

#define YAW_POS_PID_CFG_DEFAULT \
{ \
	.kp = 0, \
	.ki = 0, \
	.kd = 0, \
	.Pmax = 4000, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.outmax = 4900, \
}

#define YAW_SPD_PID_CFG_DEFAULT \
{ \
	.kp = 0, \
	.ki = 0, \
	.kd = 0, \
	.Pmax = 4000, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.outmax = 4900, \
}

#define PIT_POS_PID_CFG_DEFAULT \
{ \
	.kp = 0, \
	.ki = 0, \
	.kd = 0, \
	.Pmax = 4000, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.outmax = 4900, \
}

#define PIT_SPD_PID_CFG_DEFAULT \
{ \
	.kp = 0, \
	.ki = 0, \
	.kd = 0, \
	.Pmax = 4000, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.outmax = 4900, \
}

#define YAW_CFG_DEFAULT \
{ \
	YAW_POS_CFG_DEFAULT, \
	YAW_POS_PID_CFG_DEFAULT, \
	YAW_SPD_PID_CFG_DEFAULT, \
}

#define PIT_CFG_DEFAULT \
{ \
	PIT_POS_CFG_DEFAULT, \
	PIT_POS_PID_CFG_DEFAULT, \
	PIT_SPD_PID_CFG_DEFAULT, \
}

#define CHA_DIM_CFG_DEFAULT \
{ \
	.x = 0, \
	.y = 0, \
}

#define CHA_PID_CFG_DEFAULT \
{ \
	.kp = 0, \
	.ki = 0, \
	.kd = 0, \
	.Pmax = 4000, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.outmax = 4900, \
}

#define CHA_CFG_DEFAULT \
{ \
	CHA_DIM_CFG_DEFAULT, \
	CHA_PID_CFG_DEFAULT, \
}

#define CFG_DEFAULT \
{ \
	VERSION, \
	0, \
	IMU_CFG_DEFAULT, \
	MAG_CFG_DEFAULT, \
	YAW_CFG_DEFAULT, \
	PIT_CFG_DEFAULT, \
	CHA_CFG_DEFAULT, \
}

void Cfg_Read(Cfg_t* cfg);
uint8_t Cfg_Save(Cfg_t* cfg);
uint8_t Cfg_Reset(void);

#endif

