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

#include "sys.h"

PeriphsState_t FS_Get(PeriphsState_t* fs, PeriphsState_t msk)
{
	return (*fs) & msk;
}

void FS_Set(PeriphsState_t* fs, PeriphsState_t msk)
{
	(*fs) |= msk;
}

void FS_Clr(PeriphsState_t* fs, PeriphsState_t msk)
{
	(*fs) &= ~msk;
}

void FS_Tog(PeriphsState_t* fs, PeriphsState_t msk)
{
	FS_Get(fs, msk) ? FS_Clr(fs, msk) : FS_Set(fs, msk);
}

void CS_Set(ChassisState_t* cs, float x, float y, float z)
{
	cs->x = x;
	cs->y = y;
	cs->z = z;
}

void GS_Set(PantiltState_t* gs, float y, float p)
{
	gs->y = y;
	gs->p = p;
}

void MS_Set(MecanumState_t* ms, float w1, float w2, float w3, float w4)
{
	ms->w1 = w1;
	ms->w2 = w2;
	ms->w3 = w3;
	ms->w4 = w4;
}
