
#ifndef LED_H_
#define LED_H_
#include "Dio_Int.h"
#include "Std_Types.h"

void LED_Init(u8 portname,u8 pinnumber);

void LED_TurnOn(u8 portname,u8 pinnumber);

void LED_TurnOff(u8 portname,u8 pinnumber);


void LED_Toggle(u8 portname,u8 pinnumber);


u8 LED_ReadStatus(u8 portname,u8 pinnumber);

#endif /* LED_H_ */
