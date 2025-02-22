/********************************************************************
 *@file        flash_eeprom.h
 *@author      Woody      QQ：2490006131
 *@version     V1.0
 *@date        2016-10-14
 *@brief       EEPROM初始化以及读取/写入数据
 *******************************************************************/
#ifndef __FLASH_EEPROM_H
#define __FLASH_EEPROM_H

#include "stm8s.h"

void Init_EEPROM(void);  
void WriteEEPROM(u32 data);
u32 FLASH_Read_Word(u32 Address_temp);



#endif



