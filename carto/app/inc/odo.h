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
 
#ifndef __ODO_H__
#define __ODO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "app.h"
#include "can.h"
#include "mecanum.h"

typedef struct
{
	float px;
	float py;
	float pz;
	float vx;
	float vy;
	float vz;
}Odo_t;

void Odo_Calc(Odo_t* odo);

#ifdef __cplusplus
}
#endif

#endif
