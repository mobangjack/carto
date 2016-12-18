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

SwitchAction_t switch1Action = SWITCH_ACTION_NONE;
SwitchAction_t switch2Action = SWITCH_ACTION_NONE;

void GetSwitchAction(RC_t* rc)
{
	static uint8_t last_s1 = 10;
	static uint8_t last_s2 = 10;
	uint8_t this_s1 = rc->s1;
	uint8_t this_s2 = rc->s2;
	switch1Action = GET_SWITCG_ACTION(last_s1, this_s1);
	switch2Action = GET_SWITCG_ACTION(last_s2, this_s2);
	last_s1 = this_s1;
	last_s2 = this_s2;
}

void GetChassisSpeed(RC_t* rc)
{
	chassisSpeedRef.x = MAP(rc->ch0, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
	chassisSpeedRef.y = MAP(rc->ch1, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
	chassisSpeedRef.z = MAP(rc->ch2, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
}

void GetGimbalsSpeed(RC_t* rc)
{
	gimbalsSpeedRef.y = MAP(rc->ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	gimbalsSpeedRef.p = MAP(rc->ch3, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void RC_CMD(RC_t* rc)
{
	GetSwitchAction(rc);
	GetChassisSpeed(rc);
	GetGimbalsSpeed(rc);
}

