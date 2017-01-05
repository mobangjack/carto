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
 
#include "motor.h"

#define PI 3.1415926f
#define GAP 7500
void Ecd_Proc(Ecd_t* ecd, uint8_t* data)
{
	ecd->angle_fdb[0] = ecd->angle_fdb[1];
	ecd->angle_fdb[1] = (data[0] << 8) | data[1];
	if (!ecd->ini_flag) {
		ecd->bias = ecd->angle_fdb[1];
		ecd->angle_coeff = MOTOR_ECD_ANGLE_COEFF;
		ecd->speed_coeff = MOTOR_ECD_SPEED_COEFF;
		ecd->ini_flag = 1;
	}
	ecd->dif = ecd->angle_fdb[1] - ecd->angle_fdb[0];
	if (ecd->dif > GAP) {
		ecd->rnd--;
		ecd->speed_fdb = ecd->dif - MOTOR_ECD_ANGLE_FDB_MOD;
	} else if (ecd->dif < -GAP) {
		ecd->rnd++;
		ecd->speed_fdb = ecd->dif + MOTOR_ECD_ANGLE_FDB_MOD;
	} else {
		ecd->speed_fdb = ecd->dif;
	}
	ecd->angle = (ecd->angle_fdb[1] - ecd->bias) * ecd->angle_coeff + ecd->rnd * 2 * PI;
	ecd->speed = ecd->speed_fdb * ecd->speed_coeff;
}

void Ecd_Reset(Ecd_t* ecd)
{
	memset(ecd, 0, sizeof(Ecd_t));
}

void Esc_Proc(Esc_t* esc, uint8_t* data)
{
	esc->current_fdb = (data[0] << 8) | data[1];
	esc->current_ref = (data[2] << 8) | data[3];
}

void Motor_Proc(Motor_t* motor, uint8_t* data)
{
	Ecd_Proc(&motor->ecd, data);
	Esc_Proc(&motor->esc, data + 2);
}

void EC60_Cmd(CAN_TypeDef *CANx, int16_t c201, int16_t c202, int16_t c203, int16_t c204)
{
	CanTxMsg canTxMsg;
    canTxMsg.StdId = CHASSIS_MOTOR_CMD_CAN_MSG_ID;
    canTxMsg.IDE = CAN_Id_Standard;
    canTxMsg.RTR = CAN_RTR_Data;
    canTxMsg.DLC = 0x08;
    
    canTxMsg.Data[0] = (uint8_t)(c201 >> 8);
    canTxMsg.Data[1] = (uint8_t)c201;
    canTxMsg.Data[2] = (uint8_t)(c202 >> 8);
    canTxMsg.Data[3] = (uint8_t)c202;
    canTxMsg.Data[4] = (uint8_t)(c203 >> 8);
    canTxMsg.Data[5] = (uint8_t)c203;
    canTxMsg.Data[6] = (uint8_t)(c204 >> 8);
    canTxMsg.Data[7] = (uint8_t)c204;
    CAN_Transmit(CANx,&canTxMsg);
}

void RM6025_Cmd(CAN_TypeDef *CANx, int16_t c205, int16_t c206)
{
	CanTxMsg canTxMsg;
    canTxMsg.StdId = PANTILT_MOTOR_CMD_CAN_MSG_ID;
    canTxMsg.IDE = CAN_Id_Standard;
    canTxMsg.RTR = CAN_RTR_Data;
    canTxMsg.DLC = 0x08;
    
    canTxMsg.Data[0] = (uint8_t)(c205 >> 8);
    canTxMsg.Data[1] = (uint8_t)c205;
    canTxMsg.Data[2] = (uint8_t)(c206 >> 8);
    canTxMsg.Data[3] = (uint8_t)c206;
    canTxMsg.Data[4] = (uint8_t)0x00;
    canTxMsg.Data[5] = (uint8_t)0x00;
    canTxMsg.Data[6] = (uint8_t)0x00;
    canTxMsg.Data[7] = (uint8_t)0x00;
    CAN_Transmit(CANx,&canTxMsg);
}
