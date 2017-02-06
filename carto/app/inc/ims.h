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
 
#ifndef __IMS_H__
#define __IMS_H__

/**********************************************/
/*            Input Mode Switcher             */
/**********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "cmd.h"
#include "rci.h"
#include "hci.h"
#include "wdg.h"

typedef enum {
	INPUT_MODE_NO,
	INPUT_MODE_RC,
	INPUT_MODE_HC,
	INPUT_MODE_AC,
}InputMode_e;

typedef enum {
	INPUT_MODE_SWITCH_NOP, // Input Mode Switch: No Operation
	INPUT_MODE_SWITCH_R2H, // Input Mode Switch: RC -> HC
	INPUT_MODE_SWITCH_H2R, // Input Mode Switch: HC -> RC
	INPUT_MODE_SWITCH_R2A, // Input Mode Switch: RC -> AC
	INPUT_MODE_SWITCH_A2R, // Input Mode Switch: AC -> RC
	INPUT_MODE_SWITCH_H2A, // Input Mode Switch: HC -> AC
	INPUT_MODE_SWITCH_A2H, // Input Mode Switch: AC -> HC
}InputModeSwitch_e;

void Ims_Init();
void Ims_Proc();

void Rcv_Proc(uint8_t* dbuf);

/**********************************************/
/*             Exported Variables             */
/**********************************************/
extern DBUS_t dbus;
extern InputMode_e inputMode;
extern InputModeSwitch_e inputModeSwitch;

#ifdef __cplusplus
}
#endif

#endif
