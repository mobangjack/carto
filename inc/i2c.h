#ifndef __I2C_H__
#define __I2C_H__

#include "stm32f4xx.h"

/*----I2C1----SCL----PB8---*/
/*----I2C1----SDA----PB9---*/

#define IIC_DEBUG 1

#define IIC_SCL_RCC_ENR      RCC->AHB1ENR
#define IIC_SCL_RCC_PRP      RCC_AHB1Periph_GPIOB
#define IIC_SCL_ENCLK()      (IIC_SCL_RCC_ENR |= IIC_SCL_RCC_PRP)
#define IIC_SCL_GPIO         GPIOB
#define IIC_SCL_GPIO_PIN     GPIO_Pin_8

#define IIC_SDA_RCC_ENR      RCC->AHB1ENR
#define IIC_SDA_RCC_PRP      RCC_AHB1Periph_GPIOB
#define IIC_SDA_ENCLK()      (IIC_SDA_RCC_ENR |= IIC_SDA_RCC_PRP)
#define IIC_SDA_GPIO         GPIOB
#define IIC_SDA_GPIO_PIN     GPIO_Pin_9

#define IIC_SCL_H()          GPIO_SetBits(IIC_SCL_GPIO,IIC_SCL_GPIO_PIN)
#define IIC_SCL_L()          GPIO_ResetBits(IIC_SCL_GPIO,IIC_SCL_GPIO_PIN)
#define IIC_SDA_H()          GPIO_SetBits(IIC_SDA_GPIO,IIC_SDA_GPIO_PIN)
#define IIC_SDA_L()          GPIO_ResetBits(IIC_SDA_GPIO,IIC_SDA_GPIO_PIN)
#define IIC_SDA_READ()       GPIO_ReadInputDataBit(IIC_SDA_GPIO,IIC_SDA_GPIO_PIN)

#define IIC_ERR(c) (((uint32_t)1)<<c)

void IIC_Init(void);
int IIC_Write(u8 dev_addr,u8 reg_addr,u8 data);
int IIC_Read(u8 dev_addr,u8 reg_addr,u8 *pdata,u8 count);

#endif
