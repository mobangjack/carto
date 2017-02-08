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

#ifndef __WDG_H__
#define __WDG_H__

/***********************************/
/*            Watch Dog            */
/***********************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define WDG_NUM              10u

#define WDG_IDX_RC           0u
#define WDG_IDX_COM          1u
#define WDG_IDX_IMU          2u
#define WDG_IDX_ZGYRO        3u
#define WDG_IDX_MOTOR1       4u
#define WDG_IDX_MOTOR2       5u
#define WDG_IDX_MOTOR3       6u
#define WDG_IDX_MOTOR4       7u
#define WDG_IDX_MOTOR5       8u
#define WDG_IDX_MOTOR6       9u


#define WDG_ERR_RC			 (1u<<WDG_IDX_RC)
#define WDG_ERR_COM			 (1u<<WDG_IDX_COM)
#define WDG_ERR_IMU			 (1u<<WDG_IDX_IMU)
#define WDG_ERR_ZGYRO		 (1u<<WDG_IDX_ZGYRO)
#define WDG_ERR_MOTOR1		 (1u<<WDG_IDX_MOTOR1)
#define WDG_ERR_MOTOR2		 (1u<<WDG_IDX_MOTOR2)
#define WDG_ERR_MOTOR3		 (1u<<WDG_IDX_MOTOR3)
#define WDG_ERR_MOTOR4		 (1u<<WDG_IDX_MOTOR4)
#define WDG_ERR_MOTOR5		 (1u<<WDG_IDX_MOTOR5)
#define WDG_ERR_MOTOR6		 (1u<<WDG_IDX_MOTOR6)

#define WDG_ERR_ALL ( \
		WDG_ERR_RC | \
		WDG_ERR_COM | \
		WDG_ERR_IMU | \
		WDG_ERR_ZGYRO | \
		WDG_ERR_MOTOR1 | \
		WDG_ERR_MOTOR2 | \
		WDG_ERR_MOTOR3 | \
		WDG_ERR_MOTOR4 | \
		WDG_ERR_MOTOR5 | \
		WDG_ERR_MOTOR6 \
		)

#define WDG_ERR_FATAL ( \
		WDG_ERR_RC | \
		WDG_ERR_IMU | \
		WDG_ERR_ZGYRO | \
		WDG_ERR_MOTOR1 | \
		WDG_ERR_MOTOR2 | \
		WDG_ERR_MOTOR3 | \
		WDG_ERR_MOTOR4 | \
		WDG_ERR_MOTOR5 | \
		WDG_ERR_MOTOR6 \
		)

#define WDG_OVERFLOW_CNT_RC   	    100u
#define WDG_OVERFLOW_CNT_COM  		100u
#define WDG_OVERFLOW_CNT_IMU  		100u
#define WDG_OVERFLOW_CNT_ZGYRO 		100u
#define WDG_OVERFLOW_CNT_MOTOR 		100u

void Wdg_Init();
void Wdg_Proc();
void Wdg_Feed(uint8_t i);
void Wdg_Hang(uint8_t i);
uint32_t Wdg_GetErr();
uint8_t Wdg_IsErrSet(uint32_t mask);

#ifdef __cplusplus
}
#endif

#endif

