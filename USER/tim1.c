#include "tim1.h"
#include "led.h"
#include "key.h"
#include "delay.h"


u16  pwm_cnt=0;
u16  PWM_set=0;


void TIM1_Init(void)
{
  TIM1->PSCRH = 0x00; // 系统时钟经预分频f=fck/(PSCR+1)
  TIM1->PSCRL = 0x0F; // PSCR=16 ， f=16M/16=1MHz,每个计数周期1us
  TIM1->ARRH = 0x00; // 自动重载寄存器ARR=10us 
  TIM1->ARRL = 0x09; // 每记数10次产生一次中断，即10us
  TIM1->IER |= 0x01; // 允许更新中断
  TIM1->CR1 |= 0x01; // 计数器使能，开始计数
}


// 50us * 800 =40ms
#pragma vector=0xD     //11+2
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)//溢出中断，中文开发指南75页
{
  TIM1->SR1 = 0; //清除中断标记
  if(pwm_cnt == 800)  
  pwm_cnt=0; 
  PWM_SET();
  pwm_cnt++;
  
}

  
void PWM_SET(void)
{
  if(direction == 1)
  {
    GPIO_WriteLow(GPIOD, GPIO_PIN_4);     // 4低  3高 
    if(PWM_set >= 10)
    {
        if(pwm_cnt <= PWM_set)
        {
            GPIO_WriteHigh(GPIOD, GPIO_PIN_3);  // 高
        }else 
           if(pwm_cnt > PWM_set)     
             GPIO_WriteLow(GPIOD, GPIO_PIN_3);   // 低
    }else GPIO_WriteLow(GPIOD, GPIO_PIN_3);       // 低
  }else
    if(direction == 2)
    {
        GPIO_WriteLow(GPIOD, GPIO_PIN_3);     // 3低 4高
        if(PWM_set >= 10)
        {
            if(pwm_cnt <= PWM_set)
            {
                GPIO_WriteHigh(GPIOD, GPIO_PIN_4);  // 高
            }else
                if(pwm_cnt > PWM_set)   
                  GPIO_WriteLow(GPIOD, GPIO_PIN_4);   // 低
        }else  GPIO_WriteLow(GPIOD, GPIO_PIN_4);   // 低
    }
}












