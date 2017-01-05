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

#include "kalman.h"

#define SQR(x) (x*x)

Kalman_t* KalmanCreate()
{
	Kalman_t* kalman = (Kalman_t*)malloc(sizeof(Kalman_t));
	if (kalman == NULL) return NULL;
	KalmanReset(kalman);
	return kalman;
}

void KalmanReset(Kalman_t* kalman)
{
	kalman->e = 0;
	kalman->d = 0;
	kalman->k = 0;
	kalman->p = 0;
}

void KalmanSetE(Kalman_t* kalman, float e)
{
	kalman->e = e;
}

void KalmanSetD(Kalman_t* kalman, float d)
{
	kalman->d = d;
}

void KalmanSetQ(Kalman_t* kalman, float q)
{
	kalman->q = q;
}

void KalmanSetR(Kalman_t* kalman, float r)
{
	kalman->r = r;
}

float KalmanFilter(Kalman_t* kalman, float x) {
	// update
	kalman->e += kalman->d;
	kalman->p += kalman->q;
	// fusion
	kalman->k = (1 + kalman->r / kalman->p); // inverse of kalman gain
	kalman->d = (x - kalman->e) / kalman->k; // delta mean
	kalman->e += kalman->d;                  // fused mean
	kalman->p -= SQR(kalman->p) / kalman->k; // fused variance
	return kalman->e;
}

void KalmanDestroy(Kalman_t* kalman)
{
	if (kalman != NULL) {
		free(kalman);
		kalman = NULL;
	}
}

