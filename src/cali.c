#include "main.h"
//#include "protocal.h"

AppParam_t gAppParamStruct;	//
static GyroCali_t GyroCaliData;
static GimbalCali_t  GimbalCaliData;
static MagCali_t  MagCaliData;
PIDCali_t PIDCaliData;
//
GimbalCali_t GimbalSavedCaliData;    	    //gimbal pitch yaw encoder offset
GyroCali_t GyroSavedCaliData;     	    //gyro offset data
AccCali_t AccSavedCaliData;    	    	//ACC offset data
MagCali_t MagSavedCaliData;			    //Mag offset data
PIDCali_t PitchPositionSavedPID;        	//PID offset data
PIDCali_t PitchSpeedSavedPID;        	//PID offset data
PIDCali_t YawPositionSavedPID;        	//PID offset data
PIDCali_t YawSpeedSavedPID;        	    //PID offset data

uint8_t app_param_calied_flag = 0;

static UploadParamType_e upload_type = REIMU;  //

//SuperviseTask
uint8_t Is_AppParam_Calied(void)
{
	return app_param_calied_flag;    //param
}

//Save params to flash
static uint8_t AppParamSave(void)
{
    uint8_t retval = 1;   
    retval = Flash_Write(CALI_FLASH_DATA_START_ADDRESS, (uint8_t *)&gAppParamStruct, sizeof(AppParam_t));
    if(retval == 0)
    {
			
    }
    return retval;   
}

//
void AppParamInit(void)
{
    AppParam_t tmp_param;
    
    memcpy(&tmp_param, (void *)CALI_FLASH_DATA_START_ADDRESS, sizeof(AppParam_t));
    
    if((PARAM_SAVED_FLAG == tmp_param.ParamSavedFlag) &&\
		(PARAM_CALI_DONE == tmp_param.GimbalCaliData.flag) &&\
		(PARAM_CALI_DONE == tmp_param.GyroCaliData.flag))
	{
		app_param_calied_flag =1;
        memcpy(&gAppParamStruct, &tmp_param, sizeof(AppParam_t));
    }
    else
    {
		app_param_calied_flag = 0;
        gAppParamStruct.FirmwareVersion = 0; //
        gAppParamStruct.ParamSavedFlag = PARAM_SAVED_FLAG;
    }
    //if not calied before the flag is NONE the init the para with default value
    if(gAppParamStruct.GimbalCaliData.flag != PARAM_CALI_DONE)
    {
        gAppParamStruct.GimbalCaliData.flag = PARAM_CALI_NONE;
        gAppParamStruct.GimbalCaliData.pitch = 0;
        gAppParamStruct.GimbalCaliData.yaw = 0;
    }
    
    if(gAppParamStruct.GyroCaliData.flag != PARAM_CALI_DONE)
    {
        gAppParamStruct.GyroCaliData.flag = PARAM_CALI_NONE;
        gAppParamStruct.GyroCaliData.GyroXOffset = 0;
        gAppParamStruct.GyroCaliData.y = 0;
        gAppParamStruct.GyroCaliData.z = 0;
    }
    
    if(gAppParamStruct.AccCaliData.flag != PARAM_CALI_DONE)
    {
        gAppParamStruct.AccCaliData.flag = PARAM_CALI_NONE;
        gAppParamStruct.AccCaliData.AccXOffset = 0;
        gAppParamStruct.AccCaliData.y = 0;
        gAppParamStruct.AccCaliData.z = 0;
        gAppParamStruct.AccCaliData.scaleX = 1.0;
        gAppParamStruct.AccCaliData.scaleY = 1.0;
        gAppParamStruct.AccCaliData.scaleZ = 1.0;
    }
    
    if(gAppParamStruct.MagCaliData.flag != PARAM_CALI_DONE)
    {
        gAppParamStruct.MagCaliData.flag = PARAM_CALI_NONE;
        gAppParamStruct.MagCaliData.MagXOffset = 0;
        gAppParamStruct.MagCaliData.y = 0;
        gAppParamStruct.MagCaliData.z = 0;
        gAppParamStruct.MagCaliData.scaleX = 1.0;
        gAppParamStruct.MagCaliData.scaleY = 1.0;
        gAppParamStruct.MagCaliData.scaleZ = 1.0;
    }
}

