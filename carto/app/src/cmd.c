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

/*
FunctionalState_t functionalState;
ChassisSpeedRef_t chassisSpeedRef;
GimbalsSpeedRef_t gimbalsSpeedRef;

FunctionalState_t GET_FS(FunctionalState_t _functionalState)
{
	return functionalState & _functionalState;
}

void SET_FS(FunctionalState_t _functionalState)
{
	functionalState |= _functionalState;
}

void CLR_FS(FunctionalState_t _functionalState)
{
	functionalState &= ~_functionalState;
}

void TOG_FS(FunctionalState_t _functionalState)
{
	GET_FS(_functionalState) ? CLR_FS(_functionalState) : SET_FS(_functionalState);
}

void SET_CS(float vx, float vy, float vz)
{
	chassisSpeedRef.x = vx;
	chassisSpeedRef.y = vy;
	chassisSpeedRef.z = vz;
}

void SET_GS(float pitch, float yaw)
{
	gimbalsSpeedRef.p = pitch;
	gimbalsSpeedRef.y = yaw;
}

SwitchState_t switchStates[SWITCH_COUNT];
SwitchEvent_t switchEvents[SWITCH_COUNT];

void GetRCSwitchStates(RC_t* rc)
{
	static uint8_t last_state[SWITCH_COUNT];
	static uint32_t cnt[SWITCH_COUNT];
	uint8_t* this_state = rc->sw;
	uint32_t i = 0;
	for (; i < SWITCH_COUNT; i++) {
		if (this_state[i] == last_state[i]) {
			if (cnt[i] < SWITCH_STATE_CHANGE_DELAY) {
				cnt[i]++;
			} else {
				switchStates[i] = this_state[i];
			}
		} else {
			cnt[i] = 0;
		}
		last_state[i] = this_state[i];
	}
}

void GetRCSwitchEvents(RC_t* rc)
{
	static SwitchState_t last_state[SWITCH_COUNT];
	uint32_t i = 0;
	for (; i < SWITCH_COUNT; i++) {
		switchEvents[i] = GET_SWITCH_EVENT(last_state[i], switchStates[i]);
		last_state[i] = switchStates[i];
	}
}

void GetRCFunctionalStates(RC_t* rc)
{
	GetSwitchStates(rc);
	GetSwitchEvents(rc);
	switch (switchEvents[SWITCH_INDEX_LEFT]) {
		case SWITCH_EVENT_3TO1:
			TOG_FS(FUNCTIONAL_STATE_FIRE);
			if (GET_FS(FUNCTIONAL_STATE_FIRE)) {
				TOG_FS(FUNCTIONAL_STATE_LASER);
			}
			break;
		case SWITCH_EVENT_3TO2:
			if (GET_FS(FUNCTIONAL_STATE_FIRE)) {
				TOG_FS(FUNCTIONAL_STATE_LOADER);
			} else {
				CLR_FS(FUNCTIONAL_STATE_LOADER);
			}
			break;
		default:
			break;
	}
}

void GetRCChassisSpeedRef(RC_t* rc)
{
	chassisSpeedRef.x = MAP(rc->ch0, CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
	chassisSpeedRef.y = MAP(rc->ch1, CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
	chassisSpeedRef.z = MAP(rc->ch2, CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
}

void GetRCGimbalSpeedRef(RC_t* rc)
{
	gimbalsSpeedRef.y = MAP(rc->ch2, CH_MIN, CH_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
	gimbalsSpeedRef.p = MAP(rc->ch3, CH_MIN, CH_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
}

void RC_CMD(RC_t* rc)
{
	GetRCFunctionalStates(rc);
	GetRCChassisSpeedRef(rc);
	GetRCGimbalSpeedRef(rc);
}

MouseButtonState_t mouseButtonStates[MOUSE_BUTTON_NUMBER];
MouseButtonEvent_t mouseButtonEvents[MOUSE_BUTTON_NUMBER];

void GetHCMouseButtonStates(HC_t* hc)
{
	static MouseButtonState_t last_state[MOUSE_BUTTON_NUMBER];
	static uint32_t cnt[MOUSE_BUTTON_NUMBER];
	uint8_t* this_state = hc->mouse.b;
	uint32_t i = 0;
	for (; i < MOUSE_BUTTON_NUMBER; i++) {
		if (this_state[i] == last_state[i]) {
			if (cnt[i] < MOUSE_BUTTON_STATE_CHANGE_DELAY) {
				cnt[i]++;
			} else {
				mouseButtonStates[i] = this_state[i];
			}
		} else {
			cnt[i] = 0;
		}
		last_state[i] = this_state[i];
	}
}

void GetHCMouseButtonEvents(HC_t* hc)
{
	static MouseButtonState_t last_state[MOUSE_BUTTON_NUMBER];
	uint32_t i = 0;
	for (; i < MOUSE_BUTTON_NUMBER; i++) {
		mouseButtonEvents[i] = GET_MOUSE_BUTTON_EVENT(last_state[i],mouseButtonStates[i]);
		last_state[i] = mouseButtonStates[i];
	}
}

void GetHCFunctionalStates(HC_t* hc)
{
	GetMouseButtonStates(hc);
	GetMouseButtonEvents(hc);
	if (mouseButtonStates[MOUSE_BUTTON_INDEX_RIGHT]) {
		SET_FS(FUNCTIONAL_STATE_FIRE | FUNCTIONAL_STATE_LASER);
		if (mouseButtonStates[MOUSE_BUTTON_INDEX_LEFT]) {
			SET_FS(FUNCTIONAL_STATE_LOADER);
		}
	} else {
		CLR_FS(FUNCTIONAL_STATE_FIRE | FUNCTIONAL_STATE_LASER | FUNCTIONAL_STATE_LOADER);
	}
}

MAFilter_t* fx = NULL;
MAFilter_t* fy = NULL;
MAFilter_t* fz = NULL;
void GetHCChassisSpeedRef(HC_t* hc)
{
	float speed = (hc->key.val & KEY_SHIFT) ? CHASSIS_SPEED_MAX : CHASSIS_SPEED_MAX / 2.f;
	if (fx == NULL) {
		fx = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	}
	if (fy == NULL) {
		fy = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	}
	if (fz == NULL) {
		fz = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	}
	float vx = (hc->key.val & KEY_A) ? -speed : ((hc->key.val & KEY_D) ? speed : 0);
	float vy = (hc->key.val & KEY_S) ? -speed : ((hc->key.val & KEY_W) ? speed : 0);
	float vz = MAP(hc->mouse.x, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
	chassisSpeedRef.x = MAFilter_Calc(fx, vx);
	chassisSpeedRef.y = MAFilter_Calc(fy, vy);
	chassisSpeedRef.z = MAFilter_Calc(fz, vz);
}

void GetHCGimbalsSpeedRef(HC_t* hc)
{
	gimbalsSpeedRef.y = MAP(hc->mouse.x, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
	gimbalsSpeedRef.p = MAP(hc->mouse.y, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
}

void HC_CMD(HC_t* hc)
{
	GetHCFunctionalState(hc);
	GetHCChassisSpeedRef(hc);
	GetHCGimbalSpeedRef(hc);
}

InputMode_t inputMode = INPUT_MODE_NO;

void GetDBUSInputMode(DBUS_t* dbus)
{
	inputMode = dbus->rc.sw[SWITCH_INDEX_RIGHT];
}

void DBUS_CMD(DBUS_t* dbus)
{
	GetDBUSInputMode(dbus);
	if(inputMode == INPUT_MODE_RC)
	{
		RC_CMD(&dbus->rc);
	}
	else if(inputMode == INPUT_MODE_HC)
	{
		HC_CMD(&dbus->hc);
	}
}
*/
