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

#include "est.h"

Est_t* Est_Create(uint32_t gaussN, float precision, float kalmanQ)
{
	Est_t* est = (Est_t*)malloc(sizeof(Est_t));
	if (est == NULL) {
		return NULL;
	}
	est->gauss = GaussCreate(gaussN);
	if (est->gauss == NULL) {
		free(est);
		est = NULL;
		return NULL;
	}
	est->kalman = KalmanCreate();
	if (est->kalman == NULL) {
		GaussDestroy(est->gauss);
		free(est);
		est = NULL;
		return NULL;
	}
	KalmanSetQ(est->kalman, kalmanQ);
	est->gaussN = gaussN;
	est->precision = precision;
	est->gauss->delta_mse = precision;
	est->ini_flag = 0;
	return est;
}

float Est_Proc(Est_t* est, float v)
{
	if (est->gauss->delta_mse >= est->precision) {
		if (est->gauss == NULL) {
			est->gauss = GaussCreate(est->gaussN);
		}
		GaussProc(est->gauss, v);
		est->value = est->gauss->mean;
		est->delta = est->gauss->delta_mean;
		return est->value;
	} else if (!est->ini_flag) {
		KalmanSetR(est->kalman, est->gauss->mse);
		KalmanSetE(est->kalman, est->gauss->mean);
		KalmanSetD(est->kalman, est->gauss->diff);
		if (est->gauss != NULL) {
			GaussDestroy(est->gauss);
		}
		est->ini_flag = 1;
		est->value = est->gauss->mean;
		est->delta = est->gauss->delta_mean;
		return est->value;
	} else {
		KalmanFilter(est->kalman, v);
		est->value = est->kalman->e;
		est->delta = est->kalman->d;
		return est->value;
	}
}

uint8_t Est_Ok(Est_t* est)
{
	return est->ini_flag;
}

void Est_Reset(Est_t* est)
{
	if (est != NULL) {
		if (est->gauss != NULL) {
			GaussReset(est->gauss);
		}
		if (est->kalman != NULL) {
			KalmanReset(est->kalman);
		}
		est->ini_flag = 0;
	}
}

void Est_Destroy(Est_t* est)
{
	if (est != NULL) {
		GaussDestroy(est->gauss);
		KalmanDestroy(est->kalman);
		free(est);
		est = NULL;
	}
}

