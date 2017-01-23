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
 
#include "ctl.h"

/**************************************/
/*          Logic Controller          */
/**************************************/

static void WorkingStateSM()
{
	if (Wdg_IsErrSet(WDG_ERR_FATAL)) {
		workingState = WORKING_STATE_STOP;
	} else {
		workingState = WORKING_STATE_NORMAL;
	}
}

static void FunctionalStateControl()
{
	if (FS_Get(&functionalStateRef, FS_GUN)) {
		FS_Set(&functionalStateCtl, FS_GUN | FS_LASER);
	} else {
		FS_Clr(&functionalStateCtl, FS_GUN | FS_LASER | FS_SPINNER);
	}
}

static void PantiltPositionControl()
{
	pantiltPositionCtl.y = PID_Calc(&GMYAnglePID, pantiltPositionRef.y, pantiltPositionFdb.y);
	pantiltPositionCtl.p = PID_Calc(&GMPAnglePID, pantiltPositionRef.p, pantiltPositionFdb.p);
}

static void PantiltVelocityControl()
{
	pantiltVelocityCtl.y = PID_Calc(&GMYSpeedPID, pantiltVelocityRef.y, pantiltVelocityFdb.y);
	pantiltVelocityCtl.p = PID_Calc(&GMPSpeedPID, pantiltVelocityRef.p, pantiltVelocityFdb.p);
}

static void ChassisPositionControl()
{
	mecanumPositionCtl.w1 = PID_Calc(&CM1AnglePID, mecanumPositionRef.w1, mecanumPositionFdb.w1);
	mecanumPositionCtl.w2 = PID_Calc(&CM2AnglePID, mecanumPositionRef.w2, mecanumPositionFdb.w2);
	mecanumPositionCtl.w3 = PID_Calc(&CM3AnglePID, mecanumPositionRef.w3, mecanumPositionFdb.w3);
	mecanumPositionCtl.w4 = PID_Calc(&CM4AnglePID, mecanumPositionRef.w4, mecanumPositionFdb.w4);
}

static void ChassisVelocityControl()
{
	mecanumVelocityCtl.w1 = PID_Calc(&CM1SpeedPID, mecanumVelocityRef.w1, mecanumVelocityFdb.w1);
	mecanumVelocityCtl.w2 = PID_Calc(&CM2SpeedPID, mecanumVelocityRef.w2, mecanumVelocityFdb.w2);
	mecanumVelocityCtl.w3 = PID_Calc(&CM3SpeedPID, mecanumVelocityRef.w3, mecanumVelocityFdb.w3);
	mecanumVelocityCtl.w4 = PID_Calc(&CM4SpeedPID, mecanumVelocityRef.w4, mecanumVelocityFdb.w4);
}

static void EmergencyBreak()
{
	FS_Clr(&functionalStateCtl, FS_ALL);
	//CS_Set(0, 0, 0);
	//GS_Set(0, 0);
}

void Ctl_Init()
{
	FS_Clr(&functionalStateCtl, FS_ALL);
	GS_Set(&pantiltPositionCtl, 0, 0);
	GS_Set(&pantiltVelocityCtl, 0, 0);
	CS_Set(&chassisPositionCtl, 0, 0, 0);
	CS_Set(&chassisVelocityCtl, 0, 0, 0);
	MS_Set(&mecanumPositionCtl, 0, 0, 0, 0);
	MS_Set(&mecanumVelocityCtl, 0, 0, 0, 0);

	PID_Reset(&CM1AnglePID);
	PID_Reset(&CM1SpeedPID);
	PID_Reset(&CM2AnglePID);
	PID_Reset(&CM2SpeedPID);
	PID_Reset(&CM3AnglePID);
	PID_Reset(&CM3SpeedPID);
	PID_Reset(&CM4AnglePID);
	PID_Reset(&CM4SpeedPID);
	PID_Reset(&GMYAnglePID);
	PID_Reset(&GMYSpeedPID);
	PID_Reset(&GMPAnglePID);
	PID_Reset(&GMPSpeedPID);

	Ramp_Reset(&ramp);
}

void Ctl_Proc()
{
	WorkingStateSM();
	if(workingState == WORKING_STATE_PREPARE || workingState == WORKING_STATE_STOP)
	{
		EmergencyBreak();
	}
	else if(workingState == WORKING_STATE_NORMAL)
	{
		FunctionalStateControl();

		ChassisPositionControl();
		ChassisVelocityControl();

		PantiltPositionControl();
		PantiltVelocityControl();
	}
	
}

