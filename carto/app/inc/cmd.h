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

/***************************************/
/*               Command               */
/***************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "app.h"

enum {
	INPUT_MODE_NO,
	INPUT_MODE_RC,
	INPUT_MODE_HC,
	INPUT_MODE_AC,
}InputMode_e;

void Cmd_Init();
void Cmd_Proc();

void Rcv_Proc(uint8_t* dbuf);

extern InputMode_e inputMode;

extern PeriphsState_t functionalStateRef;
extern PantiltState_t pantiltPositionRef;
extern ChassisState_t chassisVelocityRef;

extern PantiltState_t pantiltVelocityRef;
extern MecanumState_t mecanumVelocityRef;

#ifdef __cplusplus
}
#endif

#endif
