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

#include "cfg.h"

void Cfg_Load(Cfg_t* cfg)
{
	Flash_Read(CFG_DATA_START_ADDRESS, (u8*)cfg, sizeof(Cfg_t));
}

uint8_t Cfg_Save(Cfg_t* cfg)
{
	return Flash_Write(CFG_DATA_START_ADDRESS, (u8*)cfg, sizeof(Cfg_t));
}

uint8_t Cfg_Reset(void)
{
	Cfg_t cfg = CFG_DEFAULT;
	return Cfg_Save(&cfg);
}
