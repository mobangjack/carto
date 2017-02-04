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

/**************************************/
/*            Application             */
/**************************************/

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
#include "aci.h" // Auto Control Interface
#include "act.h" // Action (Depend on BSP)
#include "can.h" // Controller Area Network
#include "cfg.h" // System Configuration
#include "clk.h" // System Clock Source
#include "cmd.h" // System Command
#include "com.h" // Communication
#include "ctl.h" // Logic Controller
#include "dev.h" // Device Manager
#include "hci.h" // Host Control Interface
#include "ins.h" // Inertial Navigation System
#include "odo.h" // Odometer (Sensor Message Feedback)
#include "pwr.h" // Power Management
#include "rci.h" // Remote Control Interface
#include "wdg.h" // Watch Dog

// commonly used macros
#define PI 3.1415926f
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)
#define LIMIT(X,M) ((X)=(X)>(M)?(M):((X)<-(M)?-(M):(X)))
#define SQR(x) ((x)*(x))

typedef uint32_t PeriphsState_t; // Peripherals Functional State

#define FS_LED_GREEN      	(((uint32_t)0x00000001)<<0)
#define FS_LED_RED        	(((uint32_t)0x00000002)<<1)
#define FS_GUN      		(((uint32_t)0x00000003)<<2)
#define FS_LASER    		(((uint32_t)0x00000004)<<3)
#define FS_SPINNER  		(((uint32_t)0x00000005)<<4)
#define FS_ALL      		((uint32_t)0xFFFFFFFF)
#define FS_NON       		((uint32_t)0x00000000)

typedef struct
{
	float y;
	float p;
}PantiltState_t;

typedef struct
{
	float x;
	float y;
	float z;
}ChassisState_t;

typedef struct
{
	float w1;
	float w2;
	float w3;
	float w4;
}MecanumState_t;

void App_Init();
void App_Sync();

float map(float val, float min1, float max1, float min2, float max2);
PeriphsState_t FS_Get(const PeriphsState_t* fs, PeriphsState_t msk);
void FS_Set(PeriphsState_t* fs, PeriphsState_t msk);
void FS_Clr(PeriphsState_t* fs, PeriphsState_t msk);
void FS_Tog(PeriphsState_t* fs, PeriphsState_t msk);
void CS_Set(ChassisState_t* cs, float x, float y, float z);
void GS_Set(PantiltState_t* gs, float y, float p);
void MS_Set(MecanumState_t* ms, float w1, float w2, float w3, float w4);

extern Mecanum_t mecanum;

#ifdef __cplusplus
}
#endif

#endif
