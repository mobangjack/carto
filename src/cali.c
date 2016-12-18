#include "main.h"
//#include "protocal.h"

AppParam_t appParam;
static GyroCali_t gyroCaliData;
static GimbalYawCali_t  gimbalYawCaliData;
static GimbalPitchCali_t  gimbalPitchCaliData;
static MagCali_t  MagCaliData;
PIDCali_t PIDCaliData;

GimbalYawCali_t GimbalYawSavedCaliData;
GimbalPitchCali_t GimbalPitchSavedCaliData;
GyroCali_t GyroSavedCaliData;
AccCali_t AccSavedCaliData;
MagCali_t MagSavedCaliData;
PIDCali_t PitchPositionSavedPID;
PIDCali_t PitchSpeedSavedPID;
PIDCali_t YawPositionSavedPID;
PIDCali_t YawSpeedSavedPID;

uint8_t appParamCaliedFlag = 0;

static UploadParamType_e upload_type = REIMU;

uint8_t IsAppParamCalied(void)
{
	return appParamCaliedFlag;
}

uint8_t AppParamSave(void)
{
    return Flash_Write(CALI_FLASH_DATA_START_ADDRESS, (uint8_t*)&appParam, sizeof(AppParam_t));;
}

void AppParamInit(void)
{
    memcpy(&appParam, (void*)CALI_FLASH_DATA_START_ADDRESS, sizeof(AppParam_t));
    
    if ((CALI_FLAG_DONE == appParam.paramSavedFlag) &&\
		(CALI_FLAG_DONE == appParam.gimbalYawCaliData.flag) &&\
		(CALI_FLAG_DONE == appParam.gyroCaliData.flag))
	{
		appParamCaliedFlag =1;
    }
    else
    {
		appParamCaliedFlag = 0;
        appParam.firmwareVersion = 0; //
        appParam.paramSavedFlag = PARAM_SAVED_FLAG;
    }
    //if not calied before the flag is NONE the init the para with default value
    if(appParam.gimbalCaliData.flag != PARAM_CALI_DONE)
    {
        appParam.gimbalCaliData.flag = PARAM_CALI_NONE;
        appParam.gimbalCaliData.p_offset = 0;
        appParam.gimbalCaliData.y_offset = 0;
    }
    
    if(appParam.gyroCaliData.flag != PARAM_CALI_DONE)
    {
        appParam.gyroCaliData.flag = PARAM_CALI_NONE;
        appParam.gyroCaliData.x_offset = 0;
        appParam.gyroCaliData.y = 0;
        appParam.gyroCaliData.z_offset = 0;
    }
    
    if(appParam.accCaliData.flag != PARAM_CALI_DONE)
    {
        appParam.accCaliData.flag = PARAM_CALI_NONE;
        appParam.accCaliData.AccXOffset = 0;
        appParam.accCaliData.y_offset = 0;
        appParam.accCaliData.z_offset = 0;
        appParam.accCaliData.x_scale = 1.0;
        appParam.accCaliData.y_scale = 1.0;
        appParam.accCaliData.z_scale = 1.0;
    }
    
    if(appParam.magCaliData.flag != PARAM_CALI_DONE)
    {
        appParam.magCaliData.flag = PARAM_CALI_NONE;
        appParam.magCaliData.MagXOffset = 0;
        appParam.magCaliData.y = 0;
        appParam.magCaliData.z = 0;
        appParam.magCaliData.scaleX = 1.0;
        appParam.magCaliData.scaleY = 1.0;
        appParam.magCaliData.scaleZ = 1.0;
    }
}

void SetGimbalCaliData(GimbalCali_t *cali_data)
{
	if(cali_data != NULL)
    {
		memcpy(&appParam.gimbalCaliData, cali_data, sizeof(*cali_data));
		AppParamSave();
	}
}


void SetGyroCaliData(GyroCali_t *cali_data)
{
	if(cali_data != NULL)
    {
		memcpy(&appParam.gyroCaliData, cali_data, sizeof(*cali_data));
		AppParamSave();
	}
}  

