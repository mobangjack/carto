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
 
#include "can2.h"

void CAN2_Config(void)
{
    GPIO_AF(CAN2_RX_PIN, GPIO_AF_CAN2);
    GPIO_AF(CAN2_TX_PIN, GPIO_AF_CAN2);

    NVIC_Config(CAN2_RX0_IRQn, 1, 1);
    NVIC_Config(CAN2_TX_IRQn, 0, 1);

    //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Config(CAN2, 3, 0, CAN_SJW_1tq, CAN_BS1_9tq, CAN_BS2_4tq);

    CAN_Filter_Config(0x0000, 0x0000, 0x0000, 0x0000, 0, 14);
    
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE);
}

void CAN2_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET)
	{
	   CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
	}
}

void CAN2_RX0_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)
    {
    	CanRxMsg canRxMsg;
        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
        CAN_Receive(CAN2, CAN_FIFO0, &canRxMsg);

        CAN2_RX_Callback(&canRxMsg);
    }
}


