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
 
#include "receiver.h"

uint8_t buf[2][RC_DMA_BUF_SIZE];

void Recv_Config(void)
{
	USART_Bind(RC_SIGNAL_PIN,  0, RC_USART, RC_BR, RC_WL, RC_PR, RC_SB, RC_FC);

    USART_DMACmd(RC_USART, USART_DMAReq_Rx, ENABLE);
    
    DMA_Config(RC_DMA_STREAM, RC_DMA_CHANNEL,(u32)&RC_USART->DR, (u32)buf[0], 0, RC_DMA_BUF_SIZE);

    DMA_DoubleBufferModeConfig(RC_DMA_STREAM, (u32)&buf[1][0], DMA_Memory_0);   //first used memory configuration
    DMA_DoubleBufferModeCmd(RC_DMA_STREAM, ENABLE);
    
    DMA_Cmd(RC_DMA_STREAM, ENABLE);
    
    NVIC_Config(RC_NVIC, RC_NVIC_PRE_PRIORITY, RC_NVIC_SUB_PRIORITY);
    
	USART_ITConfig(RC_USART, USART_IT_IDLE, ENABLE); // 14mspf
    USART_Cmd(RC_USART, ENABLE);

}

void RC_IRQ_HANDLER()
{
	if(USART_GetITStatus(RC_USART, USART_IT_IDLE) != RESET)
	{
		uint8_t* dbuf = buf[0];

		uint16_t rx_len = 0;

		//clear the idle pending flag 
		(void)RC_USART->SR;
		(void)RC_USART->DR;

		DMA_Cmd(RC_DMA_STREAM, DISABLE);
		rx_len = RC_DMA_BUF_SIZE - DMA_GetCurrDataCounter(RC_DMA_STREAM);
		RC_DMA_STREAM->NDTR = (uint16_t)RC_DMA_BUF_SIZE;     //relocate the DMA memory pointer to the beginning position
		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(RC_DMA_STREAM) == 0)
		{
			dbuf = buf[0];
			RC_DMA_STREAM->CR |= (uint32_t)(DMA_SxCR_CT);        //enable the current selected memory is Memory 1
		}
		else
		{
			dbuf = buf[1];
			RC_DMA_STREAM->CR &= ~(uint32_t)(DMA_SxCR_CT);       //enable the current selected memory is Memory 0
		}
		DMA_Cmd(RC_DMA_STREAM, ENABLE);
		if(rx_len == RC_FRAME_LEN)
		{
			RC_Callback(dbuf);
		}
	}       
}

