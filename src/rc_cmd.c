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

#include "main.h"

SwitchState_t switchStates[SWITCH_NUMBER];
SwitchEvent_t switchEvents[SWITCH_NUMBER];

void GetSwitchStates(RC_t* rc)
{
	static uint8_t last_state[SWITCH_NUMBER];
	static uint32_t cnt[SWITCH_NUMBER];
	uint8_t* this_state = rc->sw;
	uint32_t i = 0;
	for (; i < SWITCH_NUMBER; i++) {
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

void GetSwitchEvents(RC_t* rc)
{
	static SwitchState_t last_state[SWITCH_NUMBER];
	uint32_t i = 0;
	for (; i < SWITCH_NUMBER; i++) {
		switchEvents[i] = GET_SWITCH_EVENT(last_state[i], switchStates[i]);
		last_state[i] = switchStates[i];
	}
}

void GetFunctionalState(RC_t* rc)
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

void GetChassisSpeedRef(RC_t* rc)
{
	chassisSpeedRef.x = MAP(rc->ch0, CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
	chassisSpeedRef.y = MAP(rc->ch1, CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
	chassisSpeedRef.z = MAP(rc->ch2, CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
}

void GetGimbalsSpeedRef(RC_t* rc)
{
	gimbalsSpeedRef.y = MAP(rc->ch2, CH_MIN, CH_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
	gimbalsSpeedRef.p = MAP(rc->ch3, CH_MIN, CH_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
}

void RC_CMD(RC_t* rc)
{
	GetFunctionalState(rc);
	GetChassisSpeedRef(rc);
	GetGimbalsSpeedRef(rc);
}

