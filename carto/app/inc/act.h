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

#ifndef __ACT_H__
#define __ACT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ctl.h"
#include "motor.h"

typedef struct
{
	float m1;
	float m2;
	float m3;
	float m4;
}ChassisCurrent_t;

typedef struct
{
	float y;
	float p;
}PantiltCurrent_t;

#define RAMP_DEFAULT RAMP(5000)

void Act_Proc();

extern ChassisCurrent_t chassisCurrent;
extern PantiltCurrent_t pantiltCurrent;

#ifdef __cplusplus
}
#endif