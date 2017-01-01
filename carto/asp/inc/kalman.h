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

#ifndef __KALMAN_H__
#define __KALMAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
  /* Critical Section */
  float q;    // process noise
  float r;    // measurement noise
  /* Critical Section */
  
  float e;    // estimation
  float d;    // difference
  float k;    // inverse of kalman gain
  float p;    // fused variance
}Kalman_t;

Kalman_t* KalmanCreate();
void KalmanReset(Kalman_t* kalman);
void KalmanSetE(Kalman_t* kalman, float e);
void KalmanSetD(Kalman_t* kalman, float d);
void KalmanSetQ(Kalman_t* kalman, float q);
void KalmanSetR(Kalman_t* kalman, float r);
float KalmanFilter(Kalman_t* kalman, float x);
void KalmanDestroy(Kalman_t* kalman);

#ifdef __cplusplus
}
#endif

#endif

