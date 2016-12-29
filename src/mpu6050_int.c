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

#include "mpu6050_int.h"

void MPU6050_INT_Config(void)
{
    GPIO_INT(MPU6050_INT_PIN, EXTI_Trigger_Falling);
    NVIC_Config(EXTI4_IRQn, 2, 0);
}

void EXTI4_IRQHandler(void)         //1KHz
{   
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {    
        EXTI_ClearFlag(EXTI_Line4);          
        EXTI_ClearITPendingBit(EXTI_Line4);

        MPU6050_IRQ_Handler();
    }
}






