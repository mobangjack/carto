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
 
#ifndef __INPUT_TASK_H__
#define __INPUT_TASK_H__

#include <stdint.h>

#define ON 1
#define OFF 0

#define INPUT_CHASSIS_SPEED_MAX 4.0f     //max speed: 4m/s
#define INPUT_GIMBALS_SPEED_MAX 1.0f     //max speed: 4m/s

#define INPUT_CHASSIS_SPEED_COEFF 0.01f
#define INPUT_GIMBALS_SPEED_COEFF 0.01f
#define INPUT_LR_SPEED_DIR_COEFF 1
#define INPUT_FB_SPEED_DIR_COEFF 1
#define INPUT_RT_SPEED_DIR_COEFF 1
#define INPUT_YAW_SPEED_DIR_COEFF 1
#define INPUT_PIT_SPEED_DIR_COEFF 1

#define GET_SWITCG_ACTION(lastState,thisState) (((lastState)<<2)|(thisState))
#define SWITCH_ACTION_3TO1 GET_SWITCG_ACTION(3, 1)
#define SWITCH_ACTION_1TO3 GET_SWITCG_ACTION(1, 3)
#define SWITCH_ACTION_3TO2 GET_SWITCG_ACTION(3, 2)
#define SWITCH_ACTION_2TO3 GET_SWITCG_ACTION(2, 3)
#define SWITCH_ACTION_NONE 0

#define INPUT_MODE_RC      0x03
#define INPUT_MODE_HC      0x01
#define INPUT_MODE_NO      0x02

/*******************************************/
/* Mecanum Wheel Power Transmission System */
/*******************************************/
/*              2        1                 */
/*                 y|                      */
/*                  |___                   */
/*                z    x                   */
/*              3        4                 */
/*                                         */
/*******************************************/
typedef struct
{
	float x;
	float y;
	float z;
}ChassisSpeed;

typedef struct
{
	float yaw;
	float pit;
}GimbalsSpeed;

typedef uint8_t InputMode;
typedef uint8_t SwitchAction;
typedef uint8_t FuncState;

void InputTask(void);

extern InputMode inputMode;
extern SwitchAction switch1Action;
extern SwitchAction switch2Action;
extern ChassisSpeed chassisSpeed;
extern GimbalsSpeed gimbalsSpeed;


#endif
