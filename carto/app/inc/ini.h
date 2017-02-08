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

#ifndef __INI_H__
#define __INI_H__

/******************************************************/
/*          System Initialization Information         */
/******************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "cfg.h"
#include "ctl.h"
#include "ins.h"
#include "can.h"

#define INI_FLAG_NONE   0u
#define INI_FLAG_CFG    (1u<<0)
#define INI_FLAG_IMU    (1u<<1)
#define INI_FLAG_MAG    (1u<<2)
#define INI_FLAG_ZGYRO  (1u<<3)
#define INI_FLAG_MOTOR1 (1u<<4)
#define INI_FLAG_MOTOR2 (1u<<5)
#define INI_FLAG_MOTOR3 (1u<<6)
#define INI_FLAG_MOTOR4 (1u<<7)
#define INI_FLAG_MOTOR5 (1u<<8)
#define INI_FLAG_MOTOR6 (1u<<9)
#define INI_FLAG_SIGNIFICANT    (INI_FLAG_CFG | INI_FLAG_IMU \
		                         INI_FLAG_MAG | INI_FLAG_ZGYRO | \
                                 INI_FLAG_MOTOR1 | INI_FLAG_MOTOR2 | \
								 INI_FLAG_MOTOR3 | INI_FLAG_MOTOR4 | \
								 INI_FLAG_MOTOR5 | INI_FLAG_MOTOR6)
#define INI_FLAG_ALL            (INI_FLAG_CFG | INI_FLAG_IMU \
		                         INI_FLAG_MAG | INI_FLAG_ZGYRO | \
                                 INI_FLAG_MOTOR1 | INI_FLAG_MOTOR2 | \
								 INI_FLAG_MOTOR3 | INI_FLAG_MOTOR4 | \
								 INI_FLAG_MOTOR5 | INI_FLAG_MOTOR6)

void Ini_Init();
void Ini_Proc();

uint32_t Ini_Get(uint32_t flag);
void Ini_Set(uint32_t flag);
void Ini_Clr(uint32_t flag);
void Ini_Check(uint8_t condition, uint32_t flag);

uint8_t Ini_Ok();


#ifdef __cplusplus
}
#endif

#endif
