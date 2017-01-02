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

#include <stdint.h>

#include "pid.h"

typedef unsigned char WorkingState_t;

#define WORKING_STATE_PREPARE 0x00
#define WORKING_STATE_NORMAL  0x01
#define WORKING_STATE_STOP    0x02

typedef struct
{
	float m1;
	float m2;
	float m3;
	float m4;
}ChassisCurrent_t;

typedef struct
{
	float y;
	float p;
}GimbalsCurrent_t;

#define CM_POSITION_PID_DEFAULT \
{\
	.ref = 0,\
	.fdb = 0,\
	.err = {0,0},\
	.kp = 220.f,\
	.ki = 0.0f,\
	.kd = 0.0f,\
	.P = 0,\
	.I = 0,\
	.D = 0,\
	.Pmax = 4900,\
	.Imax = 3500,\
	.Dmax = 1500,\
	.out = 0,\
	.outmax = 4950,\
	.kp_offset = 0,\
	.ki_offset = 0,\
	.kd_offset = 0,\
}\

#define CM_SPEED_PID_DEFAULT \
{\
	.ref = 0,\
	.fdb = 0,\
	.err = {0,0},\
	.kp = 220.f,\
	.ki = 0.0f,\
	.kd = 0.0f,\
	.P = 0,\
	.I = 0,\
	.D = 0,\
	.Pmax = 4900,\
	.Imax = 3500,\
	.Dmax = 1500,\
	.out = 0,\
	.outmax = 4950,\
	.kp_offset = 0,\
	.ki_offset = 0,\
	.kd_offset = 0,\
}\

#define GM_SPEED_PID_DEFAULT \
{\
	.ref = 0,\
	.fdb = 0,\
	.err = {0,0},\
	.kp = 220.f,\
	.ki = 0.0f,\
	.kd = 0.0f,\
	.P = 0,\
	.I = 0,\
	.D = 0,\
	.Pmax = 4900,\
	.Imax = 3500,\
	.Dmax = 1500,\
	.out = 0,\
	.outmax = 4950,\
	.kp_offset = 0,\
	.ki_offset = 0,\
	.kd_offset = 0,\
}\

#define CM_SPEED_RAMP_DEFAULT \
{\
	.count = 0,\
	.scale = 5000,\
	.Init = Ramp_Init,\
	.Calc = Ramp_Calc,\
	.SetCounter = Ramp_SetCounetr,\
	.ResetCounter = Ramp_ResetCounter,\
	.SetScale = Ramp_SetScale,\
	.IsOverflow = Ramp_IsOverflow,\
}\

#define GM_SPEED_RAMP_DEFAULT \
{\
	.count = 0,\
	.scale = 5000,\
	.Init = Ramp_Init,\
	.Calc = Ramp_Calc,\
	.SetCounter = Ramp_SetCounetr,\
	.ResetCounter = Ramp_ResetCounter,\
	.SetScale = Ramp_SetScale,\
	.IsOverflow = Ramp_IsOverflow,\
}\

//void Control(void);

extern WorkingState_t workingState;
extern ChassisCurrent_t chassisCurrent;
extern GimbalsCurrent_t gimbalsCurrent;

#endif

