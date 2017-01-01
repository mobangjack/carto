#ifndef __MPU6050_I2C_H__
#define __MPU6050_I2C_H__

#include "stm32util.h"

/*----MPU6050 I2C----SCL----PB8---*/
/*----MPU6050 I2C----SDA----PB9---*/

#define MPU6050_IIC_SCL_PIN PB8
#define MPU6050_IIC_SDA_PIN PB9

#define MPU6050_IIC_SCL_H()    GPIO_SET(MPU6050_IIC_SCL_PIN)
#define MPU6050_IIC_SCL_L()    GPIO_RST(MPU6050_IIC_SCL_PIN)
#define MPU6050_IIC_SDA_H()    GPIO_SET(MPU6050_IIC_SDA_PIN)
#define MPU6050_IIC_SDA_L()    GPIO_RST(MPU6050_IIC_SDA_PIN)
#define MPU6050_IIC_SDA_READ() GPIO_READ_IN(MPU6050_IIC_SDA_PIN)
#define MPU6050_IIC_SDA_IN()   GPIO_IN(MPU6050_IIC_SDA_PIN)
#define MPU6050_IIC_SDA_OUT()  GPIO_OUT(MPU6050_IIC_SDA_PIN)

uint8_t MPU6050_IIC_Read(uint8_t dev_addr,uint8_t reg_addr,uint8_t *pdata,uint8_t count);
uint8_t MPU6050_IIC_Write(uint8_t dev_addr,uint8_t reg_addr,uint8_t data);

#endif
