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

// platform
#include "platform.h"

// standard c libraries
#include <math.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "sysctl.h"

// Board Supported Packages
#include "bsp.h"

// Application Support Packages
#include "asp.h"

// services and calls
#include "cali.h"
#include "cmd.h"
#include "odom.h"
#include "superviser.h"

// commonly used macros
#define PI 3.1415926f
//#define PI2 6.2831855f
#define PIOVER180 (PI/180.f)
#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)
#define SQR(x) (x*x)

void App_Init(void);

#endif /* __APP_H__ */
