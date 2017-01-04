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

Ramp_t CM1Ramp = CM_RAMP_DEFAULT;
Ramp_t CM2Ramp = CM_RAMP_DEFAULT;
Ramp_t CM3Ramp = CM_RAMP_DEFAULT;
Ramp_t CM4Ramp = CM_RAMP_DEFAULT;
Ramp_t GMYRamp = GM_RAMP_DEFAULT;
Ramp_t GMPRamp = GM_RAMP_DEFAULT;

ChassisCurrent_t chassisCurrent;
PantiltCurrent_t pantiltCurrent;

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

static void FunctionControl(void)
{
	if (GET_FS(FUNCTIONAL_STATE_GUN)) {
		GUN_ON();
	} else {
		GUN_OFF();
	}
	if (GET_FS(FUNCTIONAL_STATE_LASER)) {
		LASER_ON();
	} else {
		LASER_OFF();
	}
	if (GET_FS(FUNCTIONAL_STATE_SPINNER)) {
		SPINNER_ON();
	} else {
		SPINNER_OFF();
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

	CM1AnglePID.fdb = encoder[0].angle;
	CM2AnglePID.fdb = encoder[1].angle;
	CM3AnglePID.fdb = encoder[2].angle;
	CM4AnglePID.fdb = encoder[3].angle;

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
	
	CM1SpeedPID.fdb = encoder[0].speed;
	CM2SpeedPID.fdb = encoder[1].speed;
	CM3SpeedPID.fdb = encoder[2].speed;
	CM4SpeedPID.fdb = encoder[3].speed;
	
	PID_Calc(&CM1SpeedPID);
	PID_Calc(&CM2SpeedPID);
	PID_Calc(&CM3SpeedPID);
	PID_Calc(&CM4SpeedPID);
}

static void ChassisCurrentControl(void)
{
	Ramp_Calc(&CM1Ramp);
	Ramp_Calc(&CM2Ramp);
	Ramp_Calc(&CM3Ramp);
	Ramp_Calc(&CM4Ramp);
	
	chassisCurrent.m1 = CM1SpeedPID.out * CM1Ramp.output;
	chassisCurrent.m2 = CM2SpeedPID.out * CM2Ramp.output;
	chassisCurrent.m3 = CM3SpeedPID.out * CM3Ramp.output;
	chassisCurrent.m4 = CM4SpeedPID.out * CM4Ramp.output;
}

static void ChassisMotorCommand(void)
{
	CM_CMD(chassisCurrent.m1, chassisCurrent.m2, chassisCurrent.m3, chassisCurrent.m4);
}

static void PantiltPositionControl(void)
{
	GMYAnglePID.ref += pantiltSpeedRef.y;
	GMPAnglePID.ref += pantiltSpeedRef.p;

	GMYAnglePID.fdb = encoder[4].angle;
	GMPAnglePID.fdb = encoder[5].angle;

	PID_Calc(&GMYAnglePID);
	PID_Calc(&GMPAnglePID);
}

static void PantiltVelocityControl(void)
{
	GMYSpeedPID.ref = GMYAnglePID.out;
	GMPSpeedPID.ref = GMPAnglePID.out;
	
	GMYSpeedPID.fdb = encoder[4].speed;
	GMPSpeedPID.fdb = encoder[5].speed;
	
	PID_Calc(&GMYSpeedPID);
	PID_Calc(&GMPSpeedPID);
}

static void PantiltCurrentControl(void)
{
	Ramp_Calc(&GMYRamp);
	Ramp_Calc(&GMPRamp);

	pantiltCurrent.y = GMYSpeedPID.out * GMYRamp.output;
	pantiltCurrent.p = GMPSpeedPID.out * GMPRamp.output;
}

static void PantiltMotorCommand(void)
{
	GM_CMD(pantiltCurrent.y, pantiltCurrent.p);
}

static uint32_t ms_tick = 0;
void Control(void)
{
	ms_tick++;
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
		ChassisCurrentControl();
		ChassisMotorCommand();

		PantiltPositionControl();
		PantiltVelocityControl();
		PantiltCurrentControl();
		PantiltMotorCommand();
	}
	
}

