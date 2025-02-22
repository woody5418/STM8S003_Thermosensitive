/********************************************************************
 *@file        key.c
 *@author      Woody      QQ：2490006131
 *@version     V1.0
 *@date        2016-10-14
 *@brief       KEY初始化以及扫描函数
 *******************************************************************/
#include "flash_eeprom.h"
#include "delay.h"
#include "key.h"
#include "adc.h"
#include "led.h"

u8 number=0;
/*******************************************************************************
 * 函数名：key_init
 * 描述  ：配置key的初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 ******************************************************************************/
void key_init(void)
{
  //定义KEY的管脚为输入模式
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT);
}
/*******************************************************************************
 * 函数名：key_scan
 * 描述  ：配置key扫描函数,写EEPROM
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 ******************************************************************************/
void key_scan(void)
{
    if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_7) == 0)
    {
        delay_ms(20);
        if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_7) == 0)
        {
          ADC_EEPROM = ADC_Class; 
          WriteEEPROM(ADC_EEPROM);
          //number=1;
        }
    }
}

