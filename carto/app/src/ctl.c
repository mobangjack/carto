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

/**********************************************/
/*              Logic Controller              */
/**********************************************/

/**********************************************/
/*             Exported Variables             */
/**********************************************/
WorkingState_e workingState;
WorkingStateSwitch_e workingStateSwitch;

PID_t CM1SpeedPID;
PID_t CM2SpeedPID;
PID_t CM3SpeedPID;
PID_t CM4SpeedPID;
PID_t GMYAnglePID;
PID_t GMYSpeedPID;
PID_t GMPAnglePID;
PID_t GMPSpeedPID;

Ramp_t CM1SpeedRamp;
Ramp_t CM2SpeedRamp;
Ramp_t CM3SpeedRamp;
Ramp_t CM4SpeedRamp;
Ramp_t GMYSpeedRamp;
Ramp_t GMPSpeedRamp;

PeriphsState_t functionalStateCtl;
PantiltState_t pantiltVelocityCtl;
PantiltState_t pantiltCurrentsCtl;
MecanumState_t mecanumCurrentsCtl;

/**********************************************/
/*        Working State Switch Machine        */
/**********************************************/
static void WorkingStateSwitchMach()
{
	switch (workingState) {
	case WORKING_STATE_STOP:
		// Current working state is STOP.
		// If NO fatal error occurs, step into PREPARE stage.
		// Otherwise stay the same.
		if (!Wdg_IsErrSet(WDG_ERR_FATAL)) {
			workingState = WORKING_STATE_PREPARE;
			workingStateSwitch = WORKING_STATE_SWITCH_S2P;
		}
		break;
	case WORKING_STATE_PREPARE:
		// Current working state is PREPARE.
		// If any fatal error occurs, force STOP,
		// else if system initialization done, step into NORMAL stage.
		// Otherwise stay the same.
		if (Wdg_IsErrSet(WDG_ERR_FATAL)) {
			workingState = WORKING_STATE_STOP;
			workingStateSwitch = WORKING_STATE_SWITCH_P2S;
		} else if (Ini_Ok()){
			workingState = WORKING_STATE_NORMAL;
			workingStateSwitch = WORKING_STATE_SWITCH_P2N;
		}
		break;
	case WORKING_STATE_NORMAL:
		// Current working state is NORMAL.
		// If any fatal error occurs, force STOP,
		// else if system initialization is NOT done, return to PREPARE state.
		// Otherwise stay the same.
		if (Wdg_IsErrSet(WDG_ERR_FATAL)) {
			workingState = WORKING_STATE_STOP;
			workingStateSwitch = WORKING_STATE_SWITCH_N2S;
		} else if (!Ini_Ok()) {
			workingState = WORKING_STATE_PREPARE;
			workingStateSwitch = WORKING_STATE_SWITCH_N2P;
		}
		break;
	default:
		break;
	}
}

/**********************************************/
/*        Working State Switch Process        */
/**********************************************/
static void WorkingStateSwitchProc()
{
	switch (workingStateSwitch) {
	case WORKING_STATE_SWITCH_S2P: // Stop -> Prepare
		break;
	case WORKING_STATE_SWITCH_P2N: // Prepare -> Normal
		break;
	case WORKING_STATE_SWITCH_N2P: // Normal -> Prepare
		break;
	case WORKING_STATE_SWITCH_P2S: // Prepare -> Stop
		break;
	case WORKING_STATE_SWITCH_N2S: // Normal -> Stop
		break;
	default:
		break;
	}
}

/**********************************************/
/*    Peripherals Functional State Control    */
/**********************************************/
static void FunctionalStateControl()
{
	if (FS_Get(&functionalStateRef, FS_GUN)) {
		FS_Set(&functionalStateCtl, FS_GUN | FS_LASER);
	} else {
		FS_Clr(&functionalStateCtl, FS_GUN | FS_LASER | FS_SPINNER);
	}
}

/**********************************************/
/*          Chassis Velocity Control          */
/**********************************************/
static void ChassisVelocityControl()
{
	mecanumCurrentsCtl.w1 = PID_Calc(&CM1SpeedPID, mecanumVelocityRef.w1, mecanumVelocityFdb.w1) * Ramp_Calc(&CM1SpeedRamp);
	mecanumCurrentsCtl.w2 = PID_Calc(&CM2SpeedPID, mecanumVelocityRef.w2, mecanumVelocityFdb.w2) * Ramp_Calc(&CM2SpeedRamp);
	mecanumCurrentsCtl.w3 = PID_Calc(&CM3SpeedPID, mecanumVelocityRef.w3, mecanumVelocityFdb.w3) * Ramp_Calc(&CM3SpeedRamp);
	mecanumCurrentsCtl.w4 = PID_Calc(&CM4SpeedPID, mecanumVelocityRef.w4, mecanumVelocityFdb.w4) * Ramp_Calc(&CM4SpeedRamp);
}

/**********************************************/
/*          Pantilt Position Control          */
/**********************************************/
static void PantiltPositionControl()
{
	pantiltVelocityCtl.y = PID_Calc(&GMYAnglePID, pantiltPositionRef.y, pantiltPositionFdb.y);
	pantiltVelocityCtl.p = PID_Calc(&GMPAnglePID, pantiltPositionRef.p, pantiltPositionFdb.p);
	pantiltCurrentsCtl.y = PID_Calc(&GMYSpeedPID, pantiltVelocityCtl.y, pantiltVelocityFdb.y) * Ramp_Calc(&GMYSpeedRamp);
	pantiltCurrentsCtl.p = PID_Calc(&GMPSpeedPID, pantiltVelocityCtl.p, pantiltVelocityFdb.p) * Ramp_Calc(&GMPSpeedRamp);
}

/**********************************************/
/*       Logic Controller Initialization      */
/**********************************************/
void Ctl_Init()
{
	workingState = WORKING_STATE_STOP;
	workingStateSwitch = WORKING_STATE_SWITCH_NOP;

	FS_Clr(&functionalStateCtl, FS_ALL);
	GS_Set(&pantiltVelocityCtl, 0, 0);
	GS_Set(&pantiltCurrentsCtl, 0, 0);
	MS_Set(&mecanumCurrentsCtl, 0, 0, 0, 0);

	PID_Reset(&CM1SpeedPID);
	PID_Reset(&CM2SpeedPID);
	PID_Reset(&CM3SpeedPID);
	PID_Reset(&CM4SpeedPID);
	PID_Reset(&GMYAnglePID);
	PID_Reset(&GMYSpeedPID);
	PID_Reset(&GMPAnglePID);
	PID_Reset(&GMPSpeedPID);

	Ramp_Reset(&CM1SpeedRamp);
	Ramp_Reset(&CM2SpeedRamp);
	Ramp_Reset(&CM3SpeedRamp);
	Ramp_Reset(&CM4SpeedRamp);
	Ramp_Reset(&GMYSpeedRamp);
	Ramp_Reset(&GMPSpeedRamp);
}

/**********************************************/
/*          Logic Controller Process          */
/**********************************************/
void Ctl_Proc()
{
	WorkingStateSwitchMach();
	WorkingStateSwitchProc();
	if(workingState == WORKING_STATE_NORMAL)
	{
		FunctionalStateControl();
		ChassisVelocityControl();
		PantiltPositionControl();
	}
}

