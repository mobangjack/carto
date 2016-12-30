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
 
#ifndef __ESC_H__
#define __ESC_H__

/*
 * For EC60 & RM6025 Electronic Speed Controller
 */

#include "platform.h"

#define ESC1_FEEDBACK_CAN_MSG_ID  0x201
#define ESC2_FEEDBACK_CAN_MSG_ID  0x202
#define ESC3_FEEDBACK_CAN_MSG_ID  0x203
#define ESC4_FEEDBACK_CAN_MSG_ID  0x204
#define ESC5_FEEDBACK_CAN_MSG_ID  0x205
#define ESC6_FEEDBACK_CAN_MSG_ID  0x206

typedef struct ESC_t
{
	uint16_t angle_fdb;    // angle feedback
	uint16_t current_fdb;  // electric current feedback
	uint16_t current_ref;  // electric current reference
}ESC_t;

void ESC_Process(ESC_t* esc, uint8_t* data);

#endif
