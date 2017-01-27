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

#include "gdf.h"

void GdfInit(Gdf_t* gdf, float* dat, uint32_t n)
{
	gdf->dat = dat;
	gdf->n = n;
	GdfReset(gdf);
}

void GdfUpdate(Gdf_t* gdf, float dat)
{
	float avg = gdf->avg;
	float del = dat - gdf->dat[gdf->i];
	gdf->avg += del / gdf->n;
	gdf->var += del * (gdf->dat[gdf->i] - avg + dat - gdf->avg) / gdf->n;
	gdf->dat[gdf->i] = dat;
	gdf->i = (gdf->i == gdf->n) ? 0 : gdf->i + 1;
}

void GdfReset(Gdf_t* gdf)
{
	gdf->i = 0;
	gdf->avg = 0;
	gdf->var = 0;
}
