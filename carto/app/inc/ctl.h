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
 
#ifndef __CTL_H__
#define __CTL_H__

#include <stdint.h>

#include "app.h"
#include "cmd.h"
#include "can.h"
#include "gun.h"
#include "laser.h"
#include "spinner.h"
#include "mecanum.h"
#include "odo.h"
#include "pid.h"
#include "ramp.h"
#include "motor.h"
#include "wdg.h"

typedef uint8_t WorkingState_t;

#define WORKING_STATE_PREPARE 0x00
#define WORKING_STATE_NORMAL  0x01
#define WORKING_STATE_STOP    0x02

typedef struct
{
	float m1;
	float m2;
	float m3;
	float m4;
}ChassisCurrent_t;

typedef struct
{
	float y;
	float p;
}PantiltCurrent_t;

#define CM_RAMP_DEFAULT RAMP(5000)
#define GM_RAMP_DEFAULT RAMP(5000)

//void Control(void);

extern WorkingState_t workingState;
extern ChassisCurrent_t chassisCurrent;
extern PantiltCurrent_t pantiltCurrent;

#endif

