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

/***************************************/
/*               Command               */
/***************************************/

InputMode_e inputMode;

PeriphsState_t functionalStateRef;
ChassisState_t chassisVelocityRef;
PantiltState_t pantiltVelocityRef;

static DBUS_t dbus;
static CBUS_t cbus;

static void GetInputMode(const RC_t* rc)
{
	switch (rc->sw[SW_IDX_R]) {
	case SW_UP:
		inputMode = INPUT_MODE_RC;
		break;
	case SW_MID:
		inputMode = INPUT_MODE_HC;
		break;
	case SW_MID:
		inputMode = INPUT_MODE_AC;
		break;
	default:
		inputMode = INPUT_MODE_NO;
	}
}

void Cmd_Init()
{
	RCI_Init();
	HCI_Init();
	ACI_Init();
}

void Cmd_Proc()
{
	GetInputMode(&dbus.rc);
	if (inputMode == INPUT_MODE_RC)
	{
		RCI_Proc(&dbus.rc);
	}
	else if (inputMode == INPUT_MODE_HC)
	{
		HCI_Proc(&dbus.hc);
	}
	else if (inputMode == INPUT_MODE_AC)
	{
		ACI_Proc(&cbus);
	}
	else {
		// Should not reach here
	}
	Mecanum_Decompose(&mecanum, (float*)&chassisVelocityRef, (float*)&mecanumVelocityRef);
}

void Rcv_Proc(uint8_t* buf)
{
	Wdg_Feed(WDG_IDX_RC);
	DBUS_Dec(&dbus, buf);
}