void SetGimbalCaliData(GimbalCali_t *cali_data)
{
	if(cali_data != NULL)
    {
		memcpy(&gAppParamStruct.GimbalCaliData, cali_data, sizeof(*cali_data));
		AppParamSave();
	}
}


void SetGyroCaliData(GyroCali_t *cali_data)
{
	if(cali_data != NULL)
    {
		memcpy(&gAppParamStruct.GyroCaliData, cali_data, sizeof(*cali_data));
		AppParamSave();
	}
}  

void SetAccCaliData(AccCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(&gAppParamStruct.AccCaliData, cali_data, sizeof(*cali_data));
		AppParamSave();
    }
}

void SetMagCaliData(MagCali_t *cali_data)
{
    if(cali_data != NULL)
    {
		memcpy(&gAppParamStruct.MagCaliData, cali_data, sizeof(*cali_data));   //step1: copy data to struct
		AppParamSave();	
    }
																														 //step2:write data to the flash
}

//PID offset data saved in the memory 
void SetPIDCaliData(PIDCali_t *cali_data)
{
	if(cali_data != NULL)
    {
		if(cali_data->pid_type == PID_TYPE_POSITION && cali_data->motor_type == MOTOR_TYPE_PITCH)
		{
			cali_data->kp_offset += gAppParamStruct.PitchPositionPID.kp_offset;
			cali_data->ki_offset += gAppParamStruct.PitchPositionPID.ki_offset;
			cali_data->kd_offset += gAppParamStruct.PitchPositionPID.kd_offset;			
			memcpy(&gAppParamStruct.PitchPositionPID, cali_data, sizeof(*cali_data));
		}
		else if(cali_data->pid_type == PID_TYPE_SPEED && cali_data->motor_type == MOTOR_TYPE_PITCH)
		{
			cali_data->kp_offset += gAppParamStruct.PitchSpeedPID.kp_offset;
			cali_data->ki_offset += gAppParamStruct.PitchSpeedPID.ki_offset;
			cali_data->kd_offset += gAppParamStruct.PitchSpeedPID.kd_offset;	
			memcpy(&gAppParamStruct.PitchSpeedPID, cali_data, sizeof(*cali_data));
		}
		else if(cali_data->pid_type == PID_TYPE_POSITION && cali_data->motor_type == MOTOR_TYPE_YAW)
		{
			cali_data->kp_offset += gAppParamStruct.YawPositionPID.kp_offset;
			cali_data->ki_offset += gAppParamStruct.YawPositionPID.ki_offset;
			cali_data->kd_offset += gAppParamStruct.YawPositionPID.kd_offset;	
			memcpy(&gAppParamStruct.YawPositionPID, cali_data, sizeof(*cali_data));
		}
		else if(cali_data->pid_type == PID_TYPE_SPEED && cali_data->motor_type == MOTOR_TYPE_YAW)
		{
			cali_data->kp_offset += gAppParamStruct.YawSpeedPID.kp_offset;
			cali_data->ki_offset += gAppParamStruct.YawSpeedPID.ki_offset;
			cali_data->kd_offset += gAppParamStruct.YawSpeedPID.kd_offset;	
			memcpy(&gAppParamStruct.YawSpeedPID, cali_data, sizeof(*cali_data));
		}
		AppParamSave();	
	}
}

void GetGimbalCaliData(GimbalCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(cali_data, &gAppParamStruct.GimbalCaliData, sizeof(GimbalCali_t));
    }
}

void GetGyroCaliData(GyroCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(cali_data, &gAppParamStruct.GyroCaliData, sizeof(GyroCali_t));
    }
}

void GetAccCaliData(AccCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(cali_data, &gAppParamStruct.AccCaliData, sizeof(AccCali_t));
    }
}

void GetMagCaliData(MagCali_t *cali_data)
{
    if(cali_data != NULL)
    {
        memcpy(cali_data, &gAppParamStruct.MagCaliData, sizeof(MagCali_t));
    }
}

uint8_t IsGimbalCalied(void)
{
    return (gAppParamStruct.GimbalCaliData.flag == PARAM_CALI_DONE);
}

uint8_t IsGyroCalied(void)
{
    return (gAppParamStruct.GyroCaliData.flag == PARAM_CALI_DONE);
}

uint8_t IsAccCalied(void)
{
    return (gAppParamStruct.AccCaliData.flag == PARAM_CALI_DONE);
}

