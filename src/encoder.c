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
	static const uint32_t encoder_mod = ENCODER_VAL_MAX + 1;
	static const float encoder_value_to_angle_coeff = 0.0439453125f;
	static const float angle_to_radian_coeff = 0.01745329252f;
	
	if(encoder->cnt < ENCODER_INIT_FRAME_COUNT)
	{
		encoder->bias = value;
		encoder->cnt++;
	}
	encoder->last_value = encoder->value;
	encoder->value = value;
	encoder->diff = encoder->value - encoder->last_value;
	if(encoder->diff > ENCODER_DIFF_MAX)
	{
		encoder->rate_raw = encoder->diff - encoder_mod;
		encoder->round--;
	}
	else if(encoder->diff < -ENCODER_DIFF_MAX)
	{
		encoder->rate_raw = encoder->diff + encoder_mod;
		encoder->round++;
	}
	else
	{
		encoder->rate_raw = encoder->diff;
	}
	encoder->scale = (encoder->value - encoder->bias) + encoder->round * encoder_mod;
	encoder->angle = encoder->scale * encoder_value_to_angle_coeff;
	encoder->radian = encoder->angle * angle_to_radian_coeff;
	if(encoder->rate_cnt < ENCODER_RATE_BUF_SIZE)
	{
		encoder->rate_buf[encoder->rate_ptr++] = encoder->rate_raw;
		encoder->rate_sum += encoder->rate_raw;
		encoder->rate_cnt++;
	}
	else
	{
		if(encoder->rate_ptr == encoder->rate_cnt)
		{
			encoder->rate_ptr = 0;
		}
		encoder->rate_sum += (encoder->rate_raw - encoder->rate_buf[encoder->rate_ptr]);
		encoder->rate_buf[encoder->rate_ptr++] = encoder->rate_raw;
	}
	encoder->rate = encoder->rate_sum / encoder->rate_cnt;
	encoder->rate_angle = encoder->rate * 43.9453125f;
	encoder->rate_radian = encoder->rate_angle * angle_to_radian_coeff;
}

uint8_t Encoder_IsOk(Encoder* encoder)
{
	return encoder->cnt == ENCODER_INIT_FRAME_COUNT;
}

void Encoder_Reset(Encoder* encoder)
{
	memset(encoder, 0, sizeof(Encoder));
}

