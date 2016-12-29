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

#ifndef __SUPERVISER_H__
#define __SUPERVISER_H__

#include <stdint.h>

#define LOST_COUNTER_NUM                             11u

#define LOST_COUNTER_INDEX_RC                        0u    
#define LOST_COUNTER_INDEX_CALI            		     1u
#define LOST_COUNTER_INDEX_API            		     2u    
#define LOST_COUNTER_INDEX_IMU                       3u  
#define LOST_COUNTER_INDEX_ZGYRO                     4u  
#define LOST_COUNTER_INDEX_MOTOR1                    5u   
#define LOST_COUNTER_INDEX_MOTOR2                    6u   
#define LOST_COUNTER_INDEX_MOTOR3                    7u    
#define LOST_COUNTER_INDEX_MOTOR4                    8u    
#define LOST_COUNTER_INDEX_MOTOR5                    9u   
#define LOST_COUNTER_INDEX_MOTOR6                    10u  


#define LOST_ERROR_RC									(1<<LOST_COUNTER_INDEX_RC)		  
#define LOST_ERROR_CALI									(1<<LOST_COUNTER_INDEX_CALI)
#define LOST_ERROR_API									(1<<LOST_COUNTER_INDEX_API)		  
#define LOST_ERROR_IMU									(1<<LOST_COUNTER_INDEX_IMU)		   
#define LOST_ERROR_ZGYRO								(1<<LOST_COUNTER_INDEX_ZGYRO)		
#define LOST_ERROR_MOTOR1								(1<<LOST_COUNTER_INDEX_MOTOR1)	
#define LOST_ERROR_MOTOR2								(1<<LOST_COUNTER_INDEX_MOTOR2)	
#define LOST_ERROR_MOTOR3								(1<<LOST_COUNTER_INDEX_MOTOR3)	
#define LOST_ERROR_MOTOR4								(1<<LOST_COUNTER_INDEX_MOTOR4)	
#define LOST_ERROR_MOTOR5								(1<<LOST_COUNTER_INDEX_MOTOR5)	
#define LOST_ERROR_MOTOR6								(1<<LOST_COUNTER_INDEX_MOTOR6)	

#define LOST_ERROR_ALL ( \
		LOST_ERROR_RC | \
		LOST_ERROR_CALI | \
		LOST_ERROR_API | \
		LOST_ERROR_IMU | \
		LOST_ERROR_ZGYRO | \
		LOST_ERROR_MOTOR1 | \
		LOST_ERROR_MOTOR2 | \
		LOST_ERROR_MOTOR3 | \
		LOST_ERROR_MOTOR4 | \
		LOST_ERROR_MOTOR5 | \
		LOST_ERROR_MOTOR6 \
		)

#define LOST_COUNTER_NUM_RC   	    10
#define LOST_COUNTER_NUM_CALI 		50
#define LOST_COUNTER_NUM_API  		50
#define LOST_COUNTER_NUM_IMU  		50
#define LOST_COUNTER_NUM_ZGYRO 		50
#define LOST_COUNTER_NUM_MOTOR 		50

void Supervise(void);
void Superviser_Feed(uint8_t i);
uint32_t Superviser_GetErrorCode(void);
uint8_t Superviser_IsErrorSet(uint32_t mask);

extern const uint32_t LOST_COUNTER[LOST_COUNTER_NUM] = {
		LOST_COUNTER_NUM_RC,
		LOST_COUNTER_NUM_CALI,
		LOST_COUNTER_NUM_API,
		LOST_COUNTER_NUM_IMU,
		LOST_COUNTER_NUM_ZGYRO,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
		LOST_COUNTER_NUM_MOTOR,
};

#endif

