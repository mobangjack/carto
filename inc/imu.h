#ifndef __IMU_H__
#define __IMU_H__

#include <math.h>
#include "mpu6050_driver.h"
#include "mpu6050_i2c.h"
#include "mpu6050_interrupt.h"
#include "mpu6050_process.h"

void Init_Quaternion(void);
void IMU_getYawPitchRoll(volatile float * ypr); //
void GetPitchYawGxGyGz(void);
extern int16_t MPU6050_FIFO[6][11];//[0]-[9]
extern int16_t HMC5883_FIFO[3][11];//[0]-[9]

extern volatile float angle[3];
extern volatile float yaw_angle,pitch_angle,roll_angle; //

#endif