void SetAccCaliData(AccCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(&appParam.accCaliData, cali_data, sizeof(*cali_data));
		AppParamSave();
    }
}

void SetMagCaliData(MagCali_t *cali_data)
{
    if(cali_data != NULL)
    {
		memcpy(&appParam.magCaliData, cali_data, sizeof(*cali_data));   //step1: copy data to struct
		AppParamSave();	
    }
	//step2:write data to the flash
}

//PID offset data saved in the memory 
void SetPIDCaliData(PIDCali_t *cali_data)
{
	if(cali_data != NULL)
    {
		if(cali_data->pid_type == PID_TYPE_POSITION && cali_data->device_id == MOTOR_TYPE_PITCH)
		{
			cali_data->kp_offset += appParam.pitchPositionPID.kp_offset;
			cali_data->ki_offset += appParam.pitchPositionPID.ki_offset;
			cali_data->kd_offset += appParam.pitchPositionPID.kd_offset;
			memcpy(&appParam.pitchPositionPID, cali_data, sizeof(*cali_data));
		}
		else if(cali_data->pid_type == PID_TYPE_SPEED && cali_data->device_id == MOTOR_TYPE_PITCH)
		{
			cali_data->kp_offset += appParam.pitchSpeedPID.kp_offset;
			cali_data->ki_offset += appParam.pitchSpeedPID.ki_offset;
			cali_data->kd_offset += appParam.pitchSpeedPID.kd_offset;
			memcpy(&appParam.pitchSpeedPID, cali_data, sizeof(*cali_data));
		}
		else if(cali_data->pid_type == PID_TYPE_POSITION && cali_data->device_id == MOTOR_TYPE_YAW)
		{
			cali_data->kp_offset += appParam.yawPositionPID.kp_offset;
			cali_data->ki_offset += appParam.yawPositionPID.ki_offset;
			cali_data->kd_offset += appParam.yawPositionPID.kd_offset;
			memcpy(&appParam.yawPositionPID, cali_data, sizeof(*cali_data));
		}
		else if(cali_data->pid_type == PID_TYPE_SPEED && cali_data->device_id == MOTOR_TYPE_YAW)
		{
			cali_data->kp_offset += appParam.yawSpeedPID.kp_offset;
			cali_data->ki_offset += appParam.yawSpeedPID.ki_offset;
			cali_data->kd_offset += appParam.yawSpeedPID.kd_offset;
			memcpy(&appParam.yawSpeedPID, cali_data, sizeof(*cali_data));
		}
		AppParamSave();	
	}
}

void GetGimbalCaliData(GimbalCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(cali_data, &appParam.gimbalCaliData, sizeof(GimbalCali_t));
    }
}

uint8_t GetGyroCaliData(GyroCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(cali_data, &appParam.gyroCaliData, sizeof(GyroCali_t));
    }
}

uint8_t GetAccCaliData(AccCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(cali_data, &appParam.accCaliData, sizeof(AccCali_t));
    }
}

uint8_t GetMagCaliData(MagCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(cali_data, &appParam.magCaliData, sizeof(MagCali_t));
    }
}

uint8_t IsGimbalCalied(void)
{
    return (appParam.gimbalCaliData.flag == PARAM_CALI_DONE);
}

uint8_t IsGyroCalied(void)
{
    return (appParam.gyroCaliData.flag == PARAM_CALI_DONE);
}

uint8_t IsAccCalied(void)
{
    return (appParam.accCaliData.flag == PARAM_CALI_DONE);
}

uint8_t IsMagCalied(void)
{
    return (appParam.magCaliData.flag == PARAM_CALI_DONE);
}

static uint32_t CaliCmdFlagGrp = 0;     //cali cmd flag group every bit represents a cali cmd received from the PC

void SetCaliCmdFlag(uint32_t flag)  //
{
	CaliCmdFlagGrp |= flag;
}

