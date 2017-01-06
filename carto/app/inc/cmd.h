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
 
#ifndef __CMD_H__
#define __CMD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "dbus.h"
#include "rci.h"
#include "hci.h"
#include "wdg.h"

typedef uint8_t InputMode_t;

#define INPUT_MODE_RC      SW_UP
#define INPUT_MODE_HC      SW_MID
#define INPUT_MODE_NO      SW_DOWN

#define CHASSIS_SPEED_MAX 4.0f     // 4m/s
#define PANTILT_SPEED_MAX 1.0f     // 1r/s

typedef uint32_t FunctionalState_t;

#define FUNCTIONAL_STATE_GUN      (((uint32_t)0x00000001)<<0)
#define FUNCTIONAL_STATE_LASER    (((uint32_t)0x00000001)<<1)
#define FUNCTIONAL_STATE_SPINNER  (((uint32_t)0x00000001)<<2)
#define FUNCTIONAL_STATE_ALL      (((uint32_t)0xFFFFFFFF))

typedef struct
{
	float x;
	float y;
	float z;
}ChassisSpeedRef_t;

typedef struct
{
	float y;
	float p;
}PantiltSpeedRef_t;

FunctionalState_t FS_Get(FunctionalState_t mask);
void              FS_Set(FunctionalState_t mask);
void              FS_Clr(FunctionalState_t mask);
void              FS_Tog(FunctionalState_t mask);
void              CS_Set(float x, float y, float z);
void              GS_Set(float y, float p);

void DBUS_Cmd(DBUS_t* dbus);

extern InputMode_t inputMode;
extern FunctionalState_t functionalState;
extern ChassisSpeedRef_t chassisSpeedRef;
extern PantiltSpeedRef_t pantiltSpeedRef;

#ifdef __cplusplus
}
#endif

#endif
