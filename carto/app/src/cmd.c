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

FunctionalState_t FS_Get(FunctionalState_t mask)
{
	return functionalState & mask;
}

void FS_Set(FunctionalState_t mask)
{
	functionalState |= mask;
}

void FS_Clr(FunctionalState_t mask)
{
	functionalState &= ~mask;
}

void FS_Tog(FunctionalState_t mask)
{
	FS_Get(mask) ? FS_Clr(mask) : FS_Set(mask);
}

void CS_Set(float x, float y, float z)
{
	chassisSpeedRef.x = x;
	chassisSpeedRef.y = y;
	chassisSpeedRef.z = z;
}

void GS_Set(float y, float p)
{
	pantiltSpeedRef.y = y;
	pantiltSpeedRef.p = p;
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

void CBUS_Cmd(CBUS_t* cbus)
{

}
