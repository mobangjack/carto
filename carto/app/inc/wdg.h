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

#include <stdint.h>

#define WDG_NUM              11u

#define WDG_IDX_RC           0u
#define WDG_IDX_CALI         1u
#define WDG_IDX_API          2u
#define WDG_IDX_IMU          3u
#define WDG_IDX_ZGYRO        4u
#define WDG_IDX_MOTOR1       5u
#define WDG_IDX_MOTOR2       6u
#define WDG_IDX_MOTOR3       7u
#define WDG_IDX_MOTOR4       8u
#define WDG_IDX_MOTOR5       9u
#define WDG_IDX_MOTOR6       10u


#define WDG_ERR_RC			 (1<<WDG_IDX_RC)
#define WDG_ERR_CALI		 (1<<WDG_IDX_CALI)
#define WDG_ERR_API			 (1<<WDG_IDX_API)
#define WDG_ERR_IMU			 (1<<WDG_IDX_IMU)
#define WDG_ERR_ZGYRO		 (1<<WDG_IDX_ZGYRO)
#define WDG_ERR_MOTOR1		 (1<<WDG_IDX_MOTOR1)
#define WDG_ERR_MOTOR2		 (1<<WDG_IDX_MOTOR2)
#define WDG_ERR_MOTOR3		 (1<<WDG_IDX_MOTOR3)
#define WDG_ERR_MOTOR4		 (1<<WDG_IDX_MOTOR4)
#define WDG_ERR_MOTOR5		 (1<<WDG_IDX_MOTOR5)
#define WDG_ERR_MOTOR6		 (1<<WDG_IDX_MOTOR6)

#define WDG_ERR_ALL ( \
		WDG_ERR_RC | \
		WDG_ERR_CALI | \
		WDG_ERR_API | \
		WDG_ERR_IMU | \
		WDG_ERR_ZGYRO | \
		WDG_ERR_MOTOR1 | \
		WDG_ERR_MOTOR2 | \
		WDG_ERR_MOTOR3 | \
		WDG_ERR_MOTOR4 | \
		WDG_ERR_MOTOR5 | \
		WDG_ERR_MOTOR6 \
		)

#define WDG_OVERFLOW_CNT_RC   	    10
#define WDG_OVERFLOW_CNT_CALI 		50
#define WDG_OVERFLOW_CNT_API  		50
#define WDG_OVERFLOW_CNT_IMU  		50
#define WDG_OVERFLOW_CNT_ZGYRO 		50
#define WDG_OVERFLOW_CNT_MOTOR 		50

void WDG_SRV(void);
void WDG_Feed(uint8_t i);
uint32_t WDG_GetErr(void);
uint8_t WDG_IsErrSet(uint32_t mask);

#endif

