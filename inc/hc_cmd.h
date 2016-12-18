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

#ifndef __HC_CMD_H__
#define __HC_CMD_H__

#include "hc_codec.h"

typedef uint8_t MouseButtonState_t;
typedef uint8_t MouseButtonEvent_t;

#define KEY_CONTROL_MAFILTER_LEN 10
#define MOUSE_BUTTON_STATE_CHANGE_DELAY 10

#define GET_MOUSE_BUTTON_EVENT(last,this) ((last<<2)|this)
#define MOUSE_BUTTON_EVENT_UP GET_MOUSE_BUTTON_EVENT(MOUSE_BUTTON_DOWM, MOUSE_BUTTON_UP)
#define MOUSE_BUTTON_EVENT_DOWN GET_MOUSE_BUTTON_EVENT(MOUSE_BUTTON_UP, MOUSE_BUTTON_DOWM)
#define MOUSE_BUTTON_EVENT_NONE 0

void HC_CMD(HC_t* hc);

extern MouseButtonState_t mouseButtonStates[MOUSE_BUTTON_NUMBER];
extern MouseButtonEvent_t mouseButtonEvents[MOUSE_BUTTON_NUMBER];

#endif /* __HC_CMD_H__ */