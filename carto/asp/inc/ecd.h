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

#ifndef __ECD_H__
#define __ECD_H__

#include "motor.h"
#include <stdint.h>

#define MOTOR_NUM 6

typedef struct
{
	int32_t raw;  // raw value
	int32_t rnd;  // round
	int32_t dif;  // difference
	int32_t con;  // continuous value
	int32_t exp;  // expected continuous value
	int32_t arc;  // arc
	float deg;    // expected value in degree
	float rad;    // expected value in radian
	float vel;    // velocity
}ECD_t;

void ECD_PROC(uint8_t i, uint8_t* data);

extern ECD_t ecd[MOTOR_NUM];

#endif
