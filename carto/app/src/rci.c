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
 
#include "rci.h"

/**********************************************/
/*          Remote Control Interface          */
/**********************************************/

SwitchState_t switchStates[SW_CNT];
SwitchEvent_t switchEvents[SW_CNT];

static void GetSwitchStates(RC_t* rc)
{
	static uint8_t last_state[SW_CNT];
	static uint32_t cnt[SW_CNT];
	uint8_t* this_state = rc->sw;
	uint32_t i = 0;
	for (; i < SW_CNT; i++) {
		if (this_state[i] == last_state[i]) {
			if (cnt[i] < SWITCH_STATE_CHANGE_DELAY) {
				cnt[i]++;
			} else {
				switchStates[i] = this_state[i];
			}
		} else {
			cnt[i] = 0;
		}
		last_state[i] = this_state[i];
	}
}

static void GetSwitchEvents(RC_t* rc)
{
	static SwitchState_t last_state[SW_CNT];
	uint32_t i = 0;
	for (; i < SW_CNT; i++) {
		switchEvents[i] = GET_SWITCH_EVENT(last_state[i], switchStates[i]);
		last_state[i] = switchStates[i];
	}
}

static void GetFunctionalStateRef(RC_t* rc)
{
	GetSwitchStates(rc);
	GetSwitchEvents(rc);
	switch (switchEvents[SW_IDX_L]) {
		case SWITCH_EVENT_3TO1:
			FS_Tog(&functionalStateRef, FS_GUN);
			if (FS_Get(&functionalStateRef, FS_GUN)) {
				FS_Set(&functionalStateRef, FS_LASER);
			}
			break;
		case SWITCH_EVENT_3TO2:
			if (FS_Get(&functionalStateRef, FS_GUN)) {
				FS_Tog(&functionalStateRef, FS_SPINNER);
			} else {
				FS_Clr(&functionalStateRef, FS_SPINNER);
			}
			break;
		default:
			break;
	}
}

#define MAP(val,min1,max1,min2,max2) ((val-min1)*(max2-min2)/(max1-min1)+min2)

static void GetChassisVelocityRef(RC_t* rc)
{
	chassisVelocityRef.x = MAP(rc->ch[0], CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
	chassisVelocityRef.y = MAP(rc->ch[1], CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
	chassisVelocityRef.z = MAP(rc->ch[2], CH_MIN, CH_MAX, -CHASSIS_SPEED_MAX, CHASSIS_SPEED_MAX);
}

static void GetPantiltVelocityRef(RC_t* rc)
{
	pantiltVelocityRef.y = MAP(rc->ch[2], CH_MIN, CH_MAX, -PANTILT_SPEED_MAX, PANTILT_SPEED_MAX);
	pantiltVelocityRef.p = MAP(rc->ch[3], CH_MIN, CH_MAX, -PANTILT_SPEED_MAX, PANTILT_SPEED_MAX);
}

void RCI_Cmd(RC_t* rc)
{
	GetFunctionalStateRef(rc);
	GetChassisVelocityRef(rc);
	GetPantiltVelocityRef(rc);
}