void ResetCaliCmdFlag(uint32_t flag)
{
	CaliCmdFlagGrp &= ~flag;
}

uint32_t GetCaliCmdFlagGrp()
{
	return CaliCmdFlagGrp;
}

//to check whether a specfic flag if set
uint8_t IsCaliCmdFlagSet(uint32_t flag)
{
	if(flag & CaliCmdFlagGrp)
	{
		return 1;
	}else
	{
		return 0;	
	}
}

void CalibrateLoop(void)
{
    CaliState_e cali_result;    
    //gyro cali 
    if(IsCaliCmdFlagSet(CALI_START_FLAG_GYRO))   //
	{
		ResetCaliCmdFlag(CALI_START_FLAG_GYRO);
	}
	else if(IsCaliCmdFlagSet(CALI_END_FLAG_GYRO))   //calibrate the 
    {
        cali_result = GyroCaliProcess();  
		if(cali_result == CALI_STATE_ERR)
		{
			
		}
		else if(cali_result == CALI_STATE_IN)
		{
			
		}
		else if(cali_result == CALI_STATE_DONE)
		{
			SetGyroCaliData(&GyroCaliData);   //set the apparamStruct using the GyroCaliData, and save apparamStruct to the flash 
			Sensor_Offset_Param_Init(&appParam);   //update the parameter
			ResetCaliCmdFlag(CALI_END_FLAG_GYRO);		//reset the cali cmd
		}
    }
	else if(IsCaliCmdFlagSet(CALI_START_FLAG_GIMBAL))   //calibrate the 
	{
		ResetCaliCmdFlag(CALI_START_FLAG_GIMBAL);
	}
	else if(IsCaliCmdFlagSet(CALI_END_FLAG_GIMBAL))
	{
	    cali_result = GimbalCaliProcess();  
		if(cali_result == CALI_STATE_ERR)
		{
			
		}
		else if(cali_result == CALI_STATE_IN)
		{
			
		}
		else if(cali_result == CALI_STATE_DONE)
		{
			SetGimbalCaliData(&GimbalCaliData);           //set the apparamStruct using the GyroCaliData, and save apparamStruct to the flash 
			Sensor_Offset_Param_Init(&appParam);   //update the parameter
			ResetCaliCmdFlag(CALI_END_FLAG_GIMBAL);
		}	
	}
	else if(IsCaliCmdFlagSet(CALI_START_FLAG_MAG))
	{
		cali_result = MagStartCaliProcess();   //reset the max min data of the magenemter
		if(cali_result == CALI_STATE_ERR)
		{
			
		}
		else if(cali_result == CALI_STATE_IN)
		{
			
		}
		else if(cali_result == CALI_STATE_DONE)
		{			
			ResetCaliCmdFlag(CALI_START_FLAG_MAG);
		}	
	}
	else if(IsCaliCmdFlagSet(CALI_END_FLAG_MAG))
	{
		cali_result = MagEndCaliProcess();  
		if(cali_result == CALI_STATE_ERR)
		{
			
		}
		else if(cali_result == CALI_STATE_IN)
		{
			
		}
		else if(cali_result == CALI_STATE_DONE)
		{
			SetMagCaliData(&MagCaliData);                 //set the apparamStruct using the GyroCaliData, and save apparamStruct to the flash 
			Sensor_Offset_Param_Init(&appParam);   //update the parameter
			ResetCaliCmdFlag(CALI_END_FLAG_MAG);
		}		
	}
	else if(IsCaliCmdFlagSet(CALI_FLAG_PID))
	{
		SetPIDCaliData(&PIDCaliData);                 //
		Sensor_Offset_Param_Init(&appParam);   //update the parameter
		ResetCaliCmdFlag(CALI_FLAG_PID);
	}
}



