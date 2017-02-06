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
 
#include "ims.h"

/**********************************************/
/*            Input Mode Switcher             */
/**********************************************/
DBUS_t dbus;
InputMode_e inputMode;
InputModeSwitch_e inputModeSwitch;

static void InputModeSwitchMach()
{
	switch (switchStates[SW_IDX_R]) {
	case SWITCH_STATE_1:
		inputMode = INPUT_MODE_RC;
		break;
	case SWITCH_STATE_3:
		inputMode = INPUT_MODE_HC;
		break;
	case SWITCH_STATE_2:
		inputMode = INPUT_MODE_AC;
		break;
	default:
		inputMode = INPUT_MODE_NO;
	}
}

static void InputModeSwitchProc()
{
	switch (inputModeSwitch) {
	case INPUT_MODE_SWITCH_R2H:
		break;
	case INPUT_MODE_SWITCH_H2R:
		break;
	case INPUT_MODE_SWITCH_R2A:
		break;
	case INPUT_MODE_SWITCH_A2R:
		break;
	case INPUT_MODE_SWITCH_H2A:
		break;
	case INPUT_MODE_SWITCH_A2H:
		break;
	default:
		break;
	}
}

void Ims_Init()
{
	inputMode = INPUT_MODE_NO;
	inputModeSwitch = INPUT_MODE_SWITCH_NOP;
}

/**********************************************/
/*         Command Interface Process          */
/**********************************************/
void Ims_Proc()
{
	InputModeSwitchMach();
	InputModeSwitchProc();
	if (inputMode == INPUT_MODE_RC)
	{
		Rci_Proc(&dbus.rc);
	}
	else if (inputMode == INPUT_MODE_HC)
	{
		Hci_Proc(&dbus.hc);
	}
	else if (inputMode == INPUT_MODE_AC)
	{
		// Aci_Proc(&cbus);
	}
	else {
		// Should not reach here
	}
}

/**********************************************/
/*       Wireless Receiver Data Process       */
/**********************************************/
void Rcv_Proc(uint8_t* buf)
{
	Wdg_Feed(WDG_IDX_RC);
	DBUS_Dec(&dbus, buf);
}

