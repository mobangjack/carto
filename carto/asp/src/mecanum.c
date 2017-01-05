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

#define MECANUM_LX 0.160f  // Mecanum wheel span
#define MECANUM_LY 0.160f  // Mecanum wheel base
#define MECANUM_R1 0.009f  // Mecanum wheel radius 1
#define MECANUM_R2 0.070f  // Mecanum wheel radius 2

#define MECANUM_L (MECANUM_LX + MECANUM_LY)
#define MECANUM_R (MECANUM_R1 + MECANUM_R2)
#define COEFF_X   (MECANUM_R1 / 4.0f)
#define COEFF_Y   (MECANUM_R2 / 4.0f)
#define COEFF_Z   (MECANUM_R / 4.0f / MECANUM_L)

void Mecanum_Config(Mecanum_t* mecanum, float lx, float ly, float r1, float r2)
{
	mecanum->lx = lx;
	mecanum->ly = ly;
	mecanum->r1 = r1;
	mecanum->r1 = r2;

	mecanum->l = mecanum->lx + mecanum->ly;
	mecanum->r = mecanum->r1 + mecanum->r2;

	mecanum->cx = mecanum->r1 / 4.0f;
	mecanum->cy = mecanum->r2 / 4.0f;
	mecanum->cz = mecanum->r / 4.0f / mecanum->l;
}

uint8_t Mecanum_Ok(Mecanum_t* mecanum)
{
	return mecanum->lx > 0 && mecanum->ly > 0 && mecanum->l > 0 &&
		   mecanum->r1 > 0 && mecanum->r2 > 0 && mecanum->r > 0 &&
		   mecanum->cx > 0 && mecanum->cy > 0 && mecanum->cz > 0;
}

void Mecanum_Synthesis(Mecanum_t* mecanum)
{
	mecanum->x = ( mecanum->w1 + mecanum->w2 - mecanum->w3 - mecanum->w4) * mecanum->cx;
	mecanum->y = (-mecanum->w1 + mecanum->w2 + mecanum->w3 - mecanum->w4) * mecanum->cy;
	mecanum->z = ( mecanum->w1 + mecanum->w2 + mecanum->w3 + mecanum->w4) * mecanum->cz;
}

void Mecanum_Decompose(Mecanum_t* mecanum)
{
	mecanum->w1 = ( mecanum->x - mecanum->z + mecanum->z * mecanum->l) / mecanum->r;
	mecanum->w2 = ( mecanum->x + mecanum->y + mecanum->z * mecanum->l) / mecanum->r;
	mecanum->w3 = (-mecanum->x + mecanum->y + mecanum->z * mecanum->l) / mecanum->r;
	mecanum->w4 = (-mecanum->x - mecanum->y + mecanum->z * mecanum->l) / mecanum->r;
}
