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
#include "act.h" // Action (Depend on BSP)
#include "can.h" // Controller Area Network
#include "cfg.h" // System Configuration
#include "clk.h" // System Clock Source
#include "cmd.h" // System Command
#include "com.h" // Communication
#include "ctl.h" // Logic Controller
#include "hci.h" // Host Control Input
#include "ins.h" // Inertial Navigation System
#include "odo.h" // Odometer
#include "pwr.h" // Power Management
#include "rci.h" // Remote Control Input
#include "wdg.h" // Watch Dog

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
#define INPUT_MODE_AD      SW_DOWN   // Auto-drive

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

FunctionalState_t FS_Get(const FunctionalState_t* fs, FunctionalState_t msk);
void FS_Set(FunctionalState_t* fs, FunctionalState_t msk);
void FS_Clr(FunctionalState_t* fs, FunctionalState_t msk);
void FS_Tog(FunctionalState_t* fs, FunctionalState_t msk);

extern Cfg_t cfg;

extern IMU_t imu;
extern Mag_t mag;
extern AHRS_t ahrs;
extern uint8_t div;
extern Ramp_t ramp;
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

extern FunctionalState_t functionalStateRef;
extern FunctionalState_t functionalStateFdb;
extern FunctionalState_t functionalStateCmd;

extern PantiltState_t pantiltPositionRef;
extern PantiltState_t pantiltPositionFdb;
extern PantiltState_t pantiltPositionCmd;

extern PantiltState_t pantiltVelocityRef;
extern PantiltState_t pantiltVelocityFdb;
extern PantiltState_t pantiltVelocityCmd;

extern ChassisState_t chassisPositionRef;
extern ChassisState_t chassisPositionFdb;
extern ChassisState_t chassisPositionCmd;

extern ChassisState_t chassisVelocityRef;
extern ChassisState_t chassisVelocityFdb;
extern ChassisState_t chassisVelocityCmd;

extern MecanumState_t mecanumPositionRef;
extern MecanumState_t mecanumPositionFdb;
extern MecanumState_t mecanumPositionCmd;

extern MecanumState_t mecanumVelocityRef;
extern MecanumState_t mecanumVelocityFdb;
extern MecanumState_t mecanumVelocityCmd;

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */
