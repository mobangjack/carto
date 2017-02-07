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

/*************************************/
/*     Application Configuration     */
/*************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "fos.h"

// VERSION: (20)17/1/7
#define VERSION_A		1u
#define VERSION_B		7u
#define VERSION_C		1u
#define VERSION_D		7u
#define VERSION			(VERSION_A<<24)|(VERSION_B<<16)|(VERSION_C<<8)|(VERSION_D)

typedef uint32_t Version_t;
typedef uint32_t CfgFlag_t;

#define CFG_FLAG_NONE               0u
#define CFG_FLAG_DONE               (((uint32_t)1)<<0)
#define CFG_FLAG_IMU                (((uint32_t)1)<<1)
#define CFG_FLAG_MAG                (((uint32_t)1)<<2)
#define CFG_FLAG_YAW                (((uint32_t)1)<<3)
#define CFG_FLAG_PIT                (((uint32_t)1)<<4)
#define CFG_FLAG_CHA                (((uint32_t)1)<<5)
#define CFG_FLAG_ALL   (CFG_FLAG_IMU | CFG_FLAG_MAG | CFG_FLAG_YAW | \
                        CFG_FLAG_PIT | CFG_FLAG_CHA)

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
	float kp;
	float ki;
}AhrCfg_t; // Attitude Heading Reference System Configuration

typedef struct
{
	float max;
	float min;
	float ofs;
}PosCfg_t; // Position Configuration

typedef struct
{
	float max;
}SpdCfg_t; // Velocity Configuration

typedef struct
{
	float kp;
	float ki;
	float kd;
	float it;
	float Pmax;
	float Imax;
	float Dmax;
	float Omax;
}PIDCfg_t; // PID Configuration

typedef struct
{
	PosCfg_t posCfg;
	SpdCfg_t spdCfg;
	PIDCfg_t posPID;
	PIDCfg_t spdPID;
}GimCfg_t; // Gimbal Configuration

typedef struct
{
	float lx;
	float ly;
	float r1;
	float r2;
}MecCfg_t; // Mecanum Wheel Configuration

typedef struct
{
	MecCfg_t mecCfg;
	SpdCfg_t spdCfg;
	PIDCfg_t spdPID;
}ChaCfg_t; // Chassis Configuration

typedef struct
{
	uint32_t div; // Clock Division
	uint32_t rmp; // Action Ramp
}CtlCfg_t; // Logic Controller Configuration

typedef struct
{
	Version_t version;
	CfgFlag_t flag;
	ImuCfg_t imu;
	MagCfg_t mag;
	AhrCfg_t ahr;
	GimCfg_t yaw;
	GimCfg_t pit;
	ChaCfg_t cha;
	CtlCfg_t ctl;
}Cfg_t; // Application Configuration

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

#define ARH_CFG_DEFAULT \
{ \
	.kp = 2.0f, \
	.ki = 0.02f, \
}

#define YAW_POS_CFG_DEFAULT \
{ \
	.max = 0, \
	.min = 0, \
	.ofs = 0, \
}

#define YAW_SPD_CFG_DEFAULT \
{ \
	.max = 1.0f, \
}

#define YAW_POS_PID_CFG_DEFAULT \
{ \
	.kp = 220, \
	.ki = 0, \
	.kd = 0, \
	.it = 0, \
	.Pmax = 4950, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.Omax = 4950, \
}

#define YAW_SPD_PID_CFG_DEFAULT \
{ \
	.kp = 220, \
	.ki = 0, \
	.kd = 0, \
	.it = 0, \
	.Pmax = 4950, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.Omax = 4950, \
}

#define YAW_CFG_DEFAULT \
{ \
	YAW_POS_CFG_DEFAULT, \
	YAW_SPD_CFG_DEFAULT, \
	YAW_POS_PID_CFG_DEFAULT, \
	YAW_SPD_PID_CFG_DEFAULT, \
}

#define PIT_POS_CFG_DEFAULT \
{ \
	.max = 0, \
	.min = 0, \
	.ofs = 0, \
}

#define PIT_SPD_CFG_DEFAULT \
{ \
	.max = 1.0f, \
}

#define PIT_POS_PID_CFG_DEFAULT \
{ \
	.kp = 220, \
	.ki = 0, \
	.kd = 0, \
	.it = 0, \
	.Pmax = 4950, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.Omax = 4950, \
}

#define PIT_SPD_PID_CFG_DEFAULT \
{ \
	.kp = 220, \
	.ki = 0, \
	.kd = 0, \
	.it = 0, \
	.Pmax = 4950, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.Omax = 4950, \
}

#define PIT_CFG_DEFAULT \
{ \
	PIT_POS_CFG_DEFAULT, \
	PIT_SPD_CFG_DEFAULT, \
	PIT_POS_PID_CFG_DEFAULT, \
	PIT_SPD_PID_CFG_DEFAULT, \
}

#define CHA_MEC_CFG_DEFAULT \
{ \
	.lx = 0.160f, \
	.ly = 0.160f, \
	.r1 = 0.009f, \
	.r2 = 0.070f, \
}

#define CHA_SPD_CFG_DEFAULT \
{ \
	.max = 4.0f, \
}

#define CHA_SPD_PID_CFG_DEFAULT \
{ \
	.kp = 220, \
	.ki = 0, \
	.kd = 0, \
	.it = 0, \
	.Pmax = 4950, \
	.Imax = 2000, \
	.Dmax = 2000, \
	.Omax = 4950, \
}

#define CHA_CFG_DEFAULT \
{ \
	CHA_MEC_CFG_DEFAULT, \
	CHA_SPD_CFG_DEFAULT, \
	CHA_SPD_PID_CFG_DEFAULT, \
}

#define CTL_DIV_DEFAULT 4
#define CTL_RMP_DEFAULT 5000

#define CTL_CFG_DEFAULT \
{ \
	.div = CTL_DIV_DEFAULT, \
	.rmp = CTL_RMP_DEFAULT, \
}

#define CFG_DEFAULT \
{ \
	VERSION, \
	CFG_FLAG_NONE, \
	IMU_CFG_DEFAULT, \
	MAG_CFG_DEFAULT, \
	ARH_CFG_DEFAULT, \
	YAW_CFG_DEFAULT, \
	PIT_CFG_DEFAULT, \
	CHA_CFG_DEFAULT, \
	CTL_CFG_DEFAULT, \
}

void Cfg_Load(Cfg_t* cfg);
uint8_t Cfg_Save(Cfg_t* cfg);

void Cfg_Init();
void Cfg_Proc();

extern Cfg_t cfg;

#ifdef __cplusplus
}
#endif

#endif

