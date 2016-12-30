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
 
#include "esc.h"

void ESC_Process(ESC_t* esc, uint8_t* data)
{
	esc->angle_fdb = (data[0]<<8) | data[1];
	esc->current_fdb = (data[2]<<8) | data[3];
	esc->current_ref = (data[4]<<8) | data[5];
}
