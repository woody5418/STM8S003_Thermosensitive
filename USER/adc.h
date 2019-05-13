#ifndef __ADC_H
#define __ADC_H

#define AD_channel2   (GPIO_PIN_4)

#include "stm8s.h"


extern void Adc_Init(void);
extern void Adc_Init_volume(void);

#endif