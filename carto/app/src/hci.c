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
 
#include "hci.h"

MouseButtonState_t mouseButtonStates[MOUSE_BTN_CNT];
MouseButtonEvent_t mouseButtonEvents[MOUSE_BTN_CNT];

static void GetMouseButtonStates(HC_t* hc)
{
	static MouseButtonState_t last_state[MOUSE_BTN_CNT];
	static uint32_t cnt[MOUSE_BTN_CNT];
	uint8_t* this_state = hc->mouse.b;
	uint32_t i = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
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

static void GetMouseButtonEvents(HC_t* hc)
{
	static MouseButtonState_t last_state[MOUSE_BTN_CNT];
	uint32_t i = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
		mouseButtonEvents[i] = GET_MOUSE_BUTTON_EVENT(last_state[i],mouseButtonStates[i]);
		last_state[i] = mouseButtonStates[i];
	}
}

static void GetFunctionalState(HC_t* hc)
{
	GetMouseButtonStates(hc);
	GetMouseButtonEvents(hc);
	if (mouseButtonStates[MOUSE_BTN_IDX_R]) {
		SET_FS(FUNCTIONAL_STATE_GUN | FUNCTIONAL_STATE_LASER);
		if (mouseButtonStates[MOUSE_BTN_IDX_L]) {
			SET_FS(FUNCTIONAL_STATE_SPINNER);
		}
	} else {
		CLR_FS(FUNCTIONAL_STATE_GUN | FUNCTIONAL_STATE_LASER | FUNCTIONAL_STATE_SPINNER);
	}
}

#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)

MAFilter_t* fx = (void *)0;
MAFilter_t* fy = (void *)0;
MAFilter_t* fz = (void *)0;
static void GetChassisSpeedRef(HC_t* hc)
{
	float speed = (hc->key.val & KEY_SHIFT) ? CHASSIS_SPEED_MAX : CHASSIS_SPEED_MAX / 2.f;
	float vx = (hc->key.val & KEY_A) ? -speed : ((hc->key.val & KEY_D) ? speed : 0);
	float vy = (hc->key.val & KEY_S) ? -speed : ((hc->key.val & KEY_W) ? speed : 0);
	float vz = MAP(hc->mouse.x, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -PANTILT_SPEED_MAX, PANTILT_SPEED_MAX);
	if (fx == NULL) {
		fx = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	}
	if (fy == NULL) {
		fy = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	}
	if (fz == NULL) {
		fz = MAFilter_Create(KEY_CONTROL_MAFILTER_LEN);
	}
	chassisSpeedRef.x = MAFilter_Calc(fx, vx);
	chassisSpeedRef.y = MAFilter_Calc(fy, vy);
	chassisSpeedRef.z = MAFilter_Calc(fz, vz);
}

static void GetPantiltSpeedRef(HC_t* hc)
{
	pantiltSpeedRef.y = MAP(hc->mouse.x, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -PANTILT_SPEED_MAX, PANTILT_SPEED_MAX);
	pantiltSpeedRef.p = MAP(hc->mouse.y, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -PANTILT_SPEED_MAX, PANTILT_SPEED_MAX);
}

void HCI_CMD(HC_t* hc)
{
	GetFunctionalState(hc);
	GetChassisSpeedRef(hc);
	GetPantiltSpeedRef(hc);
}
