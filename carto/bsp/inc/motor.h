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
 
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "platform.h"

#define MOTOR_CAN CAN2
#define EC60_CMD(c201,c202,c203,c204) EC60_Cmd(MOTOR_CAN,c201,c202,c203,c204)
#define RM6025_CMD(c205,c206) RM6025_Cmd(MOTOR_CAN,c205,c206)

#define EC60_CMD_CAN_MSG_ID   0x200
#define RM6025_CMD_CAN_MSG_ID 0x1ff

void EC60_Cmd(CAN_TypeDef *CANx, int16_t c201, int16_t c202, int16_t c203, int16_t c204);
void RM6025_Cmd(CAN_TypeDef *CANx, int16_t c205, int16_t c206);

#endif
