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
 
#ifndef __MECANUM_H__
#define __MECANUM_H__

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

typedef struct
{
	float lx;
	float ly;
	float l;

	float r1;
	float r2;
	float r;

	float cx;
	float cy;
	float cz;

	float x;
	float y;
	float z;

	float w1;
	float w2;
	float w3;
	float w4;
}Mecanum_t;

void Mecanum_Config(Mecanum_t* mecanum, float lx, float ly, float r1, float r2);
void Mecanum_Synthesis(Mecanum_t* mecanum);
void Mecanum_Decompose(Mecanum_t* mecanum);

#endif
