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

InputMode inputMode = INPUT_MODE_NO;
SwitchAction switch1Action = SWITCH_ACTION_NONE;
SwitchAction switch2Action = SWITCH_ACTION_NONE;
ChassisSpeed chassisSpeed = {0};
GimbalsSpeed gimbalsSpeed = {0};

void GetInputMode(void)
{
	inputMode = dbus.rc.s2;
}

void GetSwitchAction()
{
	static uint8_t last_s1 = 10;
	static uint8_t last_s2 = 10;
	uint8_t this_s1 = dbus.rc.s1;
	uint8_t this_s2 = dbus.rc.s2;
	switch1Action = GET_SWITCG_ACTION(last_s1, this_s1);
	switch2Action = GET_SWITCG_ACTION(last_s2, this_s2);
	last_s1 = this_s1;
	last_s2 = this_s2;
}

void GetRcChassisSpeed(void)
{
	chassisSpeed.x = MAP(dbus.rc.ch0, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
	chassisSpeed.y = MAP(dbus.rc.ch1, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
	chassisSpeed.z = MAP(dbus.rc.ch2, CH_MIN, CH_MAX, -INPUT_CHASSIS_SPEED_MAX, INPUT_CHASSIS_SPEED_MAX);
}

void GetRcGimbalsSpeed(void)
{
	gimbalsSpeed.yaw = MAP(dbus.rc.ch2, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	gimbalsSpeed.pit = MAP(dbus.rc.ch3, CH_MIN, CH_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void GetHcChassisSpeed(void)
{
	float speed = (dbus.hc.key.val & KEY_SHIFT) ? INPUT_CHASSIS_SPEED_MAX : INPUT_CHASSIS_SPEED_MAX / 2.f;
	chassisSpeed.x = (dbus.hc.key.val & KEY_A) ? -speed : ((dbus.hc.key.val & KEY_D) ? speed : 0);
	chassisSpeed.y = (dbus.hc.key.val & KEY_S) ? -speed : ((dbus.hc.key.val & KEY_W) ? speed : 0);
	chassisSpeed.z = MAP(dbus.hc.mouse.x, MS_MIN, MS_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void GetHcGimbalsSpeed(void)
{
	gimbalsSpeed.yaw = MAP(dbus.hc.mouse.x, MS_MIN, MS_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
	gimbalsSpeed.pit = MAP(dbus.hc.mouse.y, MS_MIN, MS_MAX, -INPUT_GIMBALS_SPEED_MAX, INPUT_GIMBALS_SPEED_MAX);
}

void InputTask(void)
{
	GetInputMode();
	GetSwitchAction();
	if(inputMode == INPUT_MODE_RC)
	{
		GetRcChassisSpeed();
		GetRcGimbalsSpeed();
	}
	else if(inputMode == INPUT_MODE_HC)
	{
		GetHcChassisSpeed();
		GetHcGimbalsSpeed();
	}
}
