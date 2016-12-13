#ifndef __SUPERVISER_H__
#define __SUPERVISER_H__

#include <stdint.h>

#define LOST_COUNTER_NUM                             11u

#define LOST_COUNTER_INDEX_RC                        0u    
#define LOST_COUNTER_INDEX_KM            		     1u   
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
#define LOST_ERROR_KM									(1<<LOST_COUNTER_INDEX_KM)		  
#define LOST_ERROR_API									(1<<LOST_COUNTER_INDEX_API)		  
#define LOST_ERROR_IMU									(1<<LOST_COUNTER_INDEX_IMU)		   
#define LOST_ERROR_ZGYRO								(1<<LOST_COUNTER_INDEX_ZGYRO)		
#define LOST_ERROR_MOTOR1								(1<<LOST_COUNTER_INDEX_MOTOR1)	
#define LOST_ERROR_MOTOR2								(1<<LOST_COUNTER_INDEX_MOTOR2)	
#define LOST_ERROR_MOTOR3								(1<<LOST_COUNTER_INDEX_MOTOR3)	
#define LOST_ERROR_MOTOR4								(1<<LOST_COUNTER_INDEX_MOTOR4)	
#define LOST_ERROR_MOTOR5								(1<<LOST_COUNTER_INDEX_MOTOR5)	
#define LOST_ERROR_MOTOR6								(1<<LOST_COUNTER_INDEX_MOTOR6)	

#define LOST_ERROR_ALL (LOST_ERROR_RC|LOST_ERROR_KM|LOST_ERROR_API|LOST_ERROR_IMU|LOST_ERROR_ZGYRO|LOST_ERROR_MOTOR1|LOST_ERROR_MOTOR2|LOST_ERROR_MOTOR3|LOST_ERROR_MOTOR4|LOST_ERROR_MOTOR5|LOST_ERROR_MOTOR6)

void SuperviseTask(void);
void LostCounterFeed(uint8_t index);
void LostCounterCount(uint8_t index);
uint8_t LostCounterCheckOverflow(uint8_t index);
uint32_t GetLostError(uint32_t err_code);
uint8_t IsLostErrorSet(uint32_t err_code);
uint8_t IsSeriousError(void);

#endif

