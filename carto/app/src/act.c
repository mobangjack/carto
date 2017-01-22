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

#include "act.h"

/**********************************/
/*             Action             */
/**********************************/

static void PeriphsStateCmd()
{
	if (FS_Get(&functionalStateCtl, FS_LED_GREEN)) {
		LED_GREEN_ON();
	} else {
		LED_GREEN_OFF();
	}
	if (FS_Get(&functionalStateCtl, FS_LED_RED)) {
		LED_RED_ON();
	} else {
		LED_RED_OFF();
	}
	if (FS_Get(&functionalStateCtl, FS_GUN)) {
		GUN_ON();
	} else {
		GUN_OFF();
	}
	if (FS_Get(&functionalStateCtl, FS_LASER)) {
		LASER_ON();
	} else {
		LASER_OFF();
	}
	if (FS_Get(&functionalStateCtl, FS_SPINNER)) {
		SPINNER_ON();
	} else {
		SPINNER_OFF();
	}
}

static void ChassisMotorCmd()
{
	CM_CMD(mecanumVelocityCtl.w1, mecanumVelocityCtl.w2, mecanumVelocityCtl.w3, mecanumVelocityCtl.w4);
}

static void PantiltMotorCmd()
{
	GM_CMD(pantiltVelocityCtl.y, pantiltVelocityCtl.p);
}

void Act_Init()
{
	GUN_OFF();
	LASER_OFF();
	SPINNER_OFF();
	CM_CMD(0, 0, 0, 0);
	GM_CMD(0, 0);
}

void Act_Proc()
{
	PeriphsStateCmd();
	ChassisMotorCmd();
	PantiltMotorCmd();
}
