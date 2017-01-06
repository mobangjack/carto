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

void Odo_Calc(Odo_t* odo)
{
	mecanum.w1 = motor[0].angle;
	mecanum.w1 = motor[1].angle;
	mecanum.w1 = motor[2].angle;
	mecanum.w1 = motor[3].angle;

	Mecanum_Synthesis(&mecanum);

	odo->px = mecanum.x;
	odo->py = mecanum.y;
	odo->pz = mecanum.z;

	mecanum.w1 = motor[0].rate;
	mecanum.w1 = motor[1].rate;
	mecanum.w1 = motor[2].rate;
	mecanum.w1 = motor[3].rate;

	Mecanum_Synthesis(&mecanum);

	odo->vx = mecanum.x;
	odo->vy = mecanum.y;
	odo->vz = mecanum.z;
}

