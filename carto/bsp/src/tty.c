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
 
#include "tty.h"

FIFO_t* fifo = NULL;

void Tty_Config(void)
{
    USART_Bind(TTY_RX_PIN, TTY_TX_PIN,
    		   TTY_USART,
			   TTY_USART_BR,
			   TTY_USART_WL,
			   TTY_USART_PR,
			   TTY_USART_SB,
			   TTY_USART_FC
			   );

    USART_ITConfig(TTY_USART, USART_IT_RXNE, ENABLE);

    NVIC_Config(TTY_NVIC, TTY_NVIC_PRE_PRIORITY, TTY_NVIC_SUB_PRIORITY);

    if (fifo == NULL) {
    	fifo = FIFO_Create(TTY_TX_FIFO_SIZE);
    } else {
    	FIFO_Flush(fifo);
    }

    USART_Cmd(TTY_USART, ENABLE);
}

void Tty_WriteByte(u8 byte)
{    
    FIFO_Push(fifo, byte);
    USART_ITConfig(TTY_USART, USART_IT_TXE, ENABLE);
}

void Tty_Write(u8* pdata, u8 len)
{
	uint8_t i = 0;
	for (; i < len; i++) {
		FIFO_Push(fifo, pdata[i]);
	}
    USART_ITConfig(TTY_USART, USART_IT_TXE, ENABLE);
}

int fputc(int ch, FILE *f)
{
    while (USART_GetFlagStatus(TTY_USART,USART_FLAG_TC) == RESET);
    USART_SendData(TTY_USART, (uint8_t)ch);
    return ch;
}

void TTY_IRQ_HANDLER()
{  
    if (USART_GetITStatus(TTY_USART, USART_IT_TXE) != RESET)
    {   
		while (!FIFO_IsEmpty(fifo))
		{
			uint8_t tx_data = FIFO_Pop(fifo);
			while (USART_GetFlagStatus(TTY_USART,USART_FLAG_TC) == RESET);
			USART_SendData(TTY_USART, tx_data);
		}
		USART_ITConfig(TTY_USART, USART_IT_TXE, DISABLE);
    }
	else if (USART_GetITStatus(TTY_USART, USART_IT_RXNE) != RESET)
    {
        uint8_t rx_data = USART_ReceiveData(TTY_USART);
        TtyRxCallback(rx_data);
    }       
}

