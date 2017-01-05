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
 
#include "cmd.h"

InputMode_t inputMode;
FunctionalState_t functionalState;
ChassisSpeedRef_t chassisSpeedRef;
PantiltSpeedRef_t pantiltSpeedRef;

FunctionalState_t GET_FS(FunctionalState_t mask)
{
	return functionalState & mask;
}

void SET_FS(FunctionalState_t mask)
{
	functionalState |= mask;
}

void CLR_FS(FunctionalState_t mask)
{
	functionalState &= ~mask;
}

void TOG_FS(FunctionalState_t mask)
{
	GET_FS(mask) ? CLR_FS(mask) : SET_FS(mask);
}

void SET_CS(float x, float y, float z)
{
	chassisSpeedRef.x = x;
	chassisSpeedRef.y = y;
	chassisSpeedRef.z = z;
}

void SET_GS(float yaw, float pitch)
{
	pantiltSpeedRef.y = yaw;
	pantiltSpeedRef.p = pitch;
}

void GetInputMode(DBUS_t* dbus)
{
	inputMode = dbus->rc.sw[SW_IDX_R];
}

void DBUS_Cmd(DBUS_t* dbus)
{
	WDG_Feed(WDG_IDX_RC);
	GetInputMode(dbus);
	if(inputMode == INPUT_MODE_RC)
	{
		RCI_Cmd(&dbus->rc);
	}
	else if(inputMode == INPUT_MODE_HC)
	{
		HCI_Cmd(&dbus->hc);
	}
}

