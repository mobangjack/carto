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

/**************************************/
/*            Application             */
/**************************************/

static uint32_t sync_tick = 0;

void App_Init()
{
	sync_tick = 0;

	Act_Init();
	Can_Init();
	Cfg_Init();
	Ini_Init();
	Clk_Init();
	Sci_Init();
	Com_Init();
	Ctl_Init();
	Ins_Init();
	Odo_Init();
	Pwr_Init();
	Wdg_Init();
}

void App_Sync()
{
	Wdg_Proc();
	Sci_Proc();
	Com_Proc();
	Ins_Proc();
	Odo_Proc();
	Ctl_Proc();
	Act_Proc();
	Pwr_Proc();
}

void App_Proc()
{
	sync_tick++;
}
