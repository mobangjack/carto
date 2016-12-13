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
 
#include "main.h"

void Encoder_Process(Encoder* encoder, uint16_t value)
{
	encoder->value = value;
	encoder->angle[0] = encoder->angle[1];
	encoder->angle[1] = ENCODER_VALUE_TO_RAD(value);
	if(encoder->init_frame_cnt < ENCODER_INIT_FRAME_CNT)
	{
		encoder->bias = encoder->angle[1];
		encoder->init_frame_cnt++;
	}
	encoder->rate = encoder->angle[1] - encoder->angle[0];
	if(encoder->rate > ENCODER_DIFF_MAX)
	{
		encoder->rate -= PI2;
		encoder->round--;
	}
	else if(encoder->rate < -ENCODER_DIFF_MAX)
	{
		encoder->rate += PI2;
		encoder->round++;
	}
	encoder->angle[1] = (encoder->angle[1] - encoder->bias) + encoder->round * PI2;
	if(encoder->rate_cnt < ENCODER_RATE_BUF_SIZE)
	{
		encoder->rate_buf[encoder->rate_ptr++] = encoder->rate;
		encoder->rate_sum += encoder->rate;
		encoder->rate_cnt++;
	}
	else
	{
		if(encoder->rate_ptr == encoder->rate_cnt)
		{
			encoder->rate_ptr = 0;
		}
		encoder->rate_sum += (encoder->rate - encoder->rate_buf[encoder->rate_ptr]);
		encoder->rate_buf[encoder->rate_ptr++] = encoder->rate;
	}
	encoder->rate = encoder->rate_sum / encoder->rate_cnt;
}

uint8_t Encoder_IsOk(Encoder* encoder)
{
	return encoder->init_frame_cnt == ENCODER_INIT_FRAME_CNT;
}

void Encoder_Reset(Encoder* encoder)
{
	memset(encoder, 0, sizeof(Encoder));
}

