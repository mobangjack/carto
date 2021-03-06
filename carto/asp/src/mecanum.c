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
 
#include "mecanum.h"

/*******************************************/
/* Mecanum Wheel Power Transmission System */
/*******************************************/
/*              2        1                 */
/*                  |y                     */
/*                 b|___x                  */
/*               z    a                    */
/*              3        4                 */
/*                                         */
/*******************************************/

//static const float MECANUM_L = MECANUM_LX + MECANUM_LY;
//static const float MECANUM_R = MECANUM_R1 + MECANUM_R2;
//static const float COEFF_X = MECANUM_R1 / 4.0f;
//static const float COEFF_Y = MECANUM_R2 / 4.0f;
//static const float COEFF_Z = MECANUM_R / 4.0f / MECANUM_L;

#define MECANUM_L (MECANUM_LX + MECANUM_LY)
#define MECANUM_R (MECANUM_R1 + MECANUM_R2)
#define COEFF_X   (MECANUM_R1 / 4.0f)
#define COEFF_Y   (MECANUM_R2 / 4.0f)
#define COEFF_Z   (MECANUM_R / 4.0f / MECANUM_L)

void Mecanum_Synthesis(float* xyz, float* wheel)
{
	xyz[0] = ( wheel[0] + wheel[1] - wheel[2] - wheel[3]) * COEFF_X;
	xyz[1] = (-wheel[0] + wheel[1] + wheel[2] - wheel[3]) * COEFF_Y;
	xyz[2] = ( wheel[0] + wheel[1] + wheel[2] + wheel[3]) * COEFF_Z;
}

void Mecanum_Decompose(float* xyz, float* wheel)
{
	wheel[0] = ( xyz[0] - xyz[1] + xyz[2] * MECANUM_L) / MECANUM_R;
	wheel[1] = ( xyz[0] + xyz[1] + xyz[2] * MECANUM_L) / MECANUM_R;
	wheel[2] = (-xyz[0] + xyz[1] + xyz[2] * MECANUM_L) / MECANUM_R;
	wheel[3] = (-xyz[0] - xyz[1] + xyz[2] * MECANUM_L) / MECANUM_R;
}
