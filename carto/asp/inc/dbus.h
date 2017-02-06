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
 
#ifndef __DBUS_H__
#define __DBUS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* ----------------------- RC Channel Value Definition---------------------------- */
#define CH_MIN              	 ((uint16_t)364   )
#define CH_MID	           	 	 ((uint16_t)1024  )
#define CH_MAX              	 ((uint16_t)1684  )
/* ----------------------- RC Switch Value Definition----------------------------- */
#define SW_UP                    ((uint8_t)1      )
#define SW_MID                	 ((uint8_t)3      )
#define SW_DOWN                  ((uint8_t)2      )

#define CH_CNT   4
#define SW_CNT   2
#define SW_IDX_L 0
#define SW_IDX_R 1

typedef struct
{
	uint16_t ch[CH_CNT];
	uint8_t  sw[SW_CNT];
}RC_t; // remote control frame structure

/* ----------------------- PC Mouse Value Definition------------------------------ */
#define MOUSE_SPEED_MIN          ((int16_t)-32768 )
#define MOUSE_SPEED_MID          ((int16_t)0      )
#define MOUSE_SPEED_MAX		     ((int16_t)32767  )
#define MOUSE_BTN_UP         	 ((uint8_t)0      )
#define MOUSE_BTN_DOWN           ((uint8_t)1      )
/* ----------------------- PC Key Value Definition-------------------------------- */
#define KEY_W         			 ((uint8_t)0x01<<0)
#define KEY_S         			 ((uint8_t)0x01<<1)
#define KEY_A         			 ((uint8_t)0x01<<2)
#define KEY_D         			 ((uint8_t)0x01<<3)
#define KEY_SHIFT     		     ((uint8_t)0x01<<4)
#define KEY_CTRL      		     ((uint8_t)0x01<<5)
#define KEY_Q         		     ((uint8_t)0x01<<6)
#define KEY_E         			 ((uint8_t)0x01<<7)

#define KEY_UP   0
#define KEY_DOWN 1

#define MOUSE_BTN_CNT   2
#define MOUSE_BTN_IDX_L 0
#define MOUSE_BTN_IDX_R 1

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t b[MOUSE_BTN_CNT];
}Mouse_t; // Mouse control domain

typedef struct
{
	uint16_t val;
}Key_t; // Key control domain

typedef struct
{
	uint16_t val;
}Res_t; // Reserved control bits

typedef struct
{
	Mouse_t mouse;
	Key_t key;
	Res_t res;
}HC_t; // Host Control frame structure

/* ----------------------- DBUS = RC + HC -------------------------------- */
#define HC_OFFSET 6

typedef struct
{
	RC_t rc;
	HC_t hc;
}DBUS_t; // Robomasters DT7 receiver DBUS frame structure

void RC_Enc(RC_t* rc, uint8_t* buf);
void RC_Dec(RC_t* rc, uint8_t* buf);
void RC_Reset(RC_t* rc);
void HC_Enc(HC_t* hc, uint8_t* buf);
void HC_Dec(HC_t* hc, uint8_t* buf);
void HC_Reset(HC_t* hc);
void DBUS_Enc(DBUS_t* dbus, uint8_t* buf);
void DBUS_Dec(DBUS_t* dbus, uint8_t* buf);
void DBUS_Reset(DBUS_t* dbus);

#ifdef __cplusplus
}
#endif

#endif
