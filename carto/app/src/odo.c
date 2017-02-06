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
 
#include "odo.h"

/**********************************************/
/*                  Odometer                  */
/**********************************************/

PeriphsState_t functionalStateFdb;
PantiltState_t pantiltPositionFdb;
PantiltState_t pantiltVelocityFdb;
PantiltState_t pantiltCurrentsFdb;
MecanumState_t mecanumPositionFdb;
MecanumState_t mecanumVelocityFdb;
MecanumState_t mecanumCurrentsFdb;
ChassisState_t chassisPositionFdb;
ChassisState_t chassisVelocityFdb;

static void GetFunctionalStateFdb()
{
	if (LED_GREEN_IS_ON()) {
		functionalStateFdb |= FS_LED_GREEN;
	} else {
		functionalStateFdb &= ~FS_LED_GREEN;
	}
	if (LED_RED_IS_ON()) {
		functionalStateFdb |= FS_LED_RED;
	} else {
		functionalStateFdb &= ~FS_LED_RED;
	}
	if (GUN_IS_ON()) {
		functionalStateFdb |= FS_GUN;
	} else {
		functionalStateFdb &= ~FS_GUN;
	}
	if (LASER_IS_ON()) {
		functionalStateFdb |= FS_GUN;
	} else {
		functionalStateFdb &= ~FS_GUN;
	}
	if (SPINNER_IS_ON()) {
		functionalStateFdb |= FS_GUN;
	} else {
		functionalStateFdb &= ~FS_GUN;
	}
}

static void GetPantiltPositionFdb()
{
	pantiltPositionFdb.y = motor[4].angle;
	pantiltPositionFdb.p = motor[5].angle;
}

static void GetPantiltVelocityFdb()
{
	pantiltVelocityFdb.y = motor[4].rate;
	pantiltVelocityFdb.p = motor[5].rate;
}

static void GetPantiltCurrentsFdb()
{
	pantiltCurrentsFdb.y = motor[4].current_fdb;
	pantiltCurrentsFdb.p = motor[5].current_fdb;
}

static void GetMecanumPositionFdb()
{
	mecanumPositionFdb.w1 = motor[0].angle;
	mecanumPositionFdb.w2 = motor[1].angle;
	mecanumPositionFdb.w3 = motor[2].angle;
	mecanumPositionFdb.w4 = motor[3].angle;
}

static void GetMecanumVelocityFdb()
{
	mecanumVelocityFdb.w1 = motor[0].rate;
	mecanumVelocityFdb.w2 = motor[1].rate;
	mecanumVelocityFdb.w3 = motor[2].rate;
	mecanumVelocityFdb.w4 = motor[3].rate;
}

static void GetMecanumCurrentsFdb()
{
	mecanumCurrentsFdb.w1 = motor[0].current_fdb;
	mecanumCurrentsFdb.w2 = motor[1].current_fdb;
	mecanumCurrentsFdb.w3 = motor[2].current_fdb;
	mecanumCurrentsFdb.w4 = motor[3].current_fdb;
}

static void GetChassisPositionFdb()
{
	Mec_Synthe((float*)&mecanumPositionFdb, (float*)&chassisPositionFdb);
}

static void GetChassisVelocityFdb()
{
	Mec_Synthe((float*)&mecanumVelocityFdb, (float*)&chassisVelocityFdb);
}

void Odo_Init()
{
	FS_Clr(&functionalStateFdb, FS_ALL);
	GS_Set(&pantiltPositionFdb, 0, 0);
	GS_Set(&pantiltVelocityFdb, 0, 0);
	GS_Set(&pantiltCurrentsFdb, 0, 0);
	CS_Set(&chassisPositionFdb, 0, 0, 0);
	CS_Set(&chassisVelocityFdb, 0, 0, 0);
	MS_Set(&mecanumPositionFdb, 0, 0, 0, 0);
	MS_Set(&mecanumVelocityFdb, 0, 0, 0, 0);
	MS_Set(&mecanumCurrentsFdb, 0, 0, 0, 0);
}

void Odo_Proc()
{
	GetFunctionalStateFdb();
	GetPantiltPositionFdb();
	GetPantiltVelocityFdb();
	GetPantiltCurrentsFdb();
	GetMecanumPositionFdb();
	GetMecanumVelocityFdb();
	GetMecanumCurrentsFdb();
	GetChassisPositionFdb();
	GetChassisVelocityFdb();
}

