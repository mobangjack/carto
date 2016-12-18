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

#ifndef __RC_CMD_H__
#define __RC_CMD_H__

typedef uint8_t SwitchAction_t;

#define GET_SWITCG_ACTION(last,this) (((last)<<2)|(this))
#define SWITCH_ACTION_3TO1 GET_SWITCG_ACTION(3, 1)
#define SWITCH_ACTION_1TO3 GET_SWITCG_ACTION(1, 3)
#define SWITCH_ACTION_3TO2 GET_SWITCG_ACTION(3, 2)
#define SWITCH_ACTION_2TO3 GET_SWITCG_ACTION(2, 3)
#define SWITCH_ACTION_NONE 0

extern SwitchAction_t switch1Action;
extern SwitchAction_t switch2Action;

#endif /* __RC_CMD_H__ */
