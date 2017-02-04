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

#ifndef __INS_H__
#define __INS_H__

/**************************************/
/*     Inertial Navigation System     */
/**************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "app.h"

void Ins_Init();
void Ins_Proc();

void Mpu_Proc(float* buf);

extern Imu_t imu;
extern Mag_t mag;
extern Ahrs_t ahrs;
extern Euler_t euler;

#ifdef __cplusplus
}
#endif

#endif
