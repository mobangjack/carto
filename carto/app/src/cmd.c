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

#include "cmd.h"

/**********************************************/
/*          System Command Interface          */
/**********************************************/

PeriphsState_t functionalStateRef;
PantiltState_t pantiltPositionRef;
ChassisState_t chassisVelocityRef;
MecanumState_t mecanumVelocityRef; // Auto-Wired

void Cmd_Init()
{
	FS_Clr(&functionalStateRef, FS_ALL);
	GS_Set(&pantiltPositionRef, 0, 0);
	CS_Set(&chassisVelocityRef, 0, 0, 0);
	MS_Set(&mecanumVelocityRef, 0, 0, 0, 0);
}

void Cmd_Proc()
{
	LIMIT(pantiltPositionRef.y,  cfg.yaw.posCfg.min, cfg.yaw.posCfg.max);
	LIMIT(pantiltPositionRef.p,  cfg.pit.posCfg.min, cfg.pit.posCfg.max);
	LIMIT(chassisVelocityRef.x, -cfg.cha.spdCfg.max, cfg.cha.spdCfg.max);
	LIMIT(chassisVelocityRef.y, -cfg.cha.spdCfg.max, cfg.cha.spdCfg.max);
	LIMIT(chassisVelocityRef.z, -cfg.cha.spdCfg.max, cfg.cha.spdCfg.max);
	Mec_Decomp((float*)&chassisVelocityRef, (float*)&mecanumVelocityRef);
}


