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

void Odo_Calc(void)
{
	mecanum.w1 = encoder[0].angle;
	mecanum.w1 = encoder[1].angle;
	mecanum.w1 = encoder[2].angle;
	mecanum.w1 = encoder[3].angle;

	Mecanum_Synthesis(&mecanum);

	odo.px = mecanum.x;
	odo.py = mecanum.y;
	odo.pz = mecanum.z;

	mecanum.w1 = encoder[0].speed;
	mecanum.w1 = encoder[1].speed;
	mecanum.w1 = encoder[2].speed;
	mecanum.w1 = encoder[3].speed;

	Mecanum_Synthesis(&mecanum);

	odo.vx = mecanum.x;
	odo.vy = mecanum.y;
	odo.vz = mecanum.z;
}
