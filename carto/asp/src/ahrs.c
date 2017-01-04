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

#include "ahrs.h"

#define PI 3.1415926f

float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void AHRS_Update(AHRS_t* ahrs, float* buf, float halfT) {
    float norm;
    float ax_norm, ay_norm, az_norm;
    float gx_norm, gy_norm, gz_norm;
    float mx_norm, my_norm, mz_norm;
    float hx, hy, hz, bx, bz;
    float vx, vy, vz, wx, wy, wz;
    float ex, ey, ez;
    float tempq0, tempq1, tempq2, tempq3;

    float q0q0 = ahrs->q[0]*ahrs->q[0];
    float q0q1 = ahrs->q[0]*ahrs->q[1];
    float q0q2 = ahrs->q[0]*ahrs->q[2];
    float q0q3 = ahrs->q[0]*ahrs->q[3];
    float q1q1 = ahrs->q[1]*ahrs->q[1];
    float q1q2 = ahrs->q[1]*ahrs->q[2];
    float q1q3 = ahrs->q[1]*ahrs->q[3];
    float q2q2 = ahrs->q[2]*ahrs->q[2];
    float q2q3 = ahrs->q[2]*ahrs->q[3];
    float q3q3 = ahrs->q[3]*ahrs->q[3];

    norm = invSqrt(ahrs->ax*ahrs->ax + ahrs->ay*ahrs->ay + ahrs->az*ahrs->az);
    ax_norm = ahrs->ax * norm;
    ay_norm = ahrs->ay * norm;
    az_norm = ahrs->az * norm;

    norm = invSqrt(ahrs->mx*ahrs->mx + ahrs->my*ahrs->my + ahrs->mz*ahrs->mz);
    mx_norm = ahrs->mx * norm;
    my_norm = ahrs->my * norm;
    mz_norm = ahrs->mz * norm;

    // compute reference direction of flux
    hx = 2.0f*mx_norm*(0.5f - q2q2 - q3q3) + 2.0f*my_norm*(q1q2 - q0q3) + 2.0f*mz_norm*(q1q3 + q0q2);
    hy = 2.0f*mx_norm*(q1q2 + q0q3) + 2.0f*my_norm*(0.5f - q1q1 - q3q3) + 2.0f*mz_norm*(q2q3 - q0q1);
    hz = 2.0f*mx_norm*(q1q3 - q0q2) + 2.0f*my_norm*(q2q3 + q0q1) + 2.0f*mz_norm*(0.5f - q1q1 - q2q2);
    bx = sqrt((hx*hx) + (hy*hy));
    bz = hz;

    // estimated direction of gravity and flux (v and w)
    vx = 2.0f*(q1q3 - q0q2);
    vy = 2.0f*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;
    wx = 2.0f*bx*(0.5f - q2q2 - q3q3) + 2.0f*bz*(q1q3 - q0q2);
    wy = 2.0f*bx*(q1q2 - q0q3) + 2.0f*bz*(q0q1 + q2q3);
    wz = 2.0f*bx*(q0q2 + q1q3) + 2.0f*bz*(0.5f - q1q1 - q2q2);

    // error is sum of cross product between reference direction of fields and direction measured by sensors
    ex = (ay_norm*vz - az_norm*vy) + (my_norm*wz - mz_norm*wy);
    ey = (az_norm*vx - ax_norm*vz) + (mz_norm*wx - mx_norm*wz);
    ez = (ax_norm*vy - ay_norm*vx) + (mx_norm*wy - my_norm*wx);

    if(ex != 0.0f && ey != 0.0f && ez != 0.0f)
    {
    	ahrs->exInt = ahrs->exInt + ex * ahrs->ki * halfT;
    	ahrs->eyInt = ahrs->eyInt + ey * ahrs->ki * halfT;
    	ahrs->ezInt = ahrs->ezInt + ez * ahrs->ki * halfT;
        gx_norm = gx_norm + ahrs->kp*ex + ahrs->exInt;
        gy_norm = gy_norm + ahrs->kp*ey + ahrs->eyInt;
        gz_norm = gz_norm + ahrs->kp*ez + ahrs->ezInt;
    }

    tempq0 = ahrs->q[0] + (-ahrs->q[1]*gx_norm - ahrs->q[2]*gy_norm - ahrs->q[3]*gz_norm)*halfT;
    tempq1 = ahrs->q[1] + ( ahrs->q[0]*gx_norm + ahrs->q[2]*gz_norm - ahrs->q[3]*gy_norm)*halfT;
    tempq2 = ahrs->q[2] + ( ahrs->q[0]*gy_norm - ahrs->q[1]*gz_norm + ahrs->q[3]*gx_norm)*halfT;
    tempq3 = ahrs->q[3] + ( ahrs->q[0]*gz_norm + ahrs->q[1]*gy_norm - ahrs->q[2]*gx_norm)*halfT;

    norm = invSqrt(tempq0*tempq0 + tempq1*tempq1 + tempq2*tempq2 + tempq3*tempq3);
    ahrs->q[0] = tempq0 * norm;
    ahrs->q[1] = tempq1 * norm;
    ahrs->q[2] = tempq2 * norm;
    ahrs->q[3] = tempq3 * norm;
}

void AHRS_Q2YPR(float* q, float* ypr)
{
    ypr[0] = -atan2(2*q[1]*q[2] + 2*q[0]*q[3], -2*q[2]*q[2] - 2*q[3]*q[3] + 1)*180/PI; // yaw    -pi----pi
    ypr[1] = -asin(-2*q[1]*q[3] + 2*q[0]*q[2])*180/PI; // pitch    -pi/2    --- pi/2
    ypr[2] = atan2(2*q[2]*q[3] + 2*q[0]*q[1], -2*q[1]*q[1] - 2*q[2]*q[2] + 1)*180/PI; // roll  -pi-----pi
}
