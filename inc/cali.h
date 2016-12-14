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

#define VERSION_A		1u
#define VERSION_B		6u
#define VERSION_C		4u
#define VERSION_D		0u
#define VERSION			(VERSION_A<<24)|(VERSION_B<<16)|(VERSION_C<<8)|(VERSION_D)

#define CALI_FLASH_DATA_START_ADDRESS 	ADDR_FLASH_SECTOR_11

// calibration result enumeration
typedef enum
{
    CALI_STATE_ERR,
    CALI_STATE_IN,
    CALI_STATE_DONE,
}CALI_STATE_e;

typedef struct Version
{
		uint8_t A;  //main version number
		uint8_t B;	//sub version number
		uint8_t C;	
		uint8_t D;	// test version number
}Version;

#define VERSION_DEFAULT	\
{\
	1,\
	6,\
	2,\
	0,\
}\

#define PARAM_SAVED_FLAG                            0x5A   //header of the structure
#define PARAM_CALI_DONE                             0x5A 		
#define PARAM_CALI_NONE                             0x00

#define CALI_START_FLAG_GYRO                  ((uint32_t)1<<1)
#define CALI_END_FLAG_GYRO                    ((uint32_t)1<<2)
#define CALI_START_FLAG_ACC                   ((uint32_t)1<<3)
#define CALI_START_FLAG_MAG                   ((uint32_t)1<<4)
#define CALI_END_FLAG_MAG                     ((uint32_t)1<<5)
#define CALI_START_FLAG_GIMBAL                ((uint32_t)1<<6)
#define CALI_END_FLAG_GIMBAL                  ((uint32_t)1<<7)
#define CALI_FLAG_PID         				  ((uint32_t)1<<8)
#define CALI_FLAG_PITCH_SPEED_PID             ((uint32_t)1<<9)
#define CALI_FLAG_YAW_POSITION_PID            ((uint32_t)1<<10)
#define CALI_FLAG_YAW_SPEED_PID               ((uint32_t)1<<11)

typedef __packed struct
{
    int16_t     yaw;
    int16_t     pitch;
    uint8_t     flag;
}GimbalCali_t;

typedef __packed struct
{
    int16_t     x;
    int16_t     y;
    int16_t     z;
    uint8_t     flag;
}GyroCali_t;

typedef __packed struct
{
    int16_t     x;
    int16_t     y;
    int16_t     z; 
    float       scaleX;
    float       scaleY;
    float       scaleZ;
    uint8_t     flag;
}AccCali_t;

typedef __packed struct
{
    int16_t     x;
    int16_t     y;
    int16_t     z;
    float       scaleX;
    float       scaleY;
    float       scaleZ;    
    uint8_t     flag;
}MagCali_t;

typedef __packed struct
{
	int8_t pid_type;		// position PID
	int8_t motor_type;      //motor type ie: pitch yaw 201 202 203 204
	int16_t kp_offset;
	int16_t ki_offset;
	int16_t kd_offset;
}PIDCali_t;

typedef __packed struct 
{
    uint8_t     ParamSavedFlag;    		 //header
    uint32_t    FirmwareVersion;    	 //version
    GimbalCali_t GimbalCaliData;   //gimbal pitch yaw encoder offset
    GyroCali_t   GyroCaliData;     //gyro offset data
    AccCali_t    AccCaliData;    	 //ACC offset data
    MagCali_t    MagCaliData;		 //Mag offset data
	PIDCali_t   PitchPositionPID;
	PIDCali_t   PitchSpeedPID;
	PIDCali_t   YawPositionPID;
	PIDCali_t   YawSpeedPID;
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

extern GimbalCali_t GimbalSavedCaliData;    //gimbal pitch yaw encoder offset
extern GyroCali_t   GyroSavedCaliData;      //gyro offset data
extern AccCali_t    AccSavedCaliData;    		//ACC offset data
extern MagCali_t    MagSavedCaliData;				//Mag offset data

extern PIDCali_t PitchPostionCaliData;  //
extern PIDCali_t PitchSpeedCaliData;  //
extern PIDCali_t YawPositionCaliData;  //
extern PIDCali_t YawSpeedCaliData;  //

extern PIDCali_t PitchPositionSavedPID;        	//PID offset data
extern PIDCali_t PitchSpeedSavedPID;        	//PID offset data
extern PIDCali_t YawPositionSavedPID;        	//PID offset data
extern PIDCali_t YawSpeedSavedPID;        	//PID offset data

extern AppParam_t gAppParamStruct;
void AppParamInit(void);

void GetGimbalCaliData(GimbalCali_t *cali_data);
void GetGyroCaliData(GyroCali_t *cali_data);
void GetAccCaliData(AccCali_t *cali_data);
void GetMagCaliData(MagCali_t *cali_data);

//Flash
void SetGimbalCaliData(GimbalCali_t *cali_data);
void SetGyroCaliData(GyroCali_t *cali_data);
void SetAccCaliData(AccCali_t *cali_data);
void SetMagCaliData(MagCali_t *cali_data);
CALI_STATE_e PIDCaliProcess(PIDCali_t *cali_data);
//set or reset the Cali Cmd flag

void Sensor_Offset_Param_Init(AppParam_t *appParam);
void SetCaliCmdFlag(uint32_t flag);
void ResetCaliCmdFlag(uint32_t flag);
uint32_t GetCaliCmdFlagGrp(void);
uint8_t IsCaliCmdFlagSet(uint32_t flag);
CALI_STATE_e GimbalCaliProcess(void);
CALI_STATE_e GyroCaliProcess(void);
CALI_STATE_e MagStartCaliProcess(void);
CALI_STATE_e MagEndCaliProcess(void);
void CalibrateLoop(void);
uint8_t IsGimbalCalied(void);
uint8_t IsGyroCalied(void);
uint8_t IsAccCalied(void);
uint8_t IsMagCalied(void);
uint8_t Is_AppParam_Calied(void);


#endif

