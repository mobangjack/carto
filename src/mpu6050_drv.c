/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
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

#include "main.h"

uint32_t MPU6050_Init(void)
{
    uint8_t data = 0x00;
    IIC_Init();
    if(IIC_Read(MPU6050_DEVICE_ADDRESS,WHO_AM_I,&data,1) != 0)
    {
#ifdef MPU6050_DEBUG
    	printf("mpu6050 init error 1.\r\n");
#endif
        return MPU6050ERR(1);
    }
    else
    {
    	if(data != MPU6050_ID)
		{
#ifdef MPU6050_DEBUG
			printf("mpu6050 init error 2.\r\n");
#endif
			return MPU6050ERR(2);
		}
    }
    if(IIC_Write(MPU6050_DEVICE_ADDRESS,PWR_MGMT_1,0x01) != 0)    // Exiting the sleeping mode
    {
#ifdef MPU6050_DEBUG
    	printf("mpu6050 init error 3.\r\n");
#endif
        return MPU6050ERR(3);
    }
    if(IIC_Write(MPU6050_DEVICE_ADDRESS,CONFIG,0x03) != 0)   // Digital Low-Pass Filter: DLPF_CFG is 3, frequency: 1khz
    {                                                           // ACC bandwidth: 44Hz,GYRO bandwidth: 42Hz
#ifdef MPU6050_DEBUG
        printf("mpu6050 init error 4.\r\n");
#endif
        return MPU6050ERR(4);
    }
    if(IIC_Write(MPU6050_DEVICE_ADDRESS,GYRO_CONFIG,0x10) != 0)    // FS_SEL 3 : gyroscope full scale range is +-1000degs/s
    {
#ifdef MPU6050_DEBUG
    	printf("mpu6050 init error 5.\r\n");
#endif
        return MPU6050ERR(5);
    }
    if(IIC_Write(MPU6050_DEVICE_ADDRESS,ACCEL_CONFIG,0x00) != 0)   // AFS_SEL 1: accelerometer full scale range is +-2g
    {
#ifdef MPU6050_DEBUG
    	printf("mpu6050 init error 6.\r\n");
#endif
        return MPU6050ERR(6);
    }
    if(IIC_Write(MPU6050_DEVICE_ADDRESS,INT_PIN_CFG,0x02) != 0)    // logic level for the INT pin is active high
    {
#ifdef MPU6050_DEBUG
    	printf("mpu6050 init error 7.\r\n");
#endif
        return MPU6050ERR(7);
    }
    if(IIC_Write(MPU6050_DEVICE_ADDRESS,INT_ENABLE,0x00) != 0)      // disable data ready interrupt
    {
#ifdef MPU6050_DEBUG
    	printf("mpu6050 init error 8.\r\n");
#endif
        return MPU6050ERR(8);
    }
	// mpu6050 IIC masters mode  disabled
	if(IIC_Write(MPU6050_DEVICE_ADDRESS,MPU6050_RA_USER_CTRL,0x00) != 0)      // disable data ready interrupt
    {
#ifdef MPU6050_DEBUG
		printf("mpu6050 init error 9.\r\n");
#endif
        return MPU6050ERR(9);
    }
	// masters mode bypass mode enabled
    // HMC5883
	if(HMC5883_Init() != 0)
	{
#ifdef MPU6050_DEBUG
		printf("mpu6050 init error 10.\r\n");
#endif
		return MPU6050ERR(10);
	}
    return 0;
}

uint32_t HMC5883_Init(void)
{
    uint8_t data = 0;
    if(IIC_Read(HMC5883_ADDRESS, HMC58X3_R_IDA, &data, 1) != 0)
    {
#ifdef MPU6050_DEBUG
    	printf("HMC5883 init error 1.\r\n");
        return HMC5883ERR(1);
#endif
    }
    else
    {
		if(data != HMC5883_DEVICE_ID_A)
		{
#ifdef MPU6050_DEBUG
			printf("HMC5886 init error 2.\r\n");
#endif
			return HMC5883ERR(2);
		}
    }
    IIC_Write(HMC5883_ADDRESS, HMC58X3_R_CONFA,0x70);
    delay_ms(5);
    IIC_Write(HMC5883_ADDRESS, HMC58X3_R_CONFB,0xA0);
    delay_ms(5);
    IIC_Write(HMC5883_ADDRESS, HMC58X3_R_MODE,0x00);
    delay_ms(6); // wait 6 milliseconds for stabilization
    IIC_Write(HMC5883_ADDRESS, HMC58X3_R_CONFA,6<<2);   //75HZ
    delay_ms(6);
    return 0;
}

uint32_t MPU6050_Wait(int t)
{
    while(MPU6050_Init() != 0)
    {
    	if (--t < 1) return 0xff;
        delay_ms(500);
    }
    return 0;
}

int MPU6050_EnInt(void)
{
	if(IIC_Write(MPU6050_DEVICE_ADDRESS,SMPLRT_DIV,0x01) != 0)      //Sample Rate: Gyro output rate / (1 + 1) = 500Hz
	{
#ifdef MPU6050_DEBUG
		printf("mpu6050 error 11.\r\n");
#endif
        return MPU6050ERR(11);
	}
	delay_ms(10);
	if(IIC_Write(MPU6050_DEVICE_ADDRESS,INT_ENABLE,0x01) != 0)     //enable data ready interrupt
	{
#ifdef MPU6050_DEBUG
		printf("mpu6050 error 12.\r\n");
#endif
		return MPU6050ERR(12);
	}
	return 0;
}

uint32_t MPU6050_Read(ImuRawData_t* imu)
{
	uint8_t buf[14];
	if (IIC_Read(MPU6050_DEVICE_ADDRESS,MPU6050_DATA_START,buf,14) != 0)
	{
		return MPU6050ERR(13);
	}
	imu->ax = (((int16_t)buf[0]) << 8) | buf[1];
	imu->ay = (((int16_t)buf[2]) << 8) | buf[3];
	imu->az = (((int16_t)buf[4]) << 8) | buf[5];
	imu->tp = (((int16_t)buf[6]) << 8) | buf[7];
	imu->gx = (((int16_t)buf[8]) << 8) | buf[9];
	imu->gy = (((int16_t)buf[10]) << 8) | buf[11];
	imu->gz = (((int16_t)buf[12]) << 8) | buf[13];
	return 0;
}

uint32_t HMC58X3_Read(MagRawData_t* mag)
{
	uint8_t buf[6];
	if (IIC_Read(HMC5883_ADDRESS,HMC58X3_R_XM,buf,6) != 0)
	{
		return MPU6050ERR(14);
	}
	mag->mx = (((int16_t)buf[0]) << 8) | buf[1];
	mag->my = (((int16_t)buf[2]) << 8) | buf[3];
	mag->mz = (((int16_t)buf[4]) << 8) | buf[5];
	return 0;
}
