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

Cfg_t cfg = CFG_DEFAULT;

IMU_t imu;
Mag_t mag;
AHRS_t ahrs;
uint8_t div = 4;
Ramp_t ramp;
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

FunctionalState_t functionalStateRef;
FunctionalState_t functionalStateFdb;
FunctionalState_t functionalStateCmd;

PantiltState_t pantiltPositionRef;
PantiltState_t pantiltPositionFdb;
PantiltState_t pantiltPositionCmd;

PantiltState_t pantiltVelocityRef;
PantiltState_t pantiltVelocityFdb;
PantiltState_t pantiltVelocityCmd;

ChassisState_t chassisPositionRef;
ChassisState_t chassisPositionFdb;
ChassisState_t chassisPositionCmd;

ChassisState_t chassisVelocityRef;
ChassisState_t chassisVelocityFdb;
ChassisState_t chassisVelocityCmd;

MecanumState_t mecanumPositionRef;
MecanumState_t mecanumPositionFdb;
MecanumState_t mecanumPositionCmd;

MecanumState_t mecanumVelocityRef;
MecanumState_t mecanumVelocityFdb;
MecanumState_t mecanumVelocityCmd;

void App_Init()
{
	Bsp_Config();

	Cfg_Load(&cfg);

	// IMU Configuration
	IMU_Config(&imu,
		cfg.imu.ax_offset,
		cfg.imu.ay_offset,
		cfg.imu.az_offset,
		cfg.imu.gx_offset,
		cfg.imu.gy_offset,
		cfg.imu.gz_offset);
	// Mag Configuration
	Mag_Config(&mag,
		cfg.mag.mx_offset,
		cfg.mag.my_offset,
		cfg.mag.mz_offset);
	// Attitude Heading Reference System Configuration
	AHRS_Config(&ahrs, 2.0f, 0.02f);
	// Ramp Configuration
	Ramp_Config(&ramp, cfg.ctl.rmp);
	/*******************************************/
	/* Mecanum Wheel Power Transmission System */
	/*              Configuration              */
	/*******************************************/
	/*              2        1                 */
	/*                  |y                     */
	/*                 b|___x                  */
	/*               z    a                    */
	/*              3        4                 */
	/*                                         */
	/*******************************************/
	Mecanum_Config(&mecanum,
		cfg.cha.mecCfg.lx,
		cfg.cha.mecCfg.ly,
		cfg.cha.mecCfg.r1,
		cfg.cha.mecCfg.r2);
	// Gimbal Yaw Angle PID Configuration
	PID_Config(&GMYAnglePID,
		cfg.yaw.posPID.kp,
		cfg.yaw.posPID.ki,
		cfg.yaw.posPID.kd,
		cfg.yaw.posPID.it,
		cfg.yaw.posPID.Pmax,
		cfg.yaw.posPID.Imax,
		cfg.yaw.posPID.Dmax,
		cfg.yaw.posPID.Omax);
	// Gimbal Yaw Speed PID Configuration
	PID_Config(&GMYSpeedPID,
		cfg.yaw.spdPID.kp,
		cfg.yaw.spdPID.ki,
		cfg.yaw.spdPID.kd,
		cfg.yaw.spdPID.it,
		cfg.yaw.spdPID.Pmax,
		cfg.yaw.spdPID.Imax,
		cfg.yaw.spdPID.Dmax,
		cfg.yaw.spdPID.Omax);
	// Gimbal Pitch Angle PID Configuration
	PID_Config(&GMPAnglePID,
		cfg.pit.posPID.kp,
		cfg.pit.posPID.ki,
		cfg.pit.posPID.kd,
		cfg.pit.posPID.it,
		cfg.pit.posPID.Pmax,
		cfg.pit.posPID.Imax,
		cfg.pit.posPID.Dmax,
		cfg.pit.posPID.Omax);
	// Gimbal Pitch Speed PID Configuration
	PID_Config(&GMPSpeedPID,
		cfg.pit.spdPID.kp,
		cfg.pit.spdPID.ki,
		cfg.pit.spdPID.kd,
		cfg.pit.spdPID.it,
		cfg.pit.spdPID.Pmax,
		cfg.pit.spdPID.Imax,
		cfg.pit.spdPID.Dmax,
		cfg.pit.spdPID.Omax);
	// Chassis Motor Number 1 Angle PID Configuration
	PID_Config(&CM1AnglePID,
		cfg.cha.posPID.kp,
		cfg.cha.posPID.ki,
		cfg.cha.posPID.kd,
		cfg.cha.posPID.it,
		cfg.cha.posPID.Pmax,
		cfg.cha.posPID.Imax,
		cfg.cha.posPID.Dmax,
		cfg.cha.posPID.Omax);
	// Chassis Motor Number 1 Speed PID Configuration
	PID_Config(&CM1SpeedPID,
		cfg.cha.spdPID.kp,
		cfg.cha.spdPID.ki,
		cfg.cha.spdPID.kd,
		cfg.cha.spdPID.it,
		cfg.cha.spdPID.Pmax,
		cfg.cha.spdPID.Imax,
		cfg.cha.spdPID.Dmax,
		cfg.cha.spdPID.Omax);
	// Chassis Motor Number 2 Angle PID Configuration
	PID_Config(&CM2AnglePID,
		cfg.cha.posPID.kp,
		cfg.cha.posPID.ki,
		cfg.cha.posPID.kd,
		cfg.cha.posPID.it,
		cfg.cha.posPID.Pmax,
		cfg.cha.posPID.Imax,
		cfg.cha.posPID.Dmax,
		cfg.cha.posPID.Omax);
	// Chassis Motor Number 2 Speed PID Configuration
	PID_Config(&CM2SpeedPID,
		cfg.cha.spdPID.kp,
		cfg.cha.spdPID.ki,
		cfg.cha.spdPID.kd,
		cfg.cha.spdPID.it,
		cfg.cha.spdPID.Pmax,
		cfg.cha.spdPID.Imax,
		cfg.cha.spdPID.Dmax,
		cfg.cha.spdPID.Omax);
	// Chassis Motor Number 3 Angle PID Configuration
	PID_Config(&CM3AnglePID,
		cfg.cha.posPID.kp,
		cfg.cha.posPID.ki,
		cfg.cha.posPID.kd,
		cfg.cha.posPID.it,
		cfg.cha.posPID.Pmax,
		cfg.cha.posPID.Imax,
		cfg.cha.posPID.Dmax,
		cfg.cha.posPID.Omax);
	// Chassis Motor Number 3 Speed PID Configuration
	PID_Config(&CM3SpeedPID,
		cfg.cha.spdPID.kp,
		cfg.cha.spdPID.ki,
		cfg.cha.spdPID.kd,
		cfg.cha.spdPID.it,
		cfg.cha.spdPID.Pmax,
		cfg.cha.spdPID.Imax,
		cfg.cha.spdPID.Dmax,
		cfg.cha.spdPID.Omax);
	// Chassis Motor Number 4 Angle PID Configuration
	PID_Config(&CM4AnglePID,
		cfg.cha.posPID.kp,
		cfg.cha.posPID.ki,
		cfg.cha.posPID.kd,
		cfg.cha.posPID.it,
		cfg.cha.posPID.Pmax,
		cfg.cha.posPID.Imax,
		cfg.cha.posPID.Dmax,
		cfg.cha.posPID.Omax);
	// Chassis Motor Number 4 Speed PID Configuration
	PID_Config(&CM4SpeedPID,
		cfg.cha.spdPID.kp,
		cfg.cha.spdPID.ki,
		cfg.cha.spdPID.kd,
		cfg.cha.spdPID.it,
		cfg.cha.spdPID.Pmax,
		cfg.cha.spdPID.Imax,
		cfg.cha.spdPID.Dmax,
		cfg.cha.spdPID.Omax);

}

void App_Reset()
{
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
}

void App_Sync()
{
	if (Clk_GetUsTick() % div == 0) {
		Odo_Proc();
		Ctl_Proc();
		Act_Proc();
	}
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

