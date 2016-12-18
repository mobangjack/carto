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
 
#ifndef __PWM_H__
#define __PWM_H__

#define PWM1 TIM5->CCR1
#define PWM2 TIM5->CCR2

#define PWM_H 1800
#define PWM_L 1000

#define SET_PWM(pwm) (PWM1=PWM2=pwm)
#define PWM_ON() SET_PWM(PWM_H)
#define PWM_OFF() SET_PWM(PWM_L)

void PWM_Config(void);

#endif

