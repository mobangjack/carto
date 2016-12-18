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

#ifndef __SYS_CMD_H__
#define __SYS_CMD_H__

#include <stdint.h>

#define ON 1
#define OFF 0

#define INPUT_MODE_RC      SW_UP
#define INPUT_MODE_HC      SW_MD
#define INPUT_MODE_NO      SW_DN

#define FUNCTIONAL_STATE_FIRE    (((uint32_t)0x00000001)<<0)
#define FUNCTIONAL_STATE_LASER   (((uint32_t)0x00000001)<<1)
#define FUNCTIONAL_STATE_LOADER  (((uint32_t)0x00000001)<<2)
#define FUNCTIONAL_STATE_ALL     (((uint32_t)0xFFFFFFFF))

#define INPUT_CHASSIS_SPEED_MAX 4.0f     // 4m/s
#define INPUT_GIMBALS_SPEED_MAX 1.0f     // 1r/s

typedef uint32_t FunctionalState_t;

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
}GimbalsSpeedRef_t;

typedef struct
{
	FunctionalState_t functionalState;
	ChassisSpeedRef_t chassisSpeedRef;
	GimbalsSpeedRef_t gimbalsSpeedRef;
}SYS_t;

extern FunctionalState_t functionalState;
extern ChassisSpeedRef_t chassisSpeedRef;
extern GimbalsSpeedRef_t gimbalsSpeedRef;

FunctionalState_t GET_FS(FunctionalState_t _functionalState);
void              SET_FS(FunctionalState_t _functionalState);
void              CLR_FS(FunctionalState_t _functionalState);
void              TOG_FS(FunctionalState_t _functionalState);

#endif /* __SYS_CMD_H__ */
