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

void GetChassisSpeed(HC_t* hc)
{
	float speed = (hc->key.val & KEY_SHIFT) ? INPUT_CHASSIS_SPEED_MAX : INPUT_CHASSIS_SPEED_MAX / 2.f;
	chassisSpeedRef.x = (hc->key.val & KEY_A) ? -speed : ((hc->key.val & KEY_D) ? speed : 0);
	chassisSpeedRef.y = (hc->key.val & KEY_S) ? -speed : ((hc->key.val & KEY_W) ? speed : 0);
	chassisSpeedRef.z = MAP(hc->mouse.x, MS_MOV_MIN, MS_MOV_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void GetGimbalsSpeed(HC_t* hc)
{
	gimbalsSpeedRef.y = MAP(hc->mouse.x, MS_MOV_MIN, MS_MOV_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	gimbalsSpeedRef.p = MAP(hc->mouse.y, MS_MOV_MIN, MS_MOV_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void HC_CMD(HC_t* hc)
{
	GetChassisSpeed(hc);
	GetGimbalsSpeed(hc);
}
