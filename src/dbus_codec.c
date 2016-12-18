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
 
#include "dbus_codec.h"

void DBUS_ENC(DBUS_t* dbus, uint8_t* buf)
{
	RC_ENC(&dbus->rc, buf);
	HC_ENC(&dbus->hc, buf+HC_OFFSET);
}

void DBUS_DEC(DBUS_t* dbus, uint8_t* buf)
{
	RC_DEC(&dbus->rc, buf);
	HC_DEC(&dbus->hc, buf+HC_OFFSET);
}

