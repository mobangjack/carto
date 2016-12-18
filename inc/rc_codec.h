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

#ifndef __RC_CODEC_H__
#define __RC_CODEC_H__

#include <stdint.h>

/* ----------------------- RC Channel Value Definition---------------------------- */
#define CH_MIN              	 ((uint16_t)364   )
#define CH_MID           	 	 ((uint16_t)1024  )
#define CH_MAX              	 ((uint16_t)1684  )
#define CH_OFF              	 ((uint16_t)660   )
/* ----------------------- RC Switch Value Definition----------------------------- */
#define SW_UP                    ((uint8_t)1      )
#define SW_MD                    ((uint8_t)3      )
#define SW_DN                    ((uint8_t)2      )

typedef struct
{
	uint16_t ch0;
	uint16_t ch1;
	uint16_t ch2;
	uint16_t ch3;
	uint8_t  s1;
	uint8_t  s2;
}RC_t; // remote control frame structure

void RC_ENC(RC_t* rc, uint8_t* buf);
void RC_DEC(RC_t* rc, uint8_t* buf);

#endif /* __RC_CODEC_H__ */
