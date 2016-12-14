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

#ifndef __FLASH_H__
#define __FLASH_H__

#include "stm32f4xx.h" 

#define STM32_FLASH_BASE 0x08000000 	//stm32 flash base address
 
#define ADDR_FLASH_SECTOR_0     ((u32)0x08000000) 	// 16 k
#define ADDR_FLASH_SECTOR_1     ((u32)0x08004000) 	// 16 k
#define ADDR_FLASH_SECTOR_2     ((u32)0x08008000) 	// 16 k
#define ADDR_FLASH_SECTOR_3     ((u32)0x0800C000) 	// 16 k
#define ADDR_FLASH_SECTOR_4     ((u32)0x08010000) 	// 64 k
#define ADDR_FLASH_SECTOR_5     ((u32)0x08020000) 	// 128 k
#define ADDR_FLASH_SECTOR_6     ((u32)0x08040000) 	// 128 k
#define ADDR_FLASH_SECTOR_7     ((u32)0x08060000) 	// 128 k
#define ADDR_FLASH_SECTOR_8     ((u32)0x08080000) 	// 128 k
#define ADDR_FLASH_SECTOR_9     ((u32)0x080A0000) 	// 128 k
#define ADDR_FLASH_SECTOR_10    ((u32)0x080C0000) 	// 128 k
#define ADDR_FLASH_SECTOR_11    ((u32)0x080E0000) 	// 128 k

#define FLASH_READ_BYTE(addr) (*(vu8*)addr)

#define FLASH_GET_SECTOR(addr) ( \
	(addr < ADDR_FLASH_SECTOR_1) ? FLASH_Sector_0 : \
	(addr < ADDR_FLASH_SECTOR_2) ? FLASH_Sector_1 : \
	(addr < ADDR_FLASH_SECTOR_3) ? FLASH_Sector_2 : \
	(addr < ADDR_FLASH_SECTOR_4) ? FLASH_Sector_3 : \
	(addr < ADDR_FLASH_SECTOR_5) ? FLASH_Sector_4 : \
	(addr < ADDR_FLASH_SECTOR_6) ? FLASH_Sector_5 : \
	(addr < ADDR_FLASH_SECTOR_7) ? FLASH_Sector_6 : \
	(addr < ADDR_FLASH_SECTOR_8) ? FLASH_Sector_7 : \
	(addr < ADDR_FLASH_SECTOR_9) ? FLASH_Sector_8 : \
	(addr < ADDR_FLASH_SECTOR_10) ? FLASH_Sector_9 : \
	(addr < ADDR_FLASH_SECTOR_11) ? FLASH_Sector_10 : \
	FLASH_Sector_11 \
)

void Flash_Read(u32 addr, u8 *buf, u32 bytes);
u8 Flash_Write(u32 addr, u8 *buf, u32 bytes);

#endif


