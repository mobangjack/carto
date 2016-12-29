#include "kalman.h"

#define SQR(x) (x*x)

struct Kalman* KalmanCreate()
{
  Kalman* kalman = (Kalman*)malloc(sizeof(Kalman));
  if (kalman == NULL) return NULL;
  KalmanReset(kalman);
  return kalman;
}

void KalmanReset(struct Kalman* kalman)
{
  kalman->e = 0;
  kalman->d = 0;
  kalman->k = 0;
  kalman->p = 0;
}

void KalmanSetE(struct Kalman* kalman, float e)
{
  kalman->e = e;
}

void KalmanSetD(struct Kalman* kalman, float d)
{
  kalman->d = d;
}

void KalmanSetQ(struct Kalman* kalman, float q)
{
  kalman->q = q;
}

void KalmanSetR(struct Kalman* kalman, float r)
{
  kalman->r = r;
}

float KalmanFilter(struct Kalman* kalman, float x) {
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

void KalmanDestroy(struct Kalman* kalman)
{
  if (kalman != NULL) {
    free(kalman);
    kalman = NULL;
  }
}

