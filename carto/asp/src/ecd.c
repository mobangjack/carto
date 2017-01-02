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

#include "ecd.h"

#define GAUSS_N 500u
#define GAUSS_BYPASS_N 500u
#define GAUSS_PROC_CNT (GAUSS_N + GAUSS_BYPASS_N)

#define ECD_Q 0.1f

Gauss_t* gauss[MOTOR_NUM];
Kalman_t* kalman[MOTOR_NUM];
uint8_t global_ini_flag[MOTOR_NUM];
uint8_t kalman_ini_flag[MOTOR_NUM];
uint32_t gauss_proc_cnt[MOTOR_NUM];

void ECD_PROC(uint8_t i, int16_t v)
{
	if (!global_ini_flag[i]) {
		gauss[i] = GaussCreate(GAUSS_N);
		kalman[i] = KalmanCreate();
		global_ini_flag[i] = 1;
	} else if (gauss_proc_cnt[i] < GAUSS_PROC_CNT) {
		GaussFilter(gauss[i], v);
	} else if (!kalman_ini_flag[i]) {
		KalmanSetQ(kalman[i], ECD_Q);
		KalmanSetR(kalman[i], gauss[i]->mse);
		KalmanSetE(kalman[i], gauss[i]->mean);
		KalmanSetD(kalman[i], gauss[i]->diff);
	} else {
		KalmanFilter(kalman[i], v);
	}
}
