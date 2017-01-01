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
 
#include "sysctl.h"

/*
WorkingState_t workingState = WORKING_STATE_PREPARE;

PID_t CM1PositionPID = CM_POSITION_PID_DEFAULT;
PID_t CM2PositionPID = CM_POSITION_PID_DEFAULT;
PID_t CM3PositionPID = CM_POSITION_PID_DEFAULT;
PID_t CM4PositionPID = CM_POSITION_PID_DEFAULT;
PID_t GMYPositionPID = CM_POSITION_PID_DEFAULT;
PID_t GMPPositionPID = CM_POSITION_PID_DEFAULT;

PID_t CM1SpeedPID = CM_SPEED_PID_DEFAULT;
PID_t CM2SpeedPID = CM_SPEED_PID_DEFAULT;
PID_t CM3SpeedPID = CM_SPEED_PID_DEFAULT;
PID_t CM4SpeedPID = CM_SPEED_PID_DEFAULT;
PID_t GMYSpeedPID = GM_SPEED_PID_DEFAULT;
PID_t GMPSpeedPID = GM_SPEED_PID_DEFAULT;

Ramp_t CM1SpeedRamp = RAMP_DEFAULT;
Ramp_t CM2SpeedRamp = RAMP_DEFAULT;
Ramp_t CM3SpeedRamp = RAMP_DEFAULT;
Ramp_t CM4SpeedRamp = RAMP_DEFAULT;
Ramp_t GMYSpeedRamp = RAMP_DEFAULT;
Ramp_t GMPSpeedRamp = RAMP_DEFAULT;

ChassisCurrent_t chassisCurrent;
GimbalsCurrent_t gimbalsCurrent;

//float ZGyroAngle = 0;

void WorkingStateSM(void)
{
	static WorkingState_t lastWorkingState = WORKING_STATE_PREPARE;
	lastWorkingState = workingState;
	if(inputMode == INPUT_MODE_NO)
	{
		workingState = WORKING_STATE_STOP;
		return;
	}
	switch(workingState)
	{
		case WORKING_STATE_PREPARE:
		{
			if(Encoder_IsOk(&ESC1) && Encoder_IsOk(&ESC1) && Encoder_IsOk(&ESC1) && Encoder_IsOk(&ESC1))
			{
				workingState = WORKING_STATE_NORMAL;
			}
		}break;
		case WORKING_STATE_NORMAL:
		{
			if(!(Encoder_IsOk(&ESC1) && Encoder_IsOk(&ESC1) && Encoder_IsOk(&ESC1) && Encoder_IsOk(&ESC1)))
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

void CMControlLoop(void)
{
	Mecanum_t mecanum;
	
	mecanum.x = chassisSpeedRef.x;
	mecanum.y = chassisSpeedRef.y;
	mecanum.z = chassisSpeedRef.z;
	
	Mecanum_Decompose(&mecanum);
	
	CM1SpeedPID.ref = mecanum.w1;
	CM2SpeedPID.ref = mecanum.w2;
	CM3SpeedPID.ref = mecanum.w3;
	CM4SpeedPID.ref = mecanum.w4;
	
	CM1SpeedPID.fdb = ESC1.rate;
	CM2SpeedPID.fdb = ESC2.rate;
	CM3SpeedPID.fdb = ESC3.rate;
	CM4SpeedPID.fdb = ESC4.rate;
	
	CM1SpeedPID.Calc(&CM1SpeedPID);
	CM2SpeedPID.Calc(&CM2SpeedPID);
	CM3SpeedPID.Calc(&CM3SpeedPID);
	CM4SpeedPID.Calc(&CM4SpeedPID);
	
	CM1SpeedRamp.Calc(&CM1SpeedRamp);
	CM2SpeedRamp.Calc(&CM2SpeedRamp);
	CM3SpeedRamp.Calc(&CM3SpeedRamp);
	CM4SpeedRamp.Calc(&CM4SpeedRamp);
	
	chassisCurrent.m1 = CM1SpeedPID.out * CM1SpeedRamp.output;
	chassisCurrent.m2 = CM2SpeedPID.out * CM2SpeedRamp.output;
	chassisCurrent.m3 = CM3SpeedPID.out * CM3SpeedRamp.output;
	chassisCurrent.m4 = CM4SpeedPID.out * CM4SpeedRamp.output;
	
	EC60_CMD(CAN2, chassisCurrent.m1, chassisCurrent.m2, chassisCurrent.m3, chassisCurrent.m4);
}

void GMControlLoop(void)
{
	GMYSpeedPID.ref = gimbalsSpeedRef.y;
	GMPSpeedPID.ref = gimbalsSpeedRef.p;
	
	GMYSpeedPID.fdb = ESC5.rate;
	GMPSpeedPID.fdb = ESC6.rate;
	
	GMYSpeedPID.Calc(&CM1SpeedPID);
	GMPSpeedPID.Calc(&CM2SpeedPID);
	
	GMYSpeedRamp.Calc(&GMYSpeedRamp);
	GMPSpeedRamp.Calc(&GMPSpeedRamp);
	
	gimbalsCurrent.y = GMYSpeedPID.out * GMYSpeedRamp.output;
	gimbalsCurrent.p = GMPSpeedPID.out * GMPSpeedRamp.output;
	
	RM6025_CMD(CAN2, gimbalsCurrent.y, gimbalsCurrent.p);
}

static uint32_t ms_tick = 0;
void Control(void)
{
	ms_tick++;
	WorkingStateSM();
	if(workingState == WORKING_STATE_STOP)
	{
		Encoder_Reset(&ESC1);
		Encoder_Reset(&ESC2);
		Encoder_Reset(&ESC3);
		Encoder_Reset(&ESC4);
		Encoder_Reset(&ESC5);
		Encoder_Reset(&ESC6);
	}
	else if(workingState == WORKING_STATE_NORMAL)
	{
		//GMControlLoop();
		CMControlLoop();
	}
	
}
*/
