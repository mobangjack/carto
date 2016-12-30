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
 
#include "com.h"

FIFO_t* fifo = NULL;

void COM_Config(void)
{
    GPIO_AF(COM_TX_PIN, COM_GPIO_AF);
    GPIO_AF(COM_RX_PIN, COM_GPIO_AF);

    USART_Config(COM_USART, ' ', 115200, 8, 'n', 1, ' ');

    USART_ITConfig(COM_USART,USART_IT_RXNE, ENABLE);

    USART_Cmd(COM_USART, ENABLE);

    NVIC_Config(COM_NVIC, 1, 0);

	fifo = FIFO_Create(COM_TX_FIFO_SIZE);
}


void COM_WriteByte(uint8_t byte)
{    
    FIFO_Push(fifo, byte);
    USART_ITConfig(COM_USART, USART_IT_TXE, ENABLE);
}

void COM_Write(uint8_t* pdata, uint8_t len)
{
	uint8_t i = 0;
	for (; i < len; i++) {
		FIFO_Push(fifo, pdata[i]);
	}
    USART_ITConfig(COM_USART, USART_IT_TXE, ENABLE);
}

int fputc(int ch, FILE *f)
{
    while (USART_GetFlagStatus(COM_USART,USART_FLAG_TC) == RESET);
    USART_SendData(COM_USART, (uint8_t)ch);
    return ch;
}

void COM_IRQ_HANDLER()
{  
    if (USART_GetITStatus(COM_USART, USART_IT_TXE) != RESET)
    {   
		while (!FIFO_IsEmpty(fifo))
		{
			uint8_t tx_data = FIFO_Pop(fifo);
			while (USART_GetFlagStatus(COM_USART,USART_FLAG_TC) == RESET);
			USART_SendData(COM_USART, tx_data);
		}
		USART_ITConfig(COM_USART, USART_IT_TXE, DISABLE);
    }
	else if (USART_GetITStatus(COM_USART, USART_IT_RXNE) != RESET)
    {
        uint8_t rx_data = USART_ReceiveData(COM_USART);
		COM_Callback(rx_data);
    }       
}

