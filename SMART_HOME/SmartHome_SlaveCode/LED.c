
#include "LED.h"
#include "Utilites.h"
void LED_Init(u8 portname,u8 pinnumber)
{
	Dio_SetPinDirection(portname,pinnumber,OUTPUT);//Set the given pin in the given port as an output

}
void LED_TurnOn(u8 portname,u8 pinnumber)
{
	Dio_SetPinValue(portname,pinnumber,HIGH);//Set the given pin in the given port to one(on)
}
void LED_TurnOff(u8 portname,u8 pinnumber)
{
	Dio_SetPinValue(portname,pinnumber,LOW);//Set the given pin in the given port to zero(off)
}
void LED_Toggle(u8 portname,u8 pinnumber)
{
	Dio_TogglePinValue(portname,pinnumber);//Set the given pin in the given port to zero if it is one or set it to one if it is zero
}
u8 LED_ReadStatus(u8 portname,u8 pinnumber)
{
	return Dio_GetPinValue(portname,pinnumber);//return the current status of the given pin
}
