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

#include "rc_codec.h"

void RC_ENC(RC_t* rc, uint8_t* buf)
{
	buf[0] = rc->ch0 & 0xff;
	buf[1] = (rc->ch1 << 3) | (rc->ch0 >> 8);
	buf[2] = (rc->ch2 << 6) | (rc->ch1 >> 5);
	buf[3] = rc->ch2;
	buf[4] = (rc->ch3 << 1) | (rc->ch2 >> 10);
	buf[5] = (rc->sw[SWITCH_INDEX_RIGHT] << 6) |
			 (rc->sw[SWITCH_INDEX_LEFT] << 4) |
			 (rc->ch3 >> 7);
}

void RC_DEC(RC_t* rc, uint8_t* buf)
{
	rc->ch0 = (buf[0] | (buf[1] << 8)) & 0x07ff;                //!< Channel 0
	rc->ch1 = ((buf[1] >> 3) | (buf[2] << 5)) & 0x07ff;         //!< Channel 1
	rc->ch2 = ((buf[2] >> 6) | (buf[3] << 2) |                  //!< Channel 2
		(buf[4] << 10)) & 0x07ff;
	rc->ch3 = ((buf[4] >> 1) | (buf[5] << 7)) & 0x07ff;         //!< Channel 3
	rc->sw[SWITCH_INDEX_LEFT] = ((buf[5] >> 4) & 0x000c) >> 2;   //!< Switch left
	rc->sw[SWITCH_INDEX_RIGHT] = ((buf[5] >> 4) & 0x0003);       //!< Switch right
}
