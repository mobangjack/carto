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

#include "mag.h"

void Mag_Config(Mag_t* mag, float mx_offset, float my_offset, float mz_offset)
{
	mag->mx_offset = mx_offset;
	mag->my_offset = my_offset;
	mag->mz_offset = mz_offset;
}

void Mag_Proc(Mag_t* mag, float* buf)
{
	mag->mx = buf[0];
	mag->my = buf[1];
	mag->mz = buf[2];
}

