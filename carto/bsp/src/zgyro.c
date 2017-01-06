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
 
#include "zgyro.h"

void ZGyro_RST(CAN_TypeDef* CANx)
{
	CanTxMsg canTxMsg;
    
    canTxMsg.StdId = ZGYRO_CMD_CAN_MSG_ID;
    canTxMsg.IDE = CAN_Id_Standard;
    canTxMsg.RTR = CAN_RTR_Data;
    canTxMsg.DLC = 0x08;
    
    canTxMsg.Data[0] = 0x00;
    canTxMsg.Data[1] = 0x01;
    canTxMsg.Data[2] = 0x02;
    canTxMsg.Data[3] = 0x03;
    canTxMsg.Data[4] = 0x04;
    canTxMsg.Data[5] = 0x05;
    canTxMsg.Data[6] = 0x06;
    canTxMsg.Data[7] = 0x07;
	
	CAN_Transmit(CANx, &canTxMsg);
}
