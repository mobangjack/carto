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

#include "cali.h"

void Cali_Get(Cali_t* cali)
{
	Flash_Read(CALI_FLASH_DATA_START_ADDRESS, (u8*)cali, sizeof(Cali_t));
}

uint8_t Cali_Set(Cali_t* cali)
{
	return Flash_Write(CALI_FLASH_DATA_START_ADDRESS, (u8*)cali, sizeof(Cali_t));
}
