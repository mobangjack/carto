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

#include "aci.h"

/********************************************/
/*          Auto Control Interface          */
/********************************************/

void Aci_Init()
{

}

void Aci_Proc(CBUS_t* cbus)
{
	functionalStateRef   = cbus->f;
	pantiltPositionRef.y = cbus->p * ACI_GIM_POS_RECIP;
	pantiltPositionRef.p = cbus->t * ACI_GIM_POS_RECIP;
	chassisVelocityRef.x = cbus->x * ACI_CHA_SPD_RECIP;
	chassisVelocityRef.y = cbus->y * ACI_CHA_SPD_RECIP;
	chassisVelocityRef.z = cbus->z * ACI_CHA_SPD_RECIP;
}
