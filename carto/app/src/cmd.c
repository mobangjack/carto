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
 
#include "cmd.h"

/***************************************/
/*               Command               */
/***************************************/

void Cmd_Init()
{
	DBUS_Reset(&dbus);
}

void Cmd_Proc()
{
	GetInputMode(&dbus.rc);
	if (inputMode == INPUT_MODE_RC)
	{
		RCI_Cmd(&dbus.rc);
	}
	else if (inputMode == INPUT_MODE_HC)
	{
		HCI_Cmd(&dbus.hc);
	}
	else if (inputMode == INPUT_MODE_AC)
	{
		//ACI_Cmd();
	}
	Mecanum_Decompose(&mecanum, (float*)&chassisVelocityRef, (float*)&mecanumVelocityRef);
}

void Rcv_Cmd(uint8_t* buf)
{
	Wdg_Feed(WDG_IDX_RC);
	DBUS_Dec(buf, &dbus);
}


