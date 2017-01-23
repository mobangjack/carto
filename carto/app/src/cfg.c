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

#include "cfg.h"

/*************************************/
/*     Application Configuration     */
/*************************************/

static void Cfg_Load(Cfg_t* cfg)
{
	Flash_Read(CFG_DATA_START_ADDR, (u8*)cfg, sizeof(Cfg_t));
}

static uint8_t Cfg_Save(Cfg_t* cfg)
{
	return Flash_Write(CFG_DATA_START_ADDR, (u8*)cfg, sizeof(Cfg_t));
}

void Cfg_Init()
{
	Cfg_Load(&cfg);

	// IMU Configuration
	Imu_Config(&imu,
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
	Ahrs_Config(&ahrs, 2.0f, 0.02f);
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

void Cfg_Proc()
{
	Cfg_Save(&cfg);
}
