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

void Receiver_Callback(u8* dbuf)
{
	DBUS_t dbus;
	DBUS_DEC(&dbus, dbuf);
	DBUS_CMD(&dbus);
}

void CAN1_RX_Callback(CanRxMsg* canRxMsg)
{

}

void CAN2_RX_Callback(CanRxMsg* canRxMsg)
{

}

void MPU6050_INT_Callback()
{

}

void TTY_RX_Callback(u8 data)
{

}
