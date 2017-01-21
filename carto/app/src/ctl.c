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

WorkingState_t workingState = WORKING_STATE_PREPARE;

static void WorkingStateSM()
{
	if (WDG_IsErrSet(WDG_ERR_FATAL)) {
		workingState = WORKING_STATE_STOP;
	} else {
		workingState = WORKING_STATE_NORMAL;
	}
}

static void FunctionalStateControl()
{
	if (!FS_Get(&functionalStateRef, FS_GUN)) {
		FS_Clr(&functionalStateCmd, FS_LASER | FS_SPINNER);
	}
}

static void PantiltPositionControl()
{
	pantiltPositionCmd.y = PID_Calc(&GMYAnglePID, pantiltPositionRef.y, pantiltPositionFdb.y);
	pantiltPositionCmd.p = PID_Calc(&GMPAnglePID, pantiltPositionRef.p, pantiltPositionFdb.p);
}

static void PantiltVelocityControl()
{
	pantiltVelocityCmd.y = PID_Calc(&GMYSpeedPID, pantiltVelocityRef.y, pantiltVelocityFdb.y);
	pantiltVelocityCmd.p = PID_Calc(&GMPSpeedPID, pantiltVelocityRef.p, pantiltVelocityFdb.p);
}

static void ChassisPositionControl()
{
	mecanumPositionCmd.w1 = PID_Calc(&CM1AnglePID, mecanumPositionRef.w1, mecanumPositionFdb.w1);
	mecanumPositionCmd.w2 = PID_Calc(&CM2AnglePID, mecanumPositionRef.w2, mecanumPositionFdb.w2);
	mecanumPositionCmd.w3 = PID_Calc(&CM3AnglePID, mecanumPositionRef.w3, mecanumPositionFdb.w3);
	mecanumPositionCmd.w4 = PID_Calc(&CM4AnglePID, mecanumPositionRef.w4, mecanumPositionFdb.w4);
}

static void ChassisVelocityControl()
{
	mecanumVelocityCmd.w1 = PID_Calc(&CM1SpeedPID, mecanumVelocityRef.w1, mecanumVelocityFdb.w1);
	mecanumVelocityCmd.w2 = PID_Calc(&CM2SpeedPID, mecanumVelocityRef.w2, mecanumVelocityFdb.w2);
	mecanumVelocityCmd.w3 = PID_Calc(&CM3SpeedPID, mecanumVelocityRef.w3, mecanumVelocityFdb.w3);
	mecanumVelocityCmd.w4 = PID_Calc(&CM4SpeedPID, mecanumVelocityRef.w4, mecanumVelocityFdb.w4);
}

static void EmergencyBreak()
{
	FS_Clr(&functionalStateCmd, FS_ALL);
	//CS_Set(0, 0, 0);
	//GS_Set(0, 0);
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

