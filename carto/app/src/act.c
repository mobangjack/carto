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

#include "act.h"

ChassisCurrent_t chassisCurrent;
PantiltCurrent_t pantiltCurrent;

Ramp_t CM1Ramp = RAMP_DEFAULT;
Ramp_t CM2Ramp = RAMP_DEFAULT;
Ramp_t CM3Ramp = RAMP_DEFAULT;
Ramp_t CM4Ramp = RAMP_DEFAULT;
Ramp_t GMYRamp = RAMP_DEFAULT;
Ramp_t GMPRamp = RAMP_DEFAULT;

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
	EC60_CMD(chassisCurrent.m1, chassisCurrent.m2, chassisCurrent.m3, chassisCurrent.m4);
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
	RM6025_CMD(pantiltCurrent.y, pantiltCurrent.p);
}

static void FunctionControl(void)
{
	if (FS_Get(FUNCTIONAL_STATE_GUN)) {
		GUN_ON();
	} else {
		GUN_OFF();
	}
	if (FS_Get(FUNCTIONAL_STATE_LASER)) {
		LASER_ON();
	} else {
		LASER_OFF();
	}
	if (FS_Get(FUNCTIONAL_STATE_SPINNER)) {
		SPINNER_ON();
	} else {
		SPINNER_OFF();
	}
}

void Act_Proc()
{
	ChassisCurrentControl();
	ChassisMotorCommand();
	PantiltCurrentControl();
	PantiltMotorCommand();
	FunctionControl();
}
