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

void AHRS_Update(float* buf, float* q, float* e, float kp, float ki, float dt) {
    float norm;
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    float hx, hy, hz, bx, bz;
    float vx, vy, vz, wx, wy, wz;
    float ex, ey, ez, halfT;
    float tempq0, tempq1, tempq2, tempq3;

    float q0q0 = q[0]*q[0];
    float q0q1 = q[0]*q[1];
    float q0q2 = q[0]*q[2];
    float q0q3 = q[0]*q[3];
    float q1q1 = q[1]*q[1];
    float q1q2 = q[1]*q[2];
    float q1q3 = q[1]*q[3];
    float q2q2 = q[2]*q[2];
    float q2q3 = q[2]*q[3];
    float q3q3 = q[3]*q[3];

    ax = buf[0];
	ay = buf[1];
	az = buf[2];
    gx = buf[3] * PI/180;
    gy = buf[4] * PI/180;
    gz = buf[5] * PI/180;
    mx = buf[6];
    my = buf[7];
    mz = buf[8];

    halfT = dt / 2;

    norm = invSqrt(ax*ax + ay*ay + az*az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

    norm = invSqrt(mx*mx + my*my + mz*mz);
    mx = mx * norm;
    my = my * norm;
    mz = mz * norm;

    // compute reference direction of flux
    hx = 2.0f*mx*(0.5f - q2q2 - q3q3) + 2.0f*my*(q1q2 - q0q3) + 2.0f*mz*(q1q3 + q0q2);
    hy = 2.0f*mx*(q1q2 + q0q3) + 2.0f*my*(0.5f - q1q1 - q3q3) + 2.0f*mz*(q2q3 - q0q1);
    hz = 2.0f*mx*(q1q3 - q0q2) + 2.0f*my*(q2q3 + q0q1) + 2.0f*mz*(0.5f - q1q1 - q2q2);
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
    ex = (ay*vz - az*vy) + (my*wz - mz*wy);
    ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
    ez = (ax*vy - ay*vx) + (mx*wy - my*wx);

    if(ex != 0.0f && ey != 0.0f && ez != 0.0f)
    {
        e[0] = e[0] + ex * ki * halfT;
        e[1] = e[1] + ey * ki * halfT;
        e[2] = e[2] + ez * ki * halfT;
        gx = gx + kp*ex + e[0];
        gy = gy + kp*ey + e[1];
        gz = gz + kp*ez + e[2];
    }

    tempq0 = q[0] + (-q[1]*gx - q[2]*gy - q[3]*gz)*halfT;
    tempq1 = q[1] + ( q[0]*gx + q[2]*gz - q[3]*gy)*halfT;
    tempq2 = q[2] + ( q[0]*gy - q[1]*gz + q[3]*gx)*halfT;
    tempq3 = q[3] + ( q[0]*gz + q[1]*gy - q[2]*gx)*halfT;

    norm = invSqrt(tempq0*tempq0 + tempq1*tempq1 + tempq2*tempq2 + tempq3*tempq3);
    q[0] = tempq0 * norm;
    q[1] = tempq1 * norm;
    q[2] = tempq2 * norm;
    q[3] = tempq3 * norm;
}

void AHRS_Q2YPR(float* q, float* ypr)
{
    ypr[0] = -atan2(2*q[1]*q[2] + 2*q[0]*q[3], -2*q[2]*q[2] - 2*q[3]*q[3] + 1)*180/PI; // yaw    -pi----pi
    ypr[1] = -asin(-2*q[1]*q[3] + 2*q[0]*q[2])*180/PI; // pitch    -pi/2    --- pi/2
    ypr[2] = atan2(2*q[2]*q[3] + 2*q[0]*q[1], -2*q[1]*q[1] - 2*q[2]*q[2] + 1)*180/PI; // roll  -pi-----pi
}
