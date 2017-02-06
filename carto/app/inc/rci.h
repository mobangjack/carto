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
 
#ifndef __RCI_H__
#define __RCI_H__

/**********************************************/
/*          Remote Control Interface          */
/**********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "dbus.h"
#include "cmd.h"

typedef uint8_t SwitchState_t;
typedef uint8_t SwitchEvent_t;

#define SWITCH_CONFIRM_CNT 10

#define SWITCH_STATE_0 ((uint8_t)0)
#define SWITCH_STATE_1 ((uint8_t)1)
#define SWITCH_STATE_3 ((uint8_t)3)
#define SWITCH_STATE_2 ((uint8_t)2)

#define GET_SWITCH_EVENT(LAST,THIS) (((LAST)<<3)|(THIS))
#define SWITCH_EVENT_3TO1 GET_SWITCH_EVENT(3, 1)
#define SWITCH_EVENT_1TO3 GET_SWITCH_EVENT(1, 3)
#define SWITCH_EVENT_3TO2 GET_SWITCH_EVENT(3, 2)
#define SWITCH_EVENT_2TO3 GET_SWITCH_EVENT(2, 3)
#define SWITCH_EVENT_NONE 0

void Rci_Init();
void Rci_Proc(RC_t* rc);

extern SwitchState_t switchStates[SW_CNT];
extern SwitchEvent_t switchEvents[SW_CNT];

#ifdef __cplusplus
}
#endif

#endif
