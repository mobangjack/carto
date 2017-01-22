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

#ifndef __CFG_H__
#define __CFG_H__

/*************************************/
/*     Application Configuration     */
/*************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "app.h"

#define CFG_DATA_START_ADDR 	FLASH_SECTOR_11_ADDR

//void Cfg_Load(Cfg_t* cfg);
//uint8_t Cfg_Save(Cfg_t* cfg);
//uint8_t Cfg_Reset();

void Cfg_Init();
void Cfg_Proc();

#ifdef __cplusplus
}
#endif

#endif

