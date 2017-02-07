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
CBUS_t cbus;
InputMode_e inputMode;
InputModeSwitch_e inputModeSwitch;

static void InputModeSwitchMach()
{
	switch (switchStates[SW_IDX_R]) {
	case SWITCH_STATE_0:
		switch (switchEvents[SW_IDX_R]) {
		case SWITCH_EVENT_1TO0:
			inputModeSwitch = INPUT_MODE_SWITCH_R2N;
			break;
		case SWITCH_EVENT_2TO0:
			inputModeSwitch = INPUT_MODE_SWITCH_A2N;
			break;
		case SWITCH_EVENT_3TO0:
			inputModeSwitch = INPUT_MODE_SWITCH_H2N;
			break;
		default:
			inputModeSwitch = INPUT_MODE_SWITCH_NOP;
		}
		inputMode = INPUT_MODE_NO;
		break;
	case SWITCH_STATE_1:
		switch (switchEvents[SW_IDX_R]) {
		case SWITCH_EVENT_0TO1:
			inputModeSwitch = INPUT_MODE_SWITCH_N2R;
			break;
		case SWITCH_EVENT_2TO1:
			inputModeSwitch = INPUT_MODE_SWITCH_A2R;
			break;
		case SWITCH_EVENT_3TO1:
			inputModeSwitch = INPUT_MODE_SWITCH_H2R;
			break;
		default:
			inputModeSwitch = INPUT_MODE_SWITCH_NOP;
		}
		inputMode = INPUT_MODE_RC;
		break;
	case SWITCH_STATE_2:
		switch (switchEvents[SW_IDX_R]) {
		case SWITCH_EVENT_0TO2:
			inputModeSwitch = INPUT_MODE_SWITCH_N2A;
			break;
		case SWITCH_EVENT_1TO2:
			inputModeSwitch = INPUT_MODE_SWITCH_R2A;
			break;
		case SWITCH_EVENT_3TO2:
			inputModeSwitch = INPUT_MODE_SWITCH_H2A;
			break;
		default:
			inputModeSwitch = INPUT_MODE_SWITCH_NOP;
		}
		inputMode = INPUT_MODE_AC;
		break;
	case SWITCH_STATE_3:
		switch (switchEvents[SW_IDX_R]) {
		case SWITCH_EVENT_0TO3:
			inputModeSwitch = INPUT_MODE_SWITCH_N2H;
			break;
		case SWITCH_EVENT_1TO3:
			inputModeSwitch = INPUT_MODE_SWITCH_R2H;
			break;
		case SWITCH_EVENT_2TO3:
			inputModeSwitch = INPUT_MODE_SWITCH_A2H;
			break;
		default:
			inputModeSwitch = INPUT_MODE_SWITCH_NOP;
		}
		inputMode = INPUT_MODE_HC;
		break;
	default:
		inputMode = INPUT_MODE_NO;
		inputModeSwitch = INPUT_MODE_SWITCH_NOP;
	}
}

static void InputModeSwitchProc()
{
	switch (inputModeSwitch) {
	case INPUT_MODE_SWITCH_NOP:
		break;
	case INPUT_MODE_SWITCH_N2R:
		break;
	case INPUT_MODE_SWITCH_R2N:
		break;
	case INPUT_MODE_SWITCH_N2H:
		break;
	case INPUT_MODE_SWITCH_H2N:
		break;
	case INPUT_MODE_SWITCH_N2A:
		break;
	case INPUT_MODE_SWITCH_A2N:
		break;
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
/*        Input Mode Switcher Process         */
/**********************************************/
void Ims_Proc()
{
	GetSwitchStates(&dbus.rc);
	GetSwitchEvents(&dbus.rc);
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
		Aci_Proc(&cbus);
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

