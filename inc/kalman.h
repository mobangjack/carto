#ifndef __KALMAN_H__
#define __KALMAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Kalman
{
  /* Critical Section */
  float q;    // process noise
  float r;    // measurement noise
  /* Critical Section */
  
  float e;    // estimation
  float d;    // difference
  float k;    // inverse of kalman gain
  float p;    // fused variance
}Kalman;

Kalman* KalmanCreate();
void KalmanReset(Kalman* kalman);
void KalmanSetE(Kalman* kalman, float e);
void KalmanSetD(Kalman* kalman, float d);
void KalmanSetQ(Kalman* kalman, float q);
void KalmanSetR(Kalman* kalman, float r);
float KalmanFilter(Kalman* kalman, float x);
void KalmanDestroy(Kalman* kalman);

#ifdef __cplusplus
}
#endif

#endif

