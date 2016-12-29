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

#include "mpu6050_i2c.h"

void MPU6050_IIC_Delay(uint32_t t)
{
	int i = 0;
	for (; i < t; i++)
	{
		int a = 6;
		while (a--);
	}
}

void MPU6050_IIC_Start(void)								  
{
	MPU6050_IIC_SDA_OUT();
	MPU6050_IIC_SDA_H();
	MPU6050_IIC_SCL_H();
	MPU6050_IIC_Delay(1);
	MPU6050_IIC_SDA_L();
	MPU6050_IIC_Delay(1);
	MPU6050_IIC_SCL_L();
}

void MPU6050_IIC_Stop(void)
{
	MPU6050_IIC_SDA_OUT();
	MPU6050_IIC_SCL_L();
	MPU6050_IIC_SDA_L();
	MPU6050_IIC_Delay(1);
	MPU6050_IIC_SCL_H();
	MPU6050_IIC_SDA_H();
	MPU6050_IIC_Delay(1);
}

void MPU6050_IIC_Ack(uint8_t re)
{
	MPU6050_IIC_SDA_OUT();
	if(re) {
	   MPU6050_IIC_SDA_H();
	} else {
	   MPU6050_IIC_SDA_L();
	}
	MPU6050_IIC_SCL_H();
	MPU6050_IIC_Delay(1);
	MPU6050_IIC_SCL_L();
	MPU6050_IIC_Delay(1);
}

uint8_t MPU6050_IIC_WaitAck(void)
{
	uint16_t time = 1000;
	MPU6050_IIC_SDA_H();
	MPU6050_IIC_SDA_IN();
	MPU6050_IIC_Delay(1);
	MPU6050_IIC_SCL_H();
	MPU6050_IIC_Delay(1);
	while(MPU6050_IIC_SDA_READ())
	{
		if(--time)
		{
			MPU6050_IIC_Stop();
			return 0;
		}
	}
	MPU6050_IIC_SCL_L();
	return 1;
}

void MPU6050_IIC_WriteByte(uint8_t byte)
{
	uint8_t i;
	MPU6050_IIC_SDA_OUT();
	MPU6050_IIC_SCL_L();
	for (i = 0; i < 8; i++)
	{
		if(byte & 0x80) {
			MPU6050_IIC_SDA_H();
		} else {
			MPU6050_IIC_SDA_L();
		}
		byte <<= 1;
		MPU6050_IIC_Delay(1);
		MPU6050_IIC_SCL_H();
		MPU6050_IIC_Delay(1);
		MPU6050_IIC_SCL_L();
	}
}

uint8_t MPU6050_IIC_ReadByte(void)
{
	uint8_t i, byte = 0;
	MPU6050_IIC_SDA_IN();
	for (i = 0; i < 8; i++)
	{
		MPU6050_IIC_SCL_L();
		MPU6050_IIC_Delay(1);
		MPU6050_IIC_SCL_H();
		byte <<= 1;
		if(IIC_SDA_Read()) {
		   byte++;
		}
		MPU6050_IIC_Delay(1);
	}
	MPU6050_IIC_SCL_L();
	return byte;
}

#define ABORT_IF_TIMEOUT() {if(!MPU6050_IIC_WaitAck()) return 0;}
uint8_t MPU6050_IIC_Read(uint8_t dev_addr,uint8_t reg_addr,uint8_t *pdata,uint8_t count)
{
	uint8_t i;

    MPU6050_IIC_Start();
	
    MPU6050_IIC_WriteByte(dev_addr);
    ABORT_IF_TIMEOUT();
    
    MPU6050_IIC_WriteByte(reg_addr);
    ABORT_IF_TIMEOUT();
	
    MPU6050_IIC_Start();
    
    MPU6050_IIC_WriteByte(dev_addr+1);
    ABORT_IF_TIMEOUT();
    
    for(i = 0; i < count - 1; i++)
    {
        *pdata = MPU6050_IIC_ReadByte();
        MPU6050_IIC_Ack(0);
        pdata++;
    }

    *pdata = MPU6050_IIC_ReadByte();

    MPU6050_IIC_Ack(1);
    MPU6050_IIC_Stop(); 
    
    return 1;
}

uint8_t MPU6050_IIC_Write(uint8_t dev_addr,uint8_t reg_addr,uint8_t data)
{
	MPU6050_IIC_Start();

	MPU6050_IIC_WriteByte(dev_addr);
	ABORT_IF_TIMEOUT();

	MPU6050_IIC_WriteByte(reg_addr);
	ABORT_IF_TIMEOUT();

    MPU6050_IIC_WriteByte(data);
	ABORT_IF_TIMEOUT();

	MPU6050_IIC_Stop();

    return 1;
}
