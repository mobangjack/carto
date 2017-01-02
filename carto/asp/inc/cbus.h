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

#ifndef __CBUS_H__
#define __CBUS_H__

#include "crc16.h"
#include <string.h>

#define CBUS_HEADER ((uint16_t)0x1234)
#define CBUS_CRC ((uint16_t)0x1234)
#define CBUS_FRAME_LEN 16

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
	int16_t p;
	int16_t t;
	int16_t f;
}CBUS_t;

void CBUS_ENC(CBUS_t* cbus, uint8_t* cbuf);
uint8_t CBUS_DEC(CBUS_t* cbus, uint8_t* cbuf);

#endif
