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

#ifndef __CAN_H__
#define __CAN_H__

#include "platform.h"

#include "esc.h"
#include "zgyro.h"
#include "motor.h"
#include "superviser.h"

#define ZGYRO_CAN_PORT CAN1
#define MOTOR_CAN_PORT CAN2

#define ZGYRO_RST() ZGyro_RST(ZGYRO_CAN_PORT)
#define CM_CMD(M1,M2,M3,M4) EC60_CMD(MOTOR_CAN_PORT,M1,M2,M3,M4)
#define GM_CMD(M5,M6) RM6025_CMD(MOTOR_CAN_PORT,M5,M6)

void CAN_RX_Callback(CanRxMsg* canRxMsg);

extern float ZGyroAngle;

extern ESC ESC1;
extern ESC ESC2;
extern ESC ESC3;
extern ESC ESC4;
extern ESC ESC5;
extern ESC ESC6;

#endif /* __CAN_H__ */
