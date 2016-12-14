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
 
#include "main.h"

InputMode_t inputMode = INPUT_MODE_NO;
SwitchAction_t switch1Action = SWITCH_ACTION_NONE;
SwitchAction_t switch2Action = SWITCH_ACTION_NONE;
ChassisSpeedRef_t chassisSpeedRef = {0};
GimbalsSpeedRef_t gimbalsSpeedRef = {0};

void GetInputMode(DBUS_t* dbus)
{
	inputMode = dbus->rc.s2;
}

void GetSwitchAction(DBUS_t* dbus)
{
	static uint8_t last_s1 = 10;
	static uint8_t last_s2 = 10;
	uint8_t this_s1 = dbus->rc.s1;
	uint8_t this_s2 = dbus->rc.s2;
	switch1Action = GET_SWITCG_ACTION(last_s1, this_s1);
	switch2Action = GET_SWITCG_ACTION(last_s2, this_s2);
	last_s1 = this_s1;
	last_s2 = this_s2;
}

void GetRcChassisSpeed(DBUS_t* dbus)
{
	chassisSpeedRef.x = MAP(dbus->rc.ch0, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
	chassisSpeedRef.y = MAP(dbus->rc.ch1, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
	chassisSpeedRef.z = MAP(dbus->rc.ch2, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
}

void GetRcGimbalsSpeed(DBUS_t* dbus)
{
	gimbalsSpeedRef.yaw = MAP(dbus->rc.ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	gimbalsSpeedRef.pit = MAP(dbus->rc.ch3, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void GetHcChassisSpeed(DBUS_t* dbus)
{
	float speed = (dbus->hc.key.val & KEY_SHIFT) ? INPUT_CHASSIS_SPEED_MAX : INPUT_CHASSIS_SPEED_MAX / 2.f;
	chassisSpeedRef.x = (dbus->hc.key.val & KEY_A) ? -speed : ((dbus->hc.key.val & KEY_D) ? speed : 0);
	chassisSpeedRef.y = (dbus->hc.key.val & KEY_S) ? -speed : ((dbus->hc.key.val & KEY_W) ? speed : 0);
	chassisSpeedRef.z = MAP(dbus->hc.mouse.x, MS_MOV_MIN, MS_MOV_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void GetHcGimbalsSpeed(DBUS_t* dbus)
{
	gimbalsSpeedRef.yaw = MAP(dbus->hc.mouse.x, MS_MOV_MIN, MS_MOV_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	gimbalsSpeedRef.pit = MAP(dbus->hc.mouse.y, MS_MOV_MIN, MS_MOV_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void DBUS_CMD(DBUS_t* dbus)
{
	GetInputMode(dbus);
	GetSwitchAction(dbus);
	if(inputMode == INPUT_MODE_RC)
	{
		GetRcChassisSpeed(dbus);
		GetRcGimbalsSpeed(dbus);
	}
	else if(inputMode == INPUT_MODE_HC)
	{
		GetHcChassisSpeed(dbus);
		GetHcGimbalsSpeed(dbus);
	}
}
