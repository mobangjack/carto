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

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C" {
#endif

// Standard c libraries
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Application Support Packages
#include "asp.h"

// Board Supported Packages
#include "bsp.h"

// Services
#include "srv.h"

// Applications
#include "can.h"
#include "cfg.h"
#include "cmd.h"
#include "com.h"
#include "ctl.h"
#include "hci.h"
#include "odo.h"
#include "rci.h"
#include "wdg.h"

// commonly used macros
#define PI 3.1415926f
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)
#define SQR(x) ((x)*(x))

void App_Init(void);
uint8_t App_Cfg(void);

extern Cfg_t cfg;

extern AHRS_t ahrs;
extern Mecanum_t mecanum;
extern PID_t GMYAnglePID;
extern PID_t GMYSpeedPID;
extern PID_t GMPAnglePID;
extern PID_t GMPSpeedPID;
extern PID_t CM1AnglePID;
extern PID_t CM1SpeedPID;
extern PID_t CM2AnglePID;
extern PID_t CM2SpeedPID;
extern PID_t CM3AnglePID;
extern PID_t CM3SpeedPID;
extern PID_t CM4AnglePID;
extern PID_t CM4SpeedPID;

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */
