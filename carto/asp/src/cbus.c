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

#include "cbus.h"

#define L8B(x) (x&0xff)
#define H8B(x) ((x>>8)&0xff)

#define BIG_END

#ifdef BIG_END
#define FIRST_BYTE(x) L8B(x)
#define SECND_BYTE(x) H8B(x)
#else
#define FIRST_BYTE(x) H8B(x)
#define SECND_BYTE(x) L8B(x)
#endif

void CBUS_Enc(CBUS_t* cbus, uint8_t* cbuf)
{
	cbuf[0] = FIRST_BYTE(CBUS_HEADER);
	cbuf[1] = SECND_BYTE(CBUS_HEADER);
	/*
	cbuf[2] = FIRST_BYTE(cbus->x);
	cbuf[3] = SECND_BYTE(cbus->x);
	cbuf[4] = FIRST_BYTE(cbus->y);
	cbuf[5] = SECND_BYTE(cbus->y);
	cbuf[6] = FIRST_BYTE(cbus->z);
	cbuf[7] = SECND_BYTE(cbus->z);
	cbuf[8] = FIRST_BYTE(cbus->p);
	cbuf[9] = SECND_BYTE(cbus->p);
	cbuf[10] = FIRST_BYTE(cbus->t);
	cbuf[11] = SECND_BYTE(cbus->t);
	cbuf[12] = FIRST_BYTE(cbus->f);
	cbuf[13] = SECND_BYTE(cbus->f);
	*/
	memcpy(cbuf, cbus, sizeof(CBUS_t));
	CRC16Append(cbuf, CBUS_FRAME_LEN, CBUS_CRC);
}

uint8_t CBUS_Dec(CBUS_t* cbus, uint8_t* cbuf)
{
	uint16_t header = *((uint16_t*)(cbuf));
	if (header != CBUS_HEADER) {
		return 0;
	}
	if (!CRC16Check(cbuf, CBUS_FRAME_LEN, CBUS_CRC)) {
		return 0;
	}
	memcpy(cbus, cbuf, sizeof(CBUS_t));
	return 1;
}
