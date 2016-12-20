#include "main.h"

void Cali_Get(Cali_t* cali)
{
	memcpy(cali, (void*)CALI_FLASH_DATA_START_ADDRESS, sizeof(Cali_t));
}

uint8_t Cali_Set(Cali_t* cali)
{
	return Flash_Write(CALI_FLASH_DATA_START_ADDRESS, cali, sizeof(Cali_t));
}
