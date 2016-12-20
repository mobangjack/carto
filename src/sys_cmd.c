/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
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

#include "app.h"

FunctionalState_t functionalState;
ChassisSpeedRef_t chassisSpeedRef;
GimbalsSpeedRef_t gimbalsSpeedRef;

FunctionalState_t GET_FS(FunctionalState_t _functionalState)
{
	return functionalState & _functionalState;
}

void SET_FS(FunctionalState_t _functionalState)
{
	functionalState |= _functionalState;
}

void CLR_FS(FunctionalState_t _functionalState)
{
	functionalState &= ~_functionalState;
}

void TOG_FS(FunctionalState_t _functionalState)
{
	GET_FS(_functionalState) ? CLR_FS(_functionalState) : SET_FS(_functionalState);
}

void SET_CS(float vx, float vy, float vz)
{
	chassisSpeedRef.x = vx;
	chassisSpeedRef.y = vy;
	chassisSpeedRef.z = vz;
}

void SET_GS(float pitch, float yaw)
{
	gimbalsSpeedRef.p = pitch;
	gimbalsSpeedRef.y = yaw;
}



