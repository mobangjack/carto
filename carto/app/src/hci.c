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

/********************************************/
/*          Host Control Interface          */
/********************************************/

static MouseButtonState_t mouseButtonStates[MOUSE_BTN_CNT];
static MouseButtonEvent_t mouseButtonEvents[MOUSE_BTN_CNT];

static MouseButtonState_t lastRawMouseButtonStates[MOUSE_BTN_CNT];
static uint32_t mouseButtonPressedCounts[MOUSE_BTN_CNT];
static void GetMouseButtonStates(const HC_t* hc)
{
	uint8_t* thisRawMouseButtonStates = hc->mouse.b;
	uint32_t i = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
		if (thisRawMouseButtonStates[i] == lastRawMouseButtonStates[i]) {
			if (mouseButtonPressedCounts[i] < MOUSE_BUTTON_PRESSED_CNT) {
				mouseButtonPressedCounts[i]++;
			} else {
				mouseButtonStates[i] = thisRawMouseButtonStates[i];
			}
		} else {
			mouseButtonPressedCounts[i] = 0;
		}
		lastRawMouseButtonStates[i] = thisRawMouseButtonStates[i];
	}
}

static MouseButtonState_t lastMouseButtonStates[MOUSE_BTN_CNT];
static void GetMouseButtonEvents(const HC_t* hc)
{
	uint32_t i = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
		mouseButtonEvents[i] = GET_MOUSE_BUTTON_EVENT(lastMouseButtonStates[i],mouseButtonStates[i]);
		lastMouseButtonStates[i] = mouseButtonStates[i];
	}
}

static void GetFunctionalStateRef(const HC_t* hc)
{
	GetMouseButtonStates(hc);
	GetMouseButtonEvents(hc);
	if (mouseButtonStates[MOUSE_BTN_IDX_R]) {
		FS_Set(&functionalStateRef, FS_GUN | FS_LASER);
		if (mouseButtonStates[MOUSE_BTN_IDX_L]) {
			FS_Set(&functionalStateRef, FS_SPINNER);
		} else {
			FS_Clr(&functionalStateRef, FS_SPINNER);
		}
	} else {
		FS_Clr(&functionalStateRef, FS_GUN | FS_LASER | FS_SPINNER);
	}
}

static MAFilter_t fx, fy, fz;
static float buf[3][KEY_CONTROL_MAFILTER_LEN];
static void GetChassisVelocityRef(const HC_t* hc)
{
	float speed = (hc->key.val & KEY_SHIFT) ? cfg.cha.spdCfg.max : cfg.cha.spdCfg.max / 2.f;
	float vx = (hc->key.val & KEY_A) ? -speed : ((hc->key.val & KEY_D) ? speed : 0);
	float vy = (hc->key.val & KEY_S) ? -speed : ((hc->key.val & KEY_W) ? speed : 0);
	float vz = MAP(hc->mouse.x, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -cfg.yaw.spdCfg.max, cfg.yaw.spdCfg.max);
	chassisVelocityRef.x = MAFilter_Calc(fx, vx);
	chassisVelocityRef.y = MAFilter_Calc(fy, vy);
	chassisVelocityRef.z = MAFilter_Calc(fz, vz);
}

static void GetPantiltPositionRef(const HC_t* hc)
{
	pantiltPositionRef.y += MAP(hc->mouse.x, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -cfg.yaw.spdCfg.max, cfg.yaw.spdCfg.max);
	pantiltPositionRef.p += MAP(hc->mouse.y, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX, -cfg.pit.spdCfg.max, cfg.pit.spdCfg.max);
}

void HCI_Init()
{
	uint32_t i = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
		lastRawMouseButtonStates[i] = 0;
		mouseButtonPressedCounts[i] = 0;
		mouseButtonStates[i] = 0;
		mouseButtonEvents[i] = 0;
		lastMouseButtonStates[i] = 0;
	}
	MAFilter_Init(&fx, buf[0], KEY_CONTROL_MAFILTER_LEN);
	MAFilter_Init(&fy, buf[1], KEY_CONTROL_MAFILTER_LEN);
	MAFilter_Init(&fz, buf[2], KEY_CONTROL_MAFILTER_LEN);
}

void HCI_Proc(const HC_t* hc)
{
	GetFunctionalStateRef(hc);
	GetChassisVelocityRef(hc);
	GetPantiltPositionRef(hc);
}
