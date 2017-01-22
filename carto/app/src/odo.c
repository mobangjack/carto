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

/************************************/
/*             Odometer             */
/************************************/

static void GetFunctionalStateFdb()
{
	FunctionalState_t fs = FS_NO;
	if (LED_GREEN_IS_ON()) {
		fs |= FS_LED_GREEN;
	} else {
		fs &= ~FS_LED_GREEN;
	}
	if (LED_RED_IS_ON()) {
		fs |= FS_LED_RED;
	} else {
		fs &= ~FS_LED_RED;
	}
	if (GUN_IS_ON()) {
		fs |= FS_GUN;
	} else {
		fs &= ~FS_GUN;
	}
	if (LASER_IS_ON()) {
		fs |= FS_GUN;
	} else {
		fs &= ~FS_GUN;
	}
	if (SPINNER_IS_ON()) {
		fs |= FS_GUN;
	} else {
		fs &= ~FS_GUN;
	}
	functionalStateFdb = fs;
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

static void GetChassisPositionFdb()
{
	Mecanum_Synthesis(&mecanum, (float*)&mecanumPositionFdb, (float*)&chassisPositionFdb);
}

static void GetChassisVelocityFdb()
{
	Mecanum_Synthesis(&mecanum, (float*)&mecanumVelocityFdb, (float*)&chassisVelocityFdb);
}

void Odo_Init()
{

}

void Odo_Proc()
{
	GetFunctionalStateFdb();
	GetPantiltPositionFdb();
	GetPantiltVelocityFdb();
	GetMecanumPositionFdb();
	GetMecanumVelocityFdb();
	GetChassisPositionFdb();
	GetChassisVelocityFdb();
}

