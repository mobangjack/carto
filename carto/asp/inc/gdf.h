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

#ifndef __GDF_H__
#define __GDF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
	float mean;
	float var; // variance

	float* dat; // data buffer
	uint32_t n; // data buffer length
	uint32_t i; // data index

	float avg; // average
	float var; // variance
}Gdf_t;

void GdfInit(Gdf_t* gdf, float* dat, uint32_t n);
void GdfUpdate(Gdf_t* gdf, float val);
void GdfReset(Gdf_t* gdf);

#ifdef __cplusplus
}
#endif

#endif
