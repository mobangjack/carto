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

PID_t GMYAnglePID = CM_ANGLE_PID_DEFAULT;
PID_t GMPAnglePID = CM_ANGLE_PID_DEFAULT;

PID_t CM1SpeedPID = CM_SPEED_PID_DEFAULT;
PID_t CM2SpeedPID = CM_SPEED_PID_DEFAULT;
PID_t CM3SpeedPID = CM_SPEED_PID_DEFAULT;
PID_t CM4SpeedPID = CM_SPEED_PID_DEFAULT;
PID_t GMYSpeedPID = GM_SPEED_PID_DEFAULT;
PID_t GMPSpeedPID = GM_SPEED_PID_DEFAULT;

Ramp_t CM1SpeedRamp = CM_SPEED_RAMP_DEFAULT;
Ramp_t CM2SpeedRamp = CM_SPEED_RAMP_DEFAULT;
Ramp_t CM3SpeedRamp = CM_SPEED_RAMP_DEFAULT;
Ramp_t CM4SpeedRamp = CM_SPEED_RAMP_DEFAULT;
Ramp_t GMYSpeedRamp = GM_SPEED_RAMP_DEFAULT;
Ramp_t GMPSpeedRamp = GM_SPEED_RAMP_DEFAULT;

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
static void ChassisControl(void)
{
	Mecanum_t mecanumVelocity;

	mecanumVelocity.x = chassisSpeedRef.x;
	mecanumVelocity.y = chassisSpeedRef.y;
	mecanumVelocity.z = chassisSpeedRef.z;
	
	Mecanum_Decompose(&mecanumVelocity);
	
	CM1SpeedPID.ref = mecanumVelocity.w1;
	CM2SpeedPID.ref = mecanumVelocity.w2;
	CM3SpeedPID.ref = mecanumVelocity.w3;
	CM4SpeedPID.ref = mecanumVelocity.w4;
	
	CM1SpeedPID.fdb = encoder[0].speed;
	CM2SpeedPID.fdb = encoder[1].speed;
	CM3SpeedPID.fdb = encoder[2].speed;
	CM4SpeedPID.fdb = encoder[3].speed;
	
	PID_Calc(&CM1SpeedPID);
	PID_Calc(&CM2SpeedPID);
	PID_Calc(&CM3SpeedPID);
	PID_Calc(&CM4SpeedPID);

	Ramp_Calc(&CM1SpeedRamp);
	Ramp_Calc(&CM2SpeedRamp);
	Ramp_Calc(&CM3SpeedRamp);
	Ramp_Calc(&CM4SpeedRamp);
	
	chassisCurrent.m1 = CM1SpeedPID.out * CM1SpeedRamp.output;
	chassisCurrent.m2 = CM2SpeedPID.out * CM2SpeedRamp.output;
	chassisCurrent.m3 = CM3SpeedPID.out * CM3SpeedRamp.output;
	chassisCurrent.m4 = CM4SpeedPID.out * CM4SpeedRamp.output;
	
	CM_CMD(chassisCurrent.m1, chassisCurrent.m2, chassisCurrent.m3, chassisCurrent.m4);
}

static void PantiltControl(void)
{
	GMYAnglePID.ref += pantiltSpeedRef.y;
	GMPAnglePID.ref += pantiltSpeedRef.p;

	GMYAnglePID.fdb = encoder[4].angle;
	GMPAnglePID.fdb = encoder[5].angle;

	PID_Calc(&GMYAnglePID);
	PID_Calc(&GMPAnglePID);

	GMYSpeedPID.ref = GMYAnglePID.out;
	GMPSpeedPID.ref = GMPAnglePID.out;
	
	GMYSpeedPID.fdb = encoder[4].speed;
	GMPSpeedPID.fdb = encoder[5].speed;
	
	PID_Calc(&GMYSpeedPID);
	PID_Calc(&GMPSpeedPID);

	Ramp_Calc(&GMYSpeedRamp);
	Ramp_Calc(&GMPSpeedRamp);
	
	pantiltCurrent.y = GMYSpeedPID.out * GMYSpeedRamp.output;
	pantiltCurrent.p = GMPSpeedPID.out * GMPSpeedRamp.output;
	
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
		ChassisControl();
		PantiltControl();
	}
	
}

