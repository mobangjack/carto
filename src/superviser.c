#include "main.h"
//add priority to error
uint32_t lost_counter[LOST_COUNTER_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint32_t LOST_COUNTER[LOST_COUNTER_NUM] = {10, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};

uint32_t lost_err = 0xFFFFFFFF;

void LostCounterFeed(uint8_t index)
{
	lost_counter[index] = 0;
}

void LostCounterCount(uint8_t index)
{
	lost_counter[index]++;
}

uint8_t LostCounterCheckOverflow(uint8_t index)
{
	return lost_counter[index] >= LOST_COUNTER[index];
}

void SuperviseTask()
{
	int i = 0;
	for(i = 0; i < LOST_COUNTER_NUM; i++)
	{
		if(LostCounterCheckOverflow(i) == 0)    //4ms*50 = 200ms error check time
		{
			LostCounterCount(i);  			    //add 1 everytime
			lost_err &= ~(uint32_t)(1 << i);    //clear the error bit
		}
		else
		{
			lost_err |= (uint32_t)(1 << i);    //set the error bit
		}
	}
}

uint32_t GetLostError(uint32_t err_code)
{
	return lost_err&err_code;
}

uint8_t IsLostErrorSet(uint32_t err_code)
{
	return GetLostError(err_code) == err_code;
}

uint8_t IsSeriousError()
{
	return 0;
}

