#include "Dio_Int.h"
#include "LED.h"
#include "ADC_Int.h"
#include "TIMER0_CTC_INIT.h"
#include "APP_SLAVE_MACROS.h"
#include "STD_MESSAGE.h"

volatile u16 required_temperature =24;
volatile u16 temp_sensor_reading = 0;
volatile u8 counter = 0;
volatile u8 last_air_conditioning_value = AIR_CONDTIONING_OFF;


int main(void)
{

   ADC_Init();
   timer0_initializeCTC();
   SPI_INIT_SLAVE();

   LED_Init(AIR_COND_PORT,AIR_COND_PIN);
   LED_Init(TV_PORT,TV_PIN);
   LED_Init(ROOM1_PORT,ROOM1_PIN);
   LED_Init(ROOM2_PORT,ROOM2_PIN);
   LED_Init(ROOM3_PORT,ROOM3_PIN);
   LED_Init(ROOM4_PORT,ROOM4_PIN);

   u8 request = DEFAULT_ACK;
   u8 response = DEFAULT_ACK;

   while(1)
   {
	   request = SPI_SEND_RECEIVE_DATA(DEFAULT_ACK);

	   switch (request)
	   {
	   case ROOM1_STATUS:
		   if (LED_ReadStatus(ROOM1_PORT,ROOM1_PIN) == 0)
		   {
			   response = OFF_STATUS;
		   }
		   else if (LED_ReadStatus(ROOM1_PORT,ROOM1_PIN) == 1)
		   {
			   response = ON_STATUS;
		   }
		   else
		   {

		   }
		   SPI_SEND_RECEIVE_DATA(response);
		   break;

	   case ROOM2_STATUS:
		   if (LED_ReadStatus(ROOM2_PORT,ROOM2_PIN) == 0)
		   {
			   response = OFF_STATUS;
	   	   }
		   else if (LED_ReadStatus(ROOM2_PORT,ROOM2_PIN) == 1)
		   {
			   response = ON_STATUS;
		   }
		   else
		   {
		   }
		   SPI_SEND_RECEIVE_DATA(response);
		   break;
	   case ROOM3_STATUS:
	   	  if (LED_ReadStatus(ROOM3_PORT,ROOM3_PIN) == 0)
	   		  {
	   		   response = OFF_STATUS;
	   	   	  }
	   		  else if (LED_ReadStatus(ROOM3_PORT,ROOM3_PIN) == 1)
	   		  {
	   		   response = ON_STATUS;
	   		  }
	   		  else
	   		  {
	   		  }
	   	SPI_SEND_RECEIVE_DATA(response);
	   		  break;
	   case ROOM4_STATUS:
	   		 if (LED_ReadStatus(ROOM4_PORT,ROOM4_PIN) == 0)
	   		  {
	   		   response = OFF_STATUS;
	   	   	  }
	   		  else if (LED_ReadStatus(ROOM4_PORT,ROOM4_PIN) == 1)
	   		  {
	   		   response = ON_STATUS;
	   		  }
	   		  else
	   		  {
	   		  }
	   		SPI_SEND_RECEIVE_DATA(response);
	   		  break;
	   case AIR_COND_STATUS:
		   if (LED_ReadStatus(AIR_COND_PORT, AIR_COND_PIN) == 0)
		   {
			   response = OFF_STATUS;
		   }
		   else if (LED_ReadStatus(AIR_COND_PORT,AIR_COND_PIN) == 1)
		   {
			   response = ON_STATUS;
		   }
		   else
		   {

		   }
		   SPI_SEND_RECEIVE_DATA(response);
		   break;

	   case TV_STATUS:
		   if (LED_ReadStatus(TV_PORT,TV_PIN) == 0)
		   {
			   response = OFF_STATUS;
		   }
		   else if (LED_ReadStatus(TV_PORT, TV_PIN) == 1)
		   {
			   response = ON_STATUS;
		   }
		   else
		   {

		   }
		   SPI_SEND_RECEIVE_DATA(response);
		   break;

	   case ROOM1_TURN_ON:
		   LED_TurnOn(ROOM1_PORT,ROOM1_PIN);
		   break;
	   case ROOM2_TURN_ON:
	   		   LED_TurnOn(ROOM2_PORT,ROOM2_PIN);
	   		   break;
	   case ROOM3_TURN_ON:
	   		   LED_TurnOn(ROOM3_PORT,ROOM3_PIN);
	   		   break;
	   case ROOM4_TURN_ON:
	   		   LED_TurnOn(ROOM4_PORT,ROOM4_PIN);
	   		   break;
	   case AIR_CONDTIONING_ON:
		   timer0_initializeCTC();
		   LED_TurnOn(AIR_COND_PORT,AIR_COND_PIN);
		   break;
	   case TV_TURN_ON:
		   LED_TurnOn(TV_PORT,TV_PIN);
		   break;

	   case ROOM1_TURN_OFF:
	   		   LED_TurnOff(ROOM1_PORT,ROOM1_PIN);
	   		   break;
	   	   case ROOM2_TURN_OFF:
	   	   		   LED_TurnOff(ROOM2_PORT,ROOM2_PIN);
	   	   		   break;
	   	   case ROOM3_TURN_OFF:
	   	   		   LED_TurnOff(ROOM3_PORT,ROOM3_PIN);
	   	   		   break;
	   	   case ROOM4_TURN_OFF:
	   	   		   LED_TurnOff(ROOM4_PORT,ROOM4_PIN);
	   	   		   break;
	   	   case AIR_CONDTIONING_OFF:
	   		   timer0_stop();
	   		   LED_TurnOff(AIR_COND_PORT,AIR_COND_PIN);
	   		   break;
	   	   case TV_TURN_OFF:
	   		   LED_TurnOff(TV_PORT,TV_PIN);
	   		   break;

	   	   case SET_TEMPERATURE:
	   		   required_temperature = SPI_SEND_RECEIVE_DATA	(DEFAULT_ACK);
	   		   break;


	   }
   }
   return 0;
}


ISR(TIMER0_COMP_vect)
{
	counter++;
	if (counter>=10)
	{
		counter = 0;
		temp_sensor_reading = (0.25*ADC_Read());
		if (temp_sensor_reading>=(required_temperature+1))
		{
			LED_TurnOn(AIR_COND_PORT,AIR_COND_PIN);
			last_air_conditioning_value =AIR_CONDTIONING_ON;
		}
		else if (temp_sensor_reading <= (required_temperature-1))
		{
			LED_TurnOff(AIR_COND_PORT,AIR_COND_PIN);
			last_air_conditioning_value = AIR_CONDTIONING_OFF;
		}
		else if (temp_sensor_reading == required_temperature)
		{
			if (last_air_conditioning_value == AIR_CONDTIONING_ON)
			{
				LED_TurnOn(AIR_COND_PORT,AIR_COND_PIN);
			}
			else if(last_air_conditioning_value == AIR_CONDTIONING_OFF)
			{
				LED_TurnOff(AIR_COND_PORT,AIR_COND_PIN);
			}

		}
	}
}
