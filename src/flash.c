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

#include "flash.h"

void Flash_Read(u32 addr, u8 *buf, u32 size)
{
	memcpy(buf, (void*)addr, size);
}

u8 Flash_Write(u32 addr, u8 *buf, u32 bytes)
{
	#define BREAK_IF_NOT_COMPLETE(status) {if(status != FLASH_COMPLETE) break;}

	// flash status
    FLASH_Status status = FLASH_COMPLETE;
    // end address
    u32 endaddr = addr+bytes;
    // start sector
    u32 start_sector = FLASH_GET_SECTOR(addr);
    // end sector
    u32 end_sector = FLASH_GET_SECTOR(endaddr);

    // validate flash address
    if(addr < STM32_FLASH_BASE) return 0;

    // unlock flash
	FLASH_Unlock();
	// disable data cache
    FLASH_DataCacheCmd(DISABLE);

    // erase sector before written
	if(addr < 0X1FFF0000)
	{
		int i = 0;
		for(i = start_sector; i <= end_sector; i += 8)
		{
			status = FLASH_EraseSector(i, VoltageRange_3);
			BREAK_IF_NOT_COMPLETE(status);
		}
	}

	// program flash byte by byte
	if(status == FLASH_COMPLETE)
	{
		while(addr < endaddr)
		{
			status = FLASH_ProgramByte(addr++,*buf++);
			BREAK_IF_NOT_COMPLETE(status);
		}
	}

	// enable data cache
    FLASH_DataCacheCmd(ENABLE);
    // lock flash
    FLASH_Lock();

    return status == FLASH_COMPLETE;
} 




