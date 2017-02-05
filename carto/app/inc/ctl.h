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
 
#ifndef __CTL_H__
#define __CTL_H__

/**********************************************/
/*              Logic Controller              */
/**********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "app.h"

typedef enum {
	WORKING_STATE_STOP,
	WORKING_STATE_PREPARE,
	WORKING_STATE_NORMAL
}WorkingState_e;

typedef enum {
	WORKING_STATE_SWITCH_NOP, // Working State Switch: No Operation
	WORKING_STATE_SWITCH_S2P, // Working State Switch: Stop -> Prepare
	WORKING_STATE_SWITCH_P2N, // Working State Switch: Prepare -> Normal
	WORKING_STATE_SWITCH_N2P, // Working State Switch: Normal -> Prepare
	WORKING_STATE_SWITCH_P2S, // Working State Switch: Prepare -> Stop
	WORKING_STATE_SWITCH_N2S  // Working State Switch: Normal -> Stop
}WorkingStateSwitch_e;

typedef uint32_t PeriphsState_t; // Peripherals Functional State

#define FS_LED_GREEN      	(((uint32_t)0x00000001)<<0)
#define FS_LED_RED        	(((uint32_t)0x00000001)<<1)
#define FS_GUN      		(((uint32_t)0x00000001)<<2)
#define FS_LASER    		(((uint32_t)0x00000001)<<3)
#define FS_SPINNER  		(((uint32_t)0x00000001)<<4)
#define FS_ALL      		((uint32_t)0xFFFFFFFF)
#define FS_NON       		((uint32_t)0x00000000)

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

void Ctl_Init();
void Ctl_Proc();

/**********************************************/
/*             Exported Variables             */
/**********************************************/
extern WorkingState_e workingState;
extern WorkingStateSwitch_e workingStateSwitch;

extern Mecanum_t mecanum;

extern PID_t CM1SpeedPID;
extern PID_t CM2SpeedPID;
extern PID_t CM3SpeedPID;
extern PID_t CM4SpeedPID;
extern PID_t GMYAnglePID;
extern PID_t GMYSpeedPID;
extern PID_t GMPAnglePID;
extern PID_t GMPSpeedPID;

extern Ramp_t CM1SpeedRamp;
extern Ramp_t CM2SpeedRamp;
extern Ramp_t CM3SpeedRamp;
extern Ramp_t CM4SpeedRamp;
extern Ramp_t GMYSpeedRamp;
extern Ramp_t GMPSpeedRamp;

extern PeriphsState_t functionalStateCtl;
extern PantiltState_t pantiltVelocityCtl;
extern PantiltState_t pantiltCurrentsCtl;
extern MecanumState_t mecanumCurrentsCtl;

#ifdef __cplusplus
}
#endif

#endif

