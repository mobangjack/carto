#ifndef __KALMAN_H__
#define __KALMAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Kalman_t
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

