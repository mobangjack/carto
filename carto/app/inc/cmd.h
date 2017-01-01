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

#include "dbus.h"

#define CHASSIS_SPEED_MAX 4.0f     // 4m/s
#define GIMBALS_SPEED_MAX 1.0f     // 1r/s

#define FUNCTIONAL_STATE_FIRE    (((uint32_t)0x00000001)<<0)
#define FUNCTIONAL_STATE_LASER   (((uint32_t)0x00000001)<<1)
#define FUNCTIONAL_STATE_LOADER  (((uint32_t)0x00000001)<<2)
#define FUNCTIONAL_STATE_ALL     (((uint32_t)0xFFFFFFFF))

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

extern FunctionalState_t functionalState;
extern ChassisSpeedRef_t chassisSpeedRef;
extern GimbalsSpeedRef_t gimbalsSpeedRef;

FunctionalState_t GET_FS(FunctionalState_t _functionalState);
void              SET_FS(FunctionalState_t _functionalState);
void              CLR_FS(FunctionalState_t _functionalState);
void              TOG_FS(FunctionalState_t _functionalState);
void              SET_CS(float vx, float vy, float vz);
void              SET_GS(float pitch, float yaw);


typedef uint8_t InputMode_t;

extern InputMode_t inputMode;

#define INPUT_MODE_RC      SW_UP
#define INPUT_MODE_HC      SW_MIDDLE
#define INPUT_MODE_NO      SW_DOWN

typedef uint8_t SwitchState_t;
typedef uint8_t SwitchEvent_t;

#define SWITCH_STATE_CHANGE_DELAY 10

#define SWITCH_STATE_0 ((uint8_t)0)
#define SWITCH_STATE_1 ((uint8_t)1)
#define SWITCH_STATE_3 ((uint8_t)3)
#define SWITCH_STATE_2 ((uint8_t)2)

#define GET_SWITCH_EVENT(last,this) (((last)<<2)|(this))
#define SWITCH_EVENT_3TO1 GET_SWITCH_EVENT(3, 1)
#define SWITCH_EVENT_1TO3 GET_SWITCH_EVENT(1, 3)
#define SWITCH_EVENT_3TO2 GET_SWITCH_EVENT(3, 2)
#define SWITCH_EVENT_2TO3 GET_SWITCH_EVENT(2, 3)
#define SWITCH_EVENT_NONE 0

typedef uint8_t MouseButtonState_t;
typedef uint8_t MouseButtonEvent_t;

extern SwitchState_t switchStates[SWITCH_COUNT];
extern SwitchEvent_t switchEvents[SWITCH_COUNT];

#define KEY_CONTROL_MAFILTER_LEN 10
#define MOUSE_BUTTON_STATE_CHANGE_DELAY 10

#define GET_MOUSE_BUTTON_EVENT(last,this) ((last<<2)|this)
#define MOUSE_BUTTON_EVENT_UP GET_MOUSE_BUTTON_EVENT(MOUSE_BUTTON_DOWM, MOUSE_BUTTON_UP)
#define MOUSE_BUTTON_EVENT_DOWN GET_MOUSE_BUTTON_EVENT(MOUSE_BUTTON_UP, MOUSE_BUTTON_DOWM)
#define MOUSE_BUTTON_EVENT_NONE 0

extern MouseButtonState_t mouseButtonStates[MOUSE_BUTTON_NUMBER];
extern MouseButtonEvent_t mouseButtonEvents[MOUSE_BUTTON_NUMBER];

void DBUS_CMD(DBUS_t* dbus);

#endif
