/*************** (C) COPYRIGHT  四维拓智 ***************************************
 * 文件名  ：main.c
 * 描述    ：工程模板    
 * 库版本  ：V1.1.0
 * 开发人员：Woody QQ：2490006131
 * 修改时间：2016-10-14
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "sysclock.h"
#include "delay.h"
#include "flash_eeprom.h"
#include "led.h"
#include "key.h"
#include "adc.h"
/*  Defines -----------------------------------------------------------*/
/*  Variate ---------------------------------------------------------*/
u32 ADC_Class = 0;
u8 flag_eeprom = 0;
u32 ADC_EEPROM;
u8 direction = 0;
u32 adctempF = 0;

int main(void)
{    
  /* 系统时钟初始化 */
  SystemClock_Init(); 
  delay_init(16);
  Init_EEPROM();
  key_init();
  Adc_Init_volume();  // 传感器AD
  LED_Init();
  enableInterrupts(); 	/* 开启总中断 */
  
  while (1)
  {
     if(flag_eeprom == 0)
     {
        flag_eeprom=1;
        ADC_EEPROM=FLASH_Read_Word(0x00004000);  
        delay_ms(10);
     }
     delay_ms(2);
     key_scan();    
     Adc_Init();
     adctempF = ADC1_GetConversionValue();
     if(adctempF < 512)
     {
        GPIO_WriteLow(GPIOA, GPIO_PIN_2);
        direction=1;
     }else direction = 0;
     
     Adc_Init_volume();  
     ADC_Class = ADC1_GetConversionValue();
    if(ADC_Class >= ADC_EEPROM)
    {
       if(direction == 0)
       {
          GPIO_WriteHigh(GPIOA, GPIO_PIN_2);
       }
    }else  
       if(direction ==0)
       {
          GPIO_WriteLow(GPIOA, GPIO_PIN_2);
       }
  }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
    
  }
}
#endif