CaliState_e  GimbalCaliProcess()     // ERROR DONE
{
	static uint32_t loopCount = 0;
	static uint32_t loopTime = 10;
	static int32_t pitchSum = 0;
	static int32_t yawSum = 0;
	
	/*
	if(Is_Lost_Error_Set(LOST_ERROR_MOTOR5) || Is_Lost_Error_Set(LOST_ERROR_MOTOR6))
	{
		return CALI_STATE_ERR;
	}
	*/
	if(Is_Lost_Error_Set(LOST_ERROR_MOTOR6))
	{
		return CALI_STATE_ERR;
	}
	else if(loopCount++<loopTime)   //in cali state
	{
		pitchSum += GMPitchEncoder.raw_value;
		yawSum += GMYawEncoder.raw_value;
		return CALI_STATE_IN;
	}
	else
	{		
		GimbalCaliData.p_offset = pitchSum/loopTime;   //
	    GimbalCaliData.y_offset = yawSum/loopTime;		//
		GimbalCaliData.flag = PARAM_CALI_DONE;
		pitchSum = 0;
		yawSum = 0;
		loopCount = 0;
		return CALI_STATE_DONE;
	}	
}

CaliState_e  GyroCaliProcess()     
{
	int16_t temp[6] = {0};
	static uint16_t loopCount = 0;
	static uint16_t loopTime = 20;
	static int32_t gyroXSum = 0;
	static int32_t gyroYSum = 0;
	static int32_t gyroZSum = 0;
	GyroSavedCaliData.GyroXOffset = 0;
	GyroSavedCaliData.y = 0;
	GyroSavedCaliData.z_offset = 0;	
	//process of the cali if error return error, elseif in processing return in , and if done return done
	if(Is_Lost_Error_Set(LOST_ERROR_IMU))    //
	{
		return CALI_STATE_ERR;
	}
	else if(loopCount++<loopTime)   //in cali state
	{
		MPU6050_getMotion6(&temp[0],&temp[1],&temp[2],&temp[3],&temp[4],&temp[5]);
		gyroXSum += temp[3];
		gyroYSum += temp[4];
		gyroZSum += temp[5];
		return CALI_STATE_IN;
	}
	else
	{					
		GyroCaliData.GyroXOffset = gyroXSum/loopTime;   //
	    GyroCaliData.y = gyroYSum/loopTime;		//
		GyroCaliData.z_offset = gyroZSum/loopTime;		//
		GyroCaliData.flag = PARAM_CALI_DONE;
		gyroXSum = 0;
		gyroYSum = 0;
		gyroZSum = 0;
		loopCount = 0;
		return CALI_STATE_DONE;
	}
}

CaliState_e  MagStartCaliProcess()
{	
	MagMaxMinData.MaxMagX = -4096;	//
	MagMaxMinData.MaxMagY = -4096;
	MagMaxMinData.MaxMagZ = -4096;
	MagMaxMinData.MinMagX = 4096;
	MagMaxMinData.MinMagY = 4096;
	MagMaxMinData.MinMagZ = 4096;
	return CALI_STATE_DONE;	
}
CaliState_e  MagEndCaliProcess()
{
	if(Is_Lost_Error_Set(LOST_ERROR_IMU))    
	{
		return CALI_STATE_ERR;
	}
	else
	{
		MagCaliData.MagXOffset = (MagMaxMinData.MaxMagX + MagMaxMinData.MinMagX)/2;
		MagCaliData.y = (MagMaxMinData.MaxMagY + MagMaxMinData.MinMagY)/2;
		MagCaliData.z = (MagMaxMinData.MaxMagZ + MagMaxMinData.MinMagZ)/2;
		MagCaliData.scaleX = 1.0;
		MagCaliData.scaleY = 1.0;
		MagCaliData.scaleZ = 1.0;	
		MagCaliData.flag = PARAM_CALI_DONE;
		return CALI_STATE_DONE;		
	}	
}

