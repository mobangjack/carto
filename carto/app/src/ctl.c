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

WorkingState_t workingState = WORKING_STATE_PREPARE;

PID_t pid[2][6];

static void WorkingStateSM(void)
{
	if(inputMode == INPUT_MODE_NO)
	{
		workingState = WORKING_STATE_STOP;
		return;
	}
	switch(workingState)
	{
		case WORKING_STATE_PREPARE:
		{
			if(10)
			{
				workingState = WORKING_STATE_NORMAL;
			}
		}break;
		case WORKING_STATE_NORMAL:
		{
			if(0)
			{
				workingState = WORKING_STATE_PREPARE;
			}
		}break;
		case WORKING_STATE_STOP:
		{
			if(inputMode != INPUT_MODE_NO)
			{
				workingState = WORKING_STATE_PREPARE;
			}
		}break;
		default:
		{
			workingState = WORKING_STATE_STOP;
		}break;
	}
}

#define LIMIT(X,M) (X=X>M?M:(X<-M>?-M:X))
static void ChassisPositionControl(void)
{
	mecanum.x = chassisSpeedRef.x;
	mecanum.y = chassisSpeedRef.y;
	mecanum.z = chassisSpeedRef.z;

	Mecanum_Decompose(&mecanum);

	CM1AnglePID.ref = mecanum.w1;
	CM2AnglePID.ref = mecanum.w2;
	CM3AnglePID.ref = mecanum.w3;
	CM4AnglePID.ref = mecanum.w4;

	CM1AnglePID.fdb = motor[0].angle;
	CM2AnglePID.fdb = motor[1].angle;
	CM3AnglePID.fdb = motor[2].angle;
	CM4AnglePID.fdb = motor[3].angle;

	PID_Calc(&CM1AnglePID);
	PID_Calc(&CM2AnglePID);
	PID_Calc(&CM3AnglePID);
	PID_Calc(&CM4AnglePID);
}

static void ChassisVelocityControl(void)
{
	CM1SpeedPID.ref = CM1AnglePID.out;
	CM2SpeedPID.ref = CM2AnglePID.out;
	CM3SpeedPID.ref = CM3AnglePID.out;
	CM4SpeedPID.ref = CM4AnglePID.out;
	
	CM1SpeedPID.fdb = motor[0].rate;
	CM2SpeedPID.fdb = motor[1].rate;
	CM3SpeedPID.fdb = motor[2].rate;
	CM4SpeedPID.fdb = motor[3].rate;
	
	PID_Calc(&CM1SpeedPID);
	PID_Calc(&CM2SpeedPID);
	PID_Calc(&CM3SpeedPID);
	PID_Calc(&CM4SpeedPID);
}

static void PantiltPositionControl(void)
{
	GMYAnglePID.ref += pantiltSpeedRef.y;
	GMPAnglePID.ref += pantiltSpeedRef.p;

	GMYAnglePID.fdb = motor[4].angle;
	GMPAnglePID.fdb = motor[5].angle;

	PID_Calc(&GMYAnglePID);
	PID_Calc(&GMPAnglePID);
}

static void PantiltVelocityControl(void)
{
	GMYSpeedPID.ref = GMYAnglePID.out;
	GMPSpeedPID.ref = GMPAnglePID.out;
	
	GMYSpeedPID.fdb = motor[4].rate;
	GMPSpeedPID.fdb = motor[5].rate;
	
	PID_Calc(&GMYSpeedPID);
	PID_Calc(&GMPSpeedPID);
}

void Ctl_Proc(void)
{
	WorkingStateSM();
	if(workingState == WORKING_STATE_STOP)
	{
		GUN_OFF();
		LASER_OFF();
		SPINNER_OFF();
		CM_CMD(0, 0, 0, 0);
		GM_CMD(0, 0);
	}
	else if(workingState == WORKING_STATE_NORMAL)
	{
		FunctionControl();
		ChassisPositionControl();
		ChassisVelocityControl();

		PantiltPositionControl();
		PantiltVelocityControl();
		PantiltCurrentControl();
	}
	
}

