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

uint8_t buf[TTY_TX_FIFO_SIZE];
FIFO_t fifo;

void Tty_Config()
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

    FIFO_Init(&fifo, buf, TTY_TX_FIFO_SIZE);

    USART_Cmd(TTY_USART, ENABLE);
}

void Tty_WriteByte(uint8_t byte)
{
	if (FIFO_NotFull(&fifo)) {
		FIFO_Push(&fifo, byte);
	}
    USART_ITConfig(TTY_USART, USART_IT_TXE, ENABLE);
}

void Tty_Write(const uint8_t* pdata, uint8_t len)
{
	uint8_t i = 0;
	for (; i < len; i++) {
		if (FIFO_NotFull(&fifo)) {
			FIFO_Push(&fifo, pdata[i]);
		} else {
			break;
		}
	}
    USART_ITConfig(TTY_USART, USART_IT_TXE, ENABLE);
}

char tx_buf[TTY_TX_FIFO_SIZE];
void Tty_Print(const char* fmt,...)
{
	uint32_t i = 0;
	uint32_t len = sprintf(tx_buf, fmt);
	for (; i < len; i++) {
		if (FIFO_NotFull(&fifo)) {
			FIFO_Push(&fifo, tx_buf[i]);
		} else {
			break;
		}
	}
	USART_ITConfig(TTY_USART, USART_IT_TXE, ENABLE);
}

int fputc(int c, FILE *f)
{
	Tty_WriteByte((u8)c);
    return c;
}

void TTY_IRQ_HANDLER()
{  
    if (USART_GetITStatus(TTY_USART, USART_IT_TXE) != RESET)
    {   
		while (FIFO_NotEmpty(&fifo))
		{
			uint8_t tx_data = FIFO_Pop(&fifo);
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