//copy src pid offset data received from the PC to the static PitchPostionCaliData/PitchSpeedCaliData
CaliState_e PIDCaliProcess(PIDCali_t *cali_data)
{
	if(cali_data!=NULL)
	{
		memcpy(&PIDCaliData, cali_data, sizeof(*cali_data));
		return CALI_STATE_DONE;
	}	
    return CALI_STATE_DONE;
}

void Sensor_Offset_Param_Init(AppParam_t *appParam)
{
	memcpy(&MagSavedCaliData, &(appParam->magCaliData), sizeof((appParam->magCaliData)));
	memcpy(&GyroSavedCaliData, &(appParam->gyroCaliData), sizeof((appParam->gyroCaliData)));
	memcpy(&GimbalSavedCaliData, &(appParam->gimbalCaliData), sizeof((appParam->gimbalCaliData)));
	
	memcpy(&PitchPositionSavedPID, &(appParam->pitchPositionPID), sizeof((appParam->pitchPositionPID)));
	memcpy(&PitchSpeedSavedPID, &(appParam->pitchSpeedPID), sizeof((appParam->pitchSpeedPID)));
	memcpy(&YawPositionSavedPID, &(appParam->yawPositionPID), sizeof((appParam->yawPositionPID)));
	memcpy(&YawSpeedSavedPID, &(appParam->yawSpeedPID), sizeof((appParam->yawSpeedPID)));

	GMPitchEncoder.ecd_bias = appParam.gimbalCaliData.p_offset;
	GMYawEncoder.ecd_bias = appParam.gimbalCaliData.y_offset;
}

void UploadParameter(void)
{				
    static int16_t ax, ay, az, gx, gy, gz, hx, hy, hz;    
    switch(upload_type) 
    {
        case REIMU:				
        {
            //GMPitchEncoder_ecder						
            IMU_Info_Send((int16_t)(angle[0]*10.0f),(int16_t)(angle[1]*10.0f),(int16_t)(angle[2]*10.0f),(int16_t)GMYawEncoder.raw_value,(int16_t)GMPitchEncoder.raw_value, 0);
            upload_type = REVERSION; //
        }	break;
        case REVERSION:
        {
            Version_Send(VERSION);   //				
            upload_type = REPID; //
        }break;
        case REPID:
        {						
            PID_Paremeter_Send(GMPPositionPID.kp, GMPPositionPID.ki,GMPPositionPID.kd, GMPSpeedPID.kp,GMPSpeedPID.ki,GMPSpeedPID.kd,GMYPositionPID.kp,GMYPositionPID.ki,GMYPositionPID.kd,GMYSpeedPID.kp,GMYSpeedPID.ki,GMYSpeedPID.kd);
            upload_type = REERROR;
        }break;
        case REERROR:
        {
            Robot_Error_Code_Send(Get_Lost_Error(LOST_ERROR_ALL));
            upload_type = REMOV;
        }break;
        case REMOV:
        {
            MPU6050_getlastMotion6(&ax, &ay, &az, &gx, &gy, &gz);   //
            HMC58X3_getlastValues(&hx, &hy, &hz);											
            Sensor_Info_Send(ax, ay, az, gx, gy, gz, hx, hy, hz);
            upload_type = REHMC; //
        }break;
        case REHMC:
        {
            Mag_Cali_Info_Send(MagMaxMinData.MaxMagX,MagMaxMinData.MaxMagY,MagMaxMinData.MaxMagZ,MagMaxMinData.MinMagX,MagMaxMinData.MinMagY,MagMaxMinData.MinMagZ);
            upload_type = REOFFSET;
        }break;					
        case REOFFSET:         //
        {
            Offset_Info_Send(IsAppParamCalied(), appParam.gyroCaliData.GyroXOffset, appParam.gyroCaliData.y, appParam.gyroCaliData.z_offset, \
            appParam.magCaliData.MagXOffset, appParam.magCaliData.y, appParam.magCaliData.z, \
            appParam.gimbalCaliData.y_offset, appParam.gimbalCaliData.p_offset);
            upload_type = REIMU;          //config
        }break;
        default:
        {						
        }break;
    }

}
