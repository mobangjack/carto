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
 
#include "main.h"

InputMode_t inputMode = INPUT_MODE_NO;

void GetInputMode(DBUS_t* dbus)
{
	inputMode = dbus->rc.s2;
}

void DBUS_CMD(DBUS_t* dbus)
{
	GetInputMode(dbus);
	if(inputMode == INPUT_MODE_RC)
	{
		RC_CMD(&dbus->rc);
	}
	else if(inputMode == INPUT_MODE_HC)
	{
		HC_CMD(&dbus->hc);
	}
}
