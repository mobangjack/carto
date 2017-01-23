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

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C" {
#endif

/**************************************/
/*            Application             */
/**************************************/

// Standard c libraries
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Application Support Packages
#include "asp.h"

// Board Supported Packages
#include "bsp.h"

// Services
#include "srv.h"

// Applications
#include "aci.h" // Auto Control Interface
#include "act.h" // Action (Depend on BSP)
#include "can.h" // Controller Area Network
#include "cfg.h" // System Configuration
#include "clk.h" // System Clock Source
#include "cmd.h" // System Command
#include "com.h" // Communication
#include "ctl.h" // Logic Controller
#include "hci.h" // Host Control Interface
#include "ins.h" // Inertial Navigation System
#include "odo.h" // Odometer
#include "pwr.h" // Power Management
#include "rci.h" // Remote Control Interface
#include "wdg.h" // Watch Dog

// VERSION: (20)17/1/7
#define VERSION_A		1u
#define VERSION_B		7u
#define VERSION_C		1u
#define VERSION_D		7u
#define VERSION			(VERSION_A<<24)|(VERSION_B<<16)|(VERSION_C<<8)|(VERSION_D)

typedef uint32_t Version_t;
typedef uint32_t CfgFlag_t;

#define CFG_FLAG_NO                 0u
#define CFG_FLAG_OK                 (((uint32_t)1)<<0)
#define CFG_FLAG_IMU 		        (((uint32_t)1)<<1)
#define CFG_FLAG_MAG 		        (((uint32_t)1)<<2)
#define CFG_FLAG_YAW 			    (((uint32_t)1)<<3)
#define CFG_FLAG_PIT 			    (((uint32_t)1)<<4)
#define CFG_FLAG_CHA 		        (((uint32_t)1)<<5)
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
	float max;
	float min;
	float mid;
}PosCfg_t; // Position Configuration

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
	PIDCfg_t posPID;
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

#define CHA_MEC_CFG_DEFAULT \
{ \
	.lx = 0.160f, \
	.ly = 0.160f, \
	.r1 = 0.009f, \
	.r2 = 0.070f, \
}

#define CHA_POS_PID_CFG_DEFAULT \
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
	CHA_POS_PID_CFG_DEFAULT, \
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
	CFG_FLAG_NO, \
	IMU_CFG_DEFAULT, \
	MAG_CFG_DEFAULT, \
	YAW_CFG_DEFAULT, \
	PIT_CFG_DEFAULT, \
	CHA_CFG_DEFAULT, \
	CTL_CFG_DEFAULT, \
}

// commonly used macros
#define PI 3.1415926f
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)
#define LIMIT(X,M) ((X)=(X)>(M)?(M):((X)<-(M)?-(M):(X)))
#define SQR(x) ((x)*(x))

#define CHASSIS_SPEED_MAX 4.0f     // 4m/s
#define PANTILT_SPEED_MAX 1.0f     // 1r/s

typedef uint8_t InputMode_t;

#define INPUT_MODE_RC      SW_MID    // Remote Control
#define INPUT_MODE_HC      SW_UP     // Host Control
#define INPUT_MODE_AC      SW_DOWN   // Auto Control
#define INPUT_MODE_NO      0         // No Control Input

typedef uint8_t WorkingState_t;

#define WORKING_STATE_STOP    0x00
#define WORKING_STATE_PREPARE 0x01
#define WORKING_STATE_NORMAL  0x02

typedef uint32_t FunctionalState_t;

#define FS_LED_GREEN      	(((uint32_t)0x00000001)<<0)
#define FS_LED_RED        	(((uint32_t)0x00000002)<<1)
#define FS_GUN      		(((uint32_t)0x00000003)<<2)
#define FS_LASER    		(((uint32_t)0x00000004)<<3)
#define FS_SPINNER  		(((uint32_t)0x00000005)<<4)
#define FS_ALL      		((uint32_t)0xFFFFFFFF)
#define FS_NO       		((uint32_t)0x00000000)

typedef struct
{
	float y;
	float p;
}PantiltState_t;

typedef struct
{
	float x;
	float y;
	float z;
}ChassisState_t;

typedef struct
{
	float w1;
	float w2;
	float w3;
	float w4;
}MecanumState_t;

void App_Init();
void App_Sync();

void GetInputMode(const RC_t* rc);
FunctionalState_t FS_Get(const FunctionalState_t* fs, FunctionalState_t msk);
void FS_Set(FunctionalState_t* fs, FunctionalState_t msk);
void FS_Clr(FunctionalState_t* fs, FunctionalState_t msk);
void FS_Tog(FunctionalState_t* fs, FunctionalState_t msk);
void CS_Set(ChassisState_t* cs, float x, float y, float z);
void GS_Set(PantiltState_t* gs, float y, float p);
void MS_Set(MecanumState_t* ms, float w1, float w2, float w3, float w4);

extern Cfg_t cfg;
extern Imu_t imu;
extern Mag_t mag;
extern Ahrs_t ahrs;
extern Ramp_t ramp;
extern DBUS_t dbus;
extern Mecanum_t mecanum;
extern PID_t GMYAnglePID;
extern PID_t GMYSpeedPID;
extern PID_t GMPAnglePID;
extern PID_t GMPSpeedPID;
extern PID_t CM1AnglePID;
extern PID_t CM1SpeedPID;
extern PID_t CM2AnglePID;
extern PID_t CM2SpeedPID;
extern PID_t CM3AnglePID;
extern PID_t CM3SpeedPID;
extern PID_t CM4AnglePID;
extern PID_t CM4SpeedPID;

extern InputMode_t inputMode;
extern WorkingState_t workingState;

extern FunctionalState_t functionalStateRef;
extern FunctionalState_t functionalStateFdb;
extern FunctionalState_t functionalStateCtl;

extern PantiltState_t pantiltPositionRef;
extern PantiltState_t pantiltPositionFdb;
extern PantiltState_t pantiltPositionCtl;

extern PantiltState_t pantiltVelocityRef;
extern PantiltState_t pantiltVelocityFdb;
extern PantiltState_t pantiltVelocityCtl;

extern ChassisState_t chassisPositionRef;
extern ChassisState_t chassisPositionFdb;
extern ChassisState_t chassisPositionCtl;

extern ChassisState_t chassisVelocityRef;
extern ChassisState_t chassisVelocityFdb;
extern ChassisState_t chassisVelocityCtl;

extern MecanumState_t mecanumPositionRef;
extern MecanumState_t mecanumPositionFdb;
extern MecanumState_t mecanumPositionCtl;

extern MecanumState_t mecanumVelocityRef;
extern MecanumState_t mecanumVelocityFdb;
extern MecanumState_t mecanumVelocityCtl;

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */
