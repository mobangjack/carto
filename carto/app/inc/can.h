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

#ifndef __CAN_H__
#define __CAN_H__

#define MOTOR_NUM 6

#include "motor.h"
#include "zgyro.h"
#include "est.h"
#include "wdg.h"

typedef struct
{
	float angle;
	float speed;
}Encoder_t;

void CAN_Proc(CanRxMsg* canRxMsg);
void Encoder_Reset(uint8_t i);

extern float ZGyroAngle;
extern Encoder_t encoder[MOTOR_NUM]; // encoder group

#endif
