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

#ifndef __FUN_H__
#define __FUN_H__

/******************************************************/
/*                  Helper Functions                  */
/******************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "app.h"

// commonly used macros
#define PI 3.1415926f
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)
#define LIMIT(X,MIN,MAX) ((X)=(X)>(MAX)?(MAX):((X)<(MIN)?MIN:(MIN)))

float map(float val, float min1, float max1, float min2, float max2);
PeriphsState_t FS_Get(const PeriphsState_t* fs, PeriphsState_t msk);
void FS_Set(PeriphsState_t* fs, PeriphsState_t msk);
void FS_Clr(PeriphsState_t* fs, PeriphsState_t msk);
void FS_Tog(PeriphsState_t* fs, PeriphsState_t msk);
void CS_Set(ChassisState_t* cs, float x, float y, float z);
void GS_Set(PantiltState_t* gs, float y, float p);
void MS_Set(MecanumState_t* ms, float w1, float w2, float w3, float w4);

#ifdef __cplusplus
}
#endif

#endif
