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

#include "hc_codec.h"

void HC_ENC(HC_t* hc, uint8_t* buf)
{
	buf[0] = hc->mouse.x;
	buf[1] = hc->mouse.x>>8;
	buf[2] = hc->mouse.y;
	buf[3] = hc->mouse.y>>8;
	buf[4] = hc->mouse.z;
	buf[5] = hc->mouse.z>>8;
	buf[6] = hc->mouse.b[MOUSE_BUTTON_INDEX_LEFT];
	buf[7] = hc->mouse.b[MOUSE_BUTTON_INDEX_RIGHT];
	buf[8] = hc->key.val;
	buf[9] = hc->key.val>>8;
	buf[10] = hc->res.val;
	buf[11] = hc->res.val>>8;
}

void HC_DEC(HC_t* hc, uint8_t* buf)
{
	hc->mouse.x = buf[0] | (buf[1] << 8);           //!< Mouse X axis
	hc->mouse.y = buf[2] | (buf[3] << 8);           //!< Mouse Y axis
	hc->mouse.z = buf[4] | (buf[5] << 8);           //!< Mouse Z axis
	hc->mouse.b[MOUSE_BUTTON_INDEX_LEFT] = buf[6];  //!< Mouse Left Is Press ?
	hc->mouse.b[MOUSE_BUTTON_INDEX_RIGHT] = buf[7]; //!< Mouse Right Is Press ?
	hc->key.val = buf[8] | (buf[9] << 8);           //!< KeyBoard value
	hc->res.val = buf[10] | (buf[11] << 8);         //!< Reserve
}
