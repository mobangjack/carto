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

Cfg_t cfg = CFG_DEFAULT;

AHRS_t ahrs;
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

void App_Init(void)
{
	Cfg_Load(&cfg);

	// Attitude Heading Reference System Configuration
	AHRS_Config(&ahrs);
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
			cfg.yaw.posPID.Pmax,
			cfg.yaw.posPID.Imax,
			cfg.yaw.posPID.Dmax,
			cfg.yaw.posPID.outmax);
	// Gimbal Yaw Speed PID Configuration
	PID_Config(&GMYSpeedPID,
			cfg.yaw.spdPID.kp,
			cfg.yaw.spdPID.ki,
			cfg.yaw.spdPID.kd,
			cfg.yaw.spdPID.Pmax,
			cfg.yaw.spdPID.Imax,
			cfg.yaw.spdPID.Dmax,
			cfg.yaw.spdPID.outmax);
	// Gimbal Pitch Angle PID Configuration
	PID_Config(&GMPAnglePID,
			cfg.pit.posPID.kp,
			cfg.pit.posPID.ki,
			cfg.pit.posPID.kd,
			cfg.pit.posPID.Pmax,
			cfg.pit.posPID.Imax,
			cfg.pit.posPID.Dmax,
			cfg.pit.posPID.outmax);
	// Gimbal Pitch Speed PID Configuration
	PID_Config(&GMPSpeedPID,
			cfg.pit.spdPID.kp,
			cfg.pit.spdPID.ki,
			cfg.pit.spdPID.kd,
			cfg.pit.spdPID.Pmax,
			cfg.pit.spdPID.Imax,
			cfg.pit.spdPID.Dmax,
			cfg.pit.spdPID.outmax);
	// Chassis Motor Number 1 Angle PID Configuration
	PID_Config(&CM1AnglePID,
			cfg.cha.posPID.kp,
			cfg.cha.posPID.ki,
			cfg.cha.posPID.kd,
			cfg.cha.posPID.Pmax,
			cfg.cha.posPID.Imax,
			cfg.cha.posPID.Dmax,
			cfg.cha.posPID.outmax);
	// Chassis Motor Number 1 Speed PID Configuration
	PID_Config(&CM1SpeedPID,
			cfg.cha.spdPID.kp,
			cfg.cha.spdPID.ki,
			cfg.cha.spdPID.kd,
			cfg.cha.spdPID.Pmax,
			cfg.cha.spdPID.Imax,
			cfg.cha.spdPID.Dmax,
			cfg.cha.spdPID.outmax);
	// Chassis Motor Number 2 Angle PID Configuration
	PID_Config(&CM2AnglePID,
			cfg.cha.posPID.kp,
			cfg.cha.posPID.ki,
			cfg.cha.posPID.kd,
			cfg.cha.posPID.Pmax,
			cfg.cha.posPID.Imax,
			cfg.cha.posPID.Dmax,
			cfg.cha.posPID.outmax);
	// Chassis Motor Number 2 Speed PID Configuration
	PID_Config(&CM2SpeedPID,
			cfg.cha.spdPID.kp,
			cfg.cha.spdPID.ki,
			cfg.cha.spdPID.kd,
			cfg.cha.spdPID.Pmax,
			cfg.cha.spdPID.Imax,
			cfg.cha.spdPID.Dmax,
			cfg.cha.spdPID.outmax);
	// Chassis Motor Number 3 Angle PID Configuration
	PID_Config(&CM3AnglePID,
			cfg.cha.posPID.kp,
			cfg.cha.posPID.ki,
			cfg.cha.posPID.kd,
			cfg.cha.posPID.Pmax,
			cfg.cha.posPID.Imax,
			cfg.cha.posPID.Dmax,
			cfg.cha.posPID.outmax);
	// Chassis Motor Number 3 Speed PID Configuration
	PID_Config(&CM3SpeedPID,
			cfg.cha.spdPID.kp,
			cfg.cha.spdPID.ki,
			cfg.cha.spdPID.kd,
			cfg.cha.spdPID.Pmax,
			cfg.cha.spdPID.Imax,
			cfg.cha.spdPID.Dmax,
			cfg.cha.spdPID.outmax);
	// Chassis Motor Number 4 Angle PID Configuration
	PID_Config(&CM4AnglePID,
			cfg.cha.posPID.kp,
			cfg.cha.posPID.ki,
			cfg.cha.posPID.kd,
			cfg.cha.posPID.Pmax,
			cfg.cha.posPID.Imax,
			cfg.cha.posPID.Dmax,
			cfg.cha.posPID.outmax);
	// Chassis Motor Number 4 Speed PID Configuration
	PID_Config(&CM4SpeedPID,
			cfg.cha.spdPID.kp,
			cfg.cha.spdPID.ki,
			cfg.cha.spdPID.kd,
			cfg.cha.spdPID.Pmax,
			cfg.cha.spdPID.Imax,
			cfg.cha.spdPID.Dmax,
			cfg.cha.spdPID.outmax);

}

uint8_t App_Cfg(void)
{
	return Cfg_Save(&cfg);
}

void App_Run(void)
{

}
