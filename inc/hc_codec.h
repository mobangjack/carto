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

#ifndef __HC_CODEC_H__
#define __HC_CODEC_H__

#include <stdint.h>

/* ----------------------- PC Mouse Value Definition------------------------------ */
#define MOUSE_SPEED_MIN            	 ((int16_t)-32768 )
#define MOUSE_SPEED_MID              ((int16_t)0      )
#define MOUSE_SPEED_MAX		         ((int16_t)32767  )
#define MOUSE_BUTTON_UP         	 ((uint8_t)0      )
#define MOUSE_BUTTON_DOWN            ((uint8_t)1      )
/* ----------------------- PC Key Value Definition-------------------------------- */
#define KEY_W         			 ((uint8_t)0x01<<0)
#define KEY_S         			 ((uint8_t)0x01<<1)
#define KEY_A         			 ((uint8_t)0x01<<2)
#define KEY_D         			 ((uint8_t)0x01<<3)
#define KEY_SHIFT     		     ((uint8_t)0x01<<4)
#define KEY_CTRL      		     ((uint8_t)0x01<<5)
#define KEY_Q         		     ((uint8_t)0x01<<6)
#define KEY_E         			 ((uint8_t)0x01<<7)

#define MOUSE_BUTTON_NUMBER 2
#define MOUSE_BUTTON_INDEX_LEFT 0
#define MOUSE_BUTTON_INDEX_RIGHT 1

typedef struct Mouse
{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t b[MOUSE_BUTTON_NUMBER];
}Mouse_t; // Mouse control domain

typedef struct Key
{
	uint16_t val;
}Key_t; // Key control domain

typedef struct Res
{
	uint16_t val;
}Res_t; // Reserved control bits

typedef struct
{
	Mouse_t mouse;
	Key_t key;
	Res_t res;
}HC_t; // Host Control frame structure


void HC_ENC(HC_t* hc, uint8_t* buf);
void HC_DEC(HC_t* hc, uint8_t* buf);

#endif /* __HC_CODEC_H__ */
