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

#include "app.h"

/**************************************/
/*            Application             */
/**************************************/

Cfg_t cfg;
Imu_t imu;
Mag_t mag;
Ahrs_t ahrs;
Ramp_t ramp;
DBUS_t dbus;
Mecanum_t mecanum;
PID_t GMYAnglePID;
PID_t GMYSpeedPID;
PID_t GMPAnglePID;
PID_t GMPSpeedPID;
PID_t CM1AnglePID;
PID_t CM1SpeedPID;
PID_t CM2AnglePID;
PID_t CM2SpeedPID;
PID_t CM3AnglePID;
PID_t CM3SpeedPID;
PID_t CM4AnglePID;
PID_t CM4SpeedPID;

InputMode_t inputMode;
WorkingState_t workingState;

FunctionalState_t functionalStateRef;
FunctionalState_t functionalStateFdb;
FunctionalState_t functionalStateCtl;

PantiltState_t pantiltPositionRef;
PantiltState_t pantiltPositionFdb;
PantiltState_t pantiltPositionCtl;

PantiltState_t pantiltVelocityRef;
PantiltState_t pantiltVelocityFdb;
PantiltState_t pantiltVelocityCtl;

ChassisState_t chassisPositionRef;
ChassisState_t chassisPositionFdb;
ChassisState_t chassisPositionCtl;

ChassisState_t chassisVelocityRef;
ChassisState_t chassisVelocityFdb;
ChassisState_t chassisVelocityCtl;

MecanumState_t mecanumPositionRef;
MecanumState_t mecanumPositionFdb;
MecanumState_t mecanumPositionCtl;

MecanumState_t mecanumVelocityRef;
MecanumState_t mecanumVelocityFdb;
MecanumState_t mecanumVelocityCtl;

void App_Init()
{
	Bsp_Config();

	Aci_Init();
	Act_Init();
	Can_Init();
	Cfg_Init();
	Clk_Init();
	Cmd_Init();
	Com_Init();
	Ctl_Init();
	Ins_Init();
	Odo_Init();
	Pwr_Init();
	Wdg_Init();
}

void App_Sync()
{
	if (Clk_GetUsTick() % cfg.ctl.div == 0) {
		Wdg_Proc();
		Cmd_Proc();
		Com_Proc();
		Ins_Proc();
		Odo_Proc();
		Ctl_Proc();
		Act_Proc();
		Pwr_Proc();
	}
}

void GetInputMode(const RC_t* rc)
{
	inputMode = rc->sw[SW_IDX_R];
}

FunctionalState_t FS_Get(const FunctionalState_t* fs, FunctionalState_t msk)
{
	return (*fs) & msk;
}

void FS_Set(FunctionalState_t* fs, FunctionalState_t msk)
{
	(*fs) |= msk;
}

void FS_Clr(FunctionalState_t* fs, FunctionalState_t msk)
{
	(*fs) &= ~msk;
}

void FS_Tog(FunctionalState_t* fs, FunctionalState_t msk)
{
	FS_Get(fs, msk) ? FS_Clr(fs, msk) : FS_Set(fs, msk);
}

void CS_Set(ChassisState_t* cs, float x, float y, float z)
{
	cs->x = x;
	cs->y = y;
	cs->z = z;
}

void GS_Set(PantiltState_t* gs, float y, float p)
{
	gs->y = y;
	gs->p = p;
}

void MS_Set(MecanumState_t* ms, float w1, float w2, float w3, float w4)
{
	ms->w1 = w1;
	ms->w2 = w2;
	ms->w3 = w3;
	ms->w4 = w4;
}

