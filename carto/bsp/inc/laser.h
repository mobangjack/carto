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

#ifndef __LASER_H__
#define __LASER_H__

#include "stm32util.h"

#define LASER_PIN PA8
#define LASER_STATE() GPIO_READ_OUT(LASER_PIN)
#define LASER_IS_ON() (LASER_STATE() != 0)
#define LASER_IS_OFF() (LASER_STATE() == 0)
#define LASER_ON() GPIO_SET(LASER_PIN)
#define LASER_OFF() GPIO_RST(LASER_PIN)
#define LASER_TOG() GPIO_TOG(LASER_PIN)

void Laser_Config(void);

#endif /* __LASER_H__ */