uint8_t IsMagCalied(void)
{
    return (gAppParamStruct.MagCaliData.flag == PARAM_CALI_DONE);
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
    CALI_STATE_e cali_result;    
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
			Sensor_Offset_Param_Init(&gAppParamStruct);   //update the parameter
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
			Sensor_Offset_Param_Init(&gAppParamStruct);   //update the parameter
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
			Sensor_Offset_Param_Init(&gAppParamStruct);   //update the parameter
			ResetCaliCmdFlag(CALI_END_FLAG_MAG);
		}		
	}
	else if(IsCaliCmdFlagSet(CALI_FLAG_PID))
	{
		SetPIDCaliData(&PIDCaliData);                 //
		Sensor_Offset_Param_Init(&gAppParamStruct);   //update the parameter
		ResetCaliCmdFlag(CALI_FLAG_PID);
	}
}



CALI_STATE_e  GimbalCaliProcess()     // ERROR DONE
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
		GimbalCaliData.pitch = pitchSum/loopTime;   //
	    GimbalCaliData.yaw = yawSum/loopTime;		//
		GimbalCaliData.flag = PARAM_CALI_DONE;
		pitchSum = 0;
		yawSum = 0;
		loopCount = 0;
		return CALI_STATE_DONE;
	}	
}

CALI_STATE_e  GyroCaliProcess()     
{
	int16_t temp[6] = {0};
	static uint16_t loopCount = 0;
	static uint16_t loopTime = 20;
	static int32_t gyroXSum = 0;
	static int32_t gyroYSum = 0;
	static int32_t gyroZSum = 0;
	GyroSavedCaliData.GyroXOffset = 0;
	GyroSavedCaliData.y = 0;
	GyroSavedCaliData.z = 0;	
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
		GyroCaliData.z = gyroZSum/loopTime;		//
		GyroCaliData.flag = PARAM_CALI_DONE;
		gyroXSum = 0;
		gyroYSum = 0;
		gyroZSum = 0;
		loopCount = 0;
		return CALI_STATE_DONE;
	}
}

CALI_STATE_e  MagStartCaliProcess()
{	
	MagMaxMinData.MaxMagX = -4096;	//
	MagMaxMinData.MaxMagY = -4096;
	MagMaxMinData.MaxMagZ = -4096;
	MagMaxMinData.MinMagX = 4096;
	MagMaxMinData.MinMagY = 4096;
	MagMaxMinData.MinMagZ = 4096;
	return CALI_STATE_DONE;	
}
CALI_STATE_e  MagEndCaliProcess()
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
CALI_STATE_e PIDCaliProcess(PIDCali_t *cali_data)
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
	memcpy(&MagSavedCaliData, &(appParam->MagCaliData), sizeof((appParam->MagCaliData)));
	memcpy(&GyroSavedCaliData, &(appParam->GyroCaliData), sizeof((appParam->GyroCaliData)));
	memcpy(&GimbalSavedCaliData, &(appParam->GimbalCaliData), sizeof((appParam->GimbalCaliData)));
	
	memcpy(&PitchPositionSavedPID, &(appParam->PitchPositionPID), sizeof((appParam->PitchPositionPID)));
	memcpy(&PitchSpeedSavedPID, &(appParam->PitchSpeedPID), sizeof((appParam->PitchSpeedPID)));
	memcpy(&YawPositionSavedPID, &(appParam->YawPositionPID), sizeof((appParam->YawPositionPID)));
	memcpy(&YawSpeedSavedPID, &(appParam->YawSpeedPID), sizeof((appParam->YawSpeedPID)));

	GMPitchEncoder.ecd_bias = gAppParamStruct.GimbalCaliData.pitch;
	GMYawEncoder.ecd_bias = gAppParamStruct.GimbalCaliData.yaw;	
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
            Offset_Info_Send(Is_AppParam_Calied(), gAppParamStruct.GyroCaliData.GyroXOffset, gAppParamStruct.GyroCaliData.y, gAppParamStruct.GyroCaliData.z, \
            gAppParamStruct.MagCaliData.MagXOffset, gAppParamStruct.MagCaliData.y, gAppParamStruct.MagCaliData.z, \
            gAppParamStruct.GimbalCaliData.yaw, gAppParamStruct.GimbalCaliData.pitch);     						
            upload_type = REIMU;          //config
        }break;
        default:
        {						
        }break;
    }

}
