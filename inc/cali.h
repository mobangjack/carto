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

#ifndef __CALI_H__
#define __CALI_H__

#include "flash.h"

#define CALI_FLASH_DATA_START_ADDRESS 	ADDR_FLASH_SECTOR_11

#define VERSION_A		1u
#define VERSION_B		6u
#define VERSION_C		4u
#define VERSION_D		0u
#define VERSION			(VERSION_A<<24)|(VERSION_B<<16)|(VERSION_C<<8)|(VERSION_D)

typedef struct
{
		uint8_t A;  //main version number
		uint8_t B;	//sub version number
		uint8_t C;	
		uint8_t D;	// test version number
}Version_t;

#define VERSION_DEFAULT	\
{\
	1,\
	6,\
	2,\
	0,\
}\

// calibration result enumeration
typedef enum
{
    CALI_STATE_ERR,
    CALI_STATE_IN,
    CALI_STATE_DONE,
}CaliState_e;

#define CALI_FLAG_NONE   0x00
#define CALI_FLAG_DONE   0x5A

#define CALI_START_FLAG_GYRO                  ((uint32_t)1<<1)
#define CALI_END_FLAG_GYRO                    ((uint32_t)1<<2)
#define CALI_START_FLAG_ACC                   ((uint32_t)1<<3)
#define CALI_START_FLAG_MAG                   ((uint32_t)1<<4)
#define CALI_END_FLAG_MAG                     ((uint32_t)1<<5)
#define CALI_START_FLAG_GIMBAL                ((uint32_t)1<<6)
#define CALI_END_FLAG_GIMBAL                  ((uint32_t)1<<7)
#define CALI_FLAG_PITCH_POSITION_PID          ((uint32_t)1<<8)
#define CALI_FLAG_PITCH_SPEED_PID             ((uint32_t)1<<9)
#define CALI_FLAG_YAW_POSITION_PID            ((uint32_t)1<<10)
#define CALI_FLAG_YAW_SPEED_PID               ((uint32_t)1<<11)

typedef __packed struct
{
	int16_t     yaw_max;
	int16_t     yaw_min;
    int16_t     yaw_offset;
    uint8_t     flag;
}GimbalYawCali_t;

typedef __packed struct
{
    int16_t     pitch_max;
    int16_t     pitch_min;
    int16_t     pitch_offset;
    uint8_t     flag;
}GimbalPitchCali_t;

typedef __packed struct
{
    int16_t     x_offset;
    int16_t     y_offset;
    int16_t     z_offset;
    uint8_t     flag;
}GyroCali_t;

typedef __packed struct
{
    int16_t     x_offset;
    int16_t     y_offset;
    int16_t     z_offset; 
    float       x_scale;
    float       y_scale;
    float       z_scale;
    uint8_t     flag;
}AccCali_t;

typedef __packed struct
{
    int16_t     x_offset;
    int16_t     y_offset;
    int16_t     z_offset;
    float       x_scale;
    float       y_scale;
    float       z_scale;    
    uint8_t     flag;
}MagCali_t;

typedef __packed struct
{
	int8_t pid_type;
	int8_t device_id;
	int16_t kp_offset;
	int16_t ki_offset;
	int16_t kd_offset;
}PIDCali_t;

typedef __packed struct 
{
    uint8_t            paramSavedFlag;                    // Header
    uint32_t           firmwareVersion;                   // Version
    GimbalYawCali_t    gimbalYawCaliData;                 // Gimbal yaw calibration data
    GimbalPitchCali_t  gimbalPitchCaliData;               // Gimbal pitch calibration data
    GyroCali_t         gyroCaliData;                      // Gyroscope calibration data
    AccCali_t          accCaliData;    	                  // Accelerator calibration data
    MagCali_t          magCaliData;		                  // Magnetometer calibration data
	PIDCali_t          gimbalYawPositionPIDCaliData;      // Yaw position PID calibration data
	PIDCali_t          gimbalYawSpeedPIDCaliData;         // Yaw speed PID calibration data
	PIDCali_t          gimbalPitchPositionPIDCaliData;    // Pitch position PID calibration data
	PIDCali_t          gimbalPitchSpeedPIDCaliData;       // Pitch speed PID calibration data
	PIDCali_t          chassisSpeedPIDCaliData;           // Chassis speed PID calibration data
}AppParam_t;

typedef enum
{
	REIMU = 1,
	REMOV = 2,
	REHMC = 3,
	REOFFSET = 4,
	REVERSION = 5,
	REERROR =6,
	REPID =7,
}UploadParamType_e;

extern GimbalYawCali_t gimbalYawSavedCaliData;
extern GimbalPitchCali_t gimbalPitchSavedCaliData;
extern GyroCali_t   gyroSavedCaliData;
extern AccCali_t    accSavedCaliData;
extern MagCali_t    magSavedCaliData;

extern PIDCali_t YawPositionSavedPID;
extern PIDCali_t YawSpeedSavedPID;
extern PIDCali_t PitchPositionSavedPID;
extern PIDCali_t PitchSpeedSavedPID;

extern PIDCali_t YawPositionCaliData;
extern PIDCali_t YawSpeedCaliData;
extern PIDCali_t PitchPostionCaliData;
extern PIDCali_t PitchSpeedCaliData;

extern AppParam_t appParam;

void AppParamInit(void);

void GetGimbalYawCaliData(GimbalYawCali_t *cali_data);
void GetGimbalPitchCaliData(GimbalPitchCali_t *cali_data);
void GetGyroCaliData(GyroCali_t *cali_data);
void GetAccCaliData(AccCali_t *cali_data);
void GetMagCaliData(MagCali_t *cali_data);
void GetPIDCaliData(PIDCali_t* cali_data);

uint8_t SetGimbalYawCaliData(GimbalYawCali_t *cali_data);
uint8_t SetGimbalPitchCaliData(GimbalPitchCali_t *cali_data);
uint8_t SetGyroCaliData(GyroCali_t *cali_data);
uint8_t SetAccCaliData(AccCali_t *cali_data);
uint8_t SetMagCaliData(MagCali_t *cali_data);
uint8_t SetPIDCaliData(PIDCali_t *cali_data);

void Sensor_Offset_Param_Init(AppParam_t *appParam);
void SetCaliCmdFlag(uint32_t flag);
void ResetCaliCmdFlag(uint32_t flag);
uint32_t GetCaliCmdFlagGrp(void);
uint8_t IsCaliCmdFlagSet(uint32_t flag);
CaliState_e GimbalCaliProcess(void);
CaliState_e GyroCaliProcess(void);
CaliState_e MagStartCaliProcess(void);
CaliState_e MagEndCaliProcess(void);

void CalibrateLoop(void);

uint8_t IsGimbalCalied(void);
uint8_t IsGyroCalied(void);
uint8_t IsAccCalied(void);
uint8_t IsMagCalied(void);
uint8_t IsAppParamCalied(void);


#endif

