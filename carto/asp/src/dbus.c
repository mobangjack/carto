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
 
#include "dbus.h"

void RC_Enc(const RC_t* rc, uint8_t* buf)
{
	buf[0] = rc->ch[0] & 0xff;
	buf[1] = (rc->ch[1] << 3) | (rc->ch[0] >> 8);
	buf[2] = (rc->ch[2] << 6) | (rc->ch[1] >> 5);
	buf[3] = rc->ch[2];
	buf[4] = (rc->ch[3] << 1) | (rc->ch[2] >> 10);
	buf[5] = (rc->sw[SW_IDX_R] << 6) |
			 (rc->sw[SW_IDX_L] << 4) |
			 (rc->ch[3] >> 7);
}

void RC_Dec(RC_t* rc, const uint8_t* buf)
{
	rc->ch[0] = (buf[0] | (buf[1] << 8)) & 0x07ff;         //!< Channel 0
	rc->ch[1] = ((buf[1] >> 3) | (buf[2] << 5)) & 0x07ff;  //!< Channel 1
	rc->ch[2] = ((buf[2] >> 6) | (buf[3] << 2) |           //!< Channel 2
		(buf[4] << 10)) & 0x07ff;
	rc->ch[3] = ((buf[4] >> 1) | (buf[5] << 7)) & 0x07ff;  //!< Channel 3
	rc->sw[SW_IDX_L] = ((buf[5] >> 4) & 0x000c) >> 2;    //!< Switch left
	rc->sw[SW_IDX_R] = ((buf[5] >> 4) & 0x0003);         //!< Switch right
}

void RC_Reset(RC_t* rc)
{
	uint8_t i = 0;
	for (; i < CH_CNT; i++) {
		rc->ch[i] = CH_MID;
	}
	for (i = 0; i < SW_CNT; i++) {
		rc->sw[i] = SW_MID;
	}
}

void HC_Enc(const HC_t* hc, uint8_t* buf)
{
	buf[0] = hc->mouse.x;
	buf[1] = hc->mouse.x >> 8;
	buf[2] = hc->mouse.y;
	buf[3] = hc->mouse.y >> 8;
	buf[4] = hc->mouse.z;
	buf[5] = hc->mouse.z >> 8;
	buf[6] = hc->mouse.b[MOUSE_BTN_IDX_L];
	buf[7] = hc->mouse.b[MOUSE_BTN_IDX_R];
	buf[8] = hc->key.val;
	buf[9] = hc->key.val >> 8;
	buf[10] = hc->res.val;
	buf[11] = hc->res.val >> 8;
}

void HC_Dec(HC_t* hc, const uint8_t* buf)
{
	hc->mouse.x = buf[0] | (buf[1] << 8);   //!< Mouse X axis
	hc->mouse.y = buf[2] | (buf[3] << 8);   //!< Mouse Y axis
	hc->mouse.z = buf[4] | (buf[5] << 8);   //!< Mouse Z axis
	hc->mouse.b[MOUSE_BTN_IDX_L] = buf[6];  //!< Mouse Left Is Press ?
	hc->mouse.b[MOUSE_BTN_IDX_R] = buf[7];  //!< Mouse Right Is Press ?
	hc->key.val = buf[8] | (buf[9] << 8);   //!< KeyBoard value
	hc->res.val = buf[10] | (buf[11] << 8); //!< Reserve
}

void HC_Reset(HC_t* hc)
{

	uint8_t i = 0;
	for (; i < MOUSE_BTN_CNT; i++) {
		hc->mouse.b[i] = MOUSE_BTN_UP;
	}
	hc->key.val = 0;
	hc->res.val = 0;
}

void DBUS_Enc(const DBUS_t* dbus, uint8_t* buf)
{
	RC_Enc(&dbus->rc, buf);
	HC_Enc(&dbus->hc, buf + HC_OFFSET);
}

void DBUS_Dec(DBUS_t* dbus, const uint8_t* buf)
{
	RC_Dec(buf, &dbus->rc);
	HC_Dec(buf + HC_OFFSET, &dbus->hc);
}

void DBUS_Reset(DBUS_t* dbus)
{
	RC_Reset(&dbus->rc);
	HC_Reset(&dbus->hc);
}

