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
 
#include "main.h"

WorkingState workingState = WORKING_STATE_PREPARE;
WorkingState lastWorkingState = WORKING_STATE_PREPARE;

PID CM1SpeedPID = CM_SPEED_PID_DEFAULT;
PID CM2SpeedPID = CM_SPEED_PID_DEFAULT;
PID CM3SpeedPID = CM_SPEED_PID_DEFAULT;
PID CM4SpeedPID = CM_SPEED_PID_DEFAULT;
PID GMYSpeedPID = GM_SPEED_PID_DEFAULT;
PID GMPSpeedPID = GM_SPEED_PID_DEFAULT;

Ramp CM1SpeedRamp = RAMP_DEFAULT;
Ramp CM2SpeedRamp = RAMP_DEFAULT;
Ramp CM3SpeedRamp = RAMP_DEFAULT;
Ramp CM4SpeedRamp = RAMP_DEFAULT;
Ramp GMYSpeedRamp = RAMP_DEFAULT;
Ramp GMPSpeedRamp = RAMP_DEFAULT;

ChassisCurrent chassisCurrent = {0};
GimbalsCurrent gimbalsCurrent = {0};

void WorkingStateSM(void)
{
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
			if(Encoder_IsOk(&CM1Encoder) && Encoder_IsOk(&CM1Encoder) && Encoder_IsOk(&CM1Encoder) && Encoder_IsOk(&CM1Encoder))
			{
				workingState = WORKING_STATE_NORMAL;
			}
		}break;
		case WORKING_STATE_NORMAL:
		{
			if(!(Encoder_IsOk(&CM1Encoder) && Encoder_IsOk(&CM1Encoder) && Encoder_IsOk(&CM1Encoder) && Encoder_IsOk(&CM1Encoder)))
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
	Mecanum mecanum;
	
	mecanum.x = chassisSpeed.x;
	mecanum.y = chassisSpeed.y;
	mecanum.z = chassisSpeed.z;
	
	Mecanum_Decompose(&mecanum);
	
	CM1SpeedPID.ref = mecanum.w1;
	CM2SpeedPID.ref = mecanum.w2;
	CM3SpeedPID.ref = mecanum.w3;
	CM4SpeedPID.ref = mecanum.w4;
	
	CM1SpeedPID.fdb = CM1Encoder.angle_rate;
	CM2SpeedPID.fdb = CM2Encoder.angle_rate;
	CM3SpeedPID.fdb = CM3Encoder.angle_rate;
	CM4SpeedPID.fdb = CM4Encoder.angle_rate;
	
	CM1SpeedPID.Calc(&CM1SpeedPID);
	CM2SpeedPID.Calc(&CM2SpeedPID);
	CM3SpeedPID.Calc(&CM3SpeedPID);
	CM4SpeedPID.Calc(&CM4SpeedPID);
	
	CM1SpeedRamp.Calc(&CM1SpeedRamp);
	CM2SpeedRamp.Calc(&CM2SpeedRamp);
	CM3SpeedRamp.Calc(&CM3SpeedRamp);
	CM4SpeedRamp.Calc(&CM4SpeedRamp);
	
	chassisCurrent.m1 = CM1SpeedPID.output * CM1SpeedRamp.output;
	chassisCurrent.m2 = CM2SpeedPID.output * CM2SpeedRamp.output;
	chassisCurrent.m3 = CM3SpeedPID.output * CM3SpeedRamp.output;
	chassisCurrent.m4 = CM4SpeedPID.output * CM4SpeedRamp.output;
	
	SetCMCurrent(CAN2, chassisCurrent.m1, chassisCurrent.m2, chassisCurrent.m3, chassisCurrent.m4);
}

void GMControlLoop(void)
{
	GMYSpeedPID.ref = gimbalsSpeed.yaw;
	GMPSpeedPID.ref = gimbalsSpeed.pit;
	
	GMYSpeedPID.fdb = GMYEncoder.angle_rate;
	GMPSpeedPID.fdb = GMPEncoder.angle_rate;
	
	GMYSpeedPID.Calc(&CM1SpeedPID);
	GMPSpeedPID.Calc(&CM2SpeedPID);
	
	GMYSpeedRamp.Calc(&GMYSpeedRamp);
	GMPSpeedRamp.Calc(&GMPSpeedRamp);
	
	gimbalsCurrent.yaw = GMYSpeedPID.output * GMYSpeedRamp.output;
	gimbalsCurrent.pit = GMPSpeedPID.output * GMPSpeedRamp.output;
	
	SetGMCurrent(CAN2, gimbalsCurrent.yaw, gimbalsCurrent.pit);
}

static uint32_t ms_tick = 0;
void ControlTask(void)
{
	ms_tick++;
	WorkingStateSM();
	if(workingState == WORKING_STATE_STOP)
	{
		Encoder_Reset(&CM1Encoder);
		Encoder_Reset(&CM2Encoder);
		Encoder_Reset(&CM3Encoder);
		Encoder_Reset(&CM4Encoder);
		Encoder_Reset(&GMYEncoder);
		Encoder_Reset(&GMPEncoder);
	}
	else if(workingState == WORKING_STATE_NORMAL)
	{
		//GMControlLoop();
		CMControlLoop();
	}
	
}

