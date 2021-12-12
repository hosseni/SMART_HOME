/*
 * ADC_Int.h
 *
 *  Created on: Nov 6, 2020
 *      Author: Mohamed
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_
#include "Dio_Reg.h"
#include "Dio_Int.h"
#include "Std_Types.h"
#include "Utilites.h"

#define ADMUX  *((volatile u8*) 0x27)
#define ADCSRA *((volatile u8*) 0x26)
#define ADCL   *((volatile u8*) 0x24) //this will take ADCL, ADCH
#define ADCH   *((volatile u8*) 0x25)

void ADC_Init(void);
u16 ADC_Read(void);


#endif /* ADC_INT_H_ */
