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

MouseButtonState_t mouseButtonStates[MOUSE_BUTTON_NUMBER];
MouseButtonEvent_t mouseButtonEvents[MOUSE_BUTTON_NUMBER];

void GetMouseButtonStates(HC_t* hc)
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

void GetMouseButtonEvents(HC_t* hc)
{
	static MouseButtonState_t last_state[MOUSE_BUTTON_NUMBER];
	uint32_t i = 0;
	for (; i < MOUSE_BUTTON_NUMBER; i++) {
		mouseButtonEvents[i] = GET_MOUSE_BUTTON_EVENT(last_state[i],mouseButtonStates[i]);
		last_state[i] = mouseButtonStates[i];
	}
}

void GetFunctionalState(HC_t* hc)
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

void GetChassisSpeedRef(HC_t* hc)
{
	static MAFilter_t* fx = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	static MAFilter_t* fy = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	static MAFilter_t* fz = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	static const float speed = (hc->key.val & KEY_SHIFT) ? CHASSIS_SPEED_MAX : CHASSIS_SPEED_MAX / 2.f;
	float vx = (hc->key.val & KEY_A) ? -speed : ((hc->key.val & KEY_D) ? speed : 0);
	float vy = (hc->key.val & KEY_S) ? -speed : ((hc->key.val & KEY_W) ? speed : 0);
	float vz = MAP(hc->mouse.x, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
	chassisSpeedRef.x = MAFilter_Calc(fx, vx);
	chassisSpeedRef.y = MAFilter_Calc(fy, vy);
	chassisSpeedRef.z = MAFilter_Calc(fz, vz);
}

void GetGimbalsSpeedRef(HC_t* hc)
{
	gimbalsSpeedRef.y = MAP(hc->mouse.x, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
	gimbalsSpeedRef.p = MAP(hc->mouse.y, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -GIMBALS_SPEED_MAX, GIMBALS_SPEED_MAX);
}

void HC_CMD(HC_t* hc)
{
	GetFunctionalState(hc);
	GetChassisSpeedRef(hc);
	GetGimbalsSpeedRef(hc);
}
