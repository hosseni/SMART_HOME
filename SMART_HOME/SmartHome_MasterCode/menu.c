
#include "menu.h"

extern volatile u16 session_counter;
extern          u8  timeout_flag;


u8 ComparePass( u8* pass1, u8* pass2, u8 size){
	u8 counter = 0;
	u8 ret_value = TRUE;

	while (counter < size )
	{
		if (*(pass1+counter) != *(pass2+counter))
		{
			ret_value = FALSE;
			break;
		}
		counter++;
	}
	return ret_value;
}
void menuOption(u8 SelectedRoom, u8 LoginMode){

	u8 StatusCode  = 0;
	u8 TurnOnCode  = 0;
	u8 TurnOffCode = 0;
	u8 response    = DEFAULT_ACK;
	u8 key_pressed  = NOT_PRESSED;

	do
	{
		LCD_CLEAR_SCREEN();
		switch(SelectedRoom)
		{

		case ROOM1_MENU:
			 StatusCode  =  ROOM1_STATUS;
			 TurnOffCode =  ROOM1_TURN_OFF;
			 TurnOnCode  =  ROOM1_TURN_ON;

			LCD_WriteString("ROOM1 S:");
			break;
		case ROOM2_MENU:
			 StatusCode  =  ROOM2_STATUS;
			 TurnOffCode =  ROOM2_TURN_OFF;
			 TurnOnCode  =  ROOM2_TURN_ON;

			LCD_WriteString("ROOM2 S:");
			break;

		case ROOM3_MENU:
			 StatusCode  =  ROOM3_STATUS;
			 TurnOffCode =  ROOM3_TURN_OFF;
			 TurnOnCode  =  ROOM3_TURN_ON;

			LCD_WriteString("ROOM3 S:");
			break;

		case ROOM4_MENU :
			 StatusCode  =  ROOM4_STATUS;
			 TurnOffCode =  ROOM4_TURN_OFF;
			 TurnOnCode  =  ROOM4_TURN_ON;

			LCD_WriteString("ROOM4 S:");
			break;

		case TV_MENU :
			 StatusCode  =  TV_STATUS;
			 TurnOffCode =  TV_TURN_OFF;
			 TurnOnCode  =  TV_TURN_ON;

			LCD_WriteString("TV S:");
			break;

		case AIRCOND_CTRL_MENU:
			 StatusCode  =  AIR_COND_STATUS;
			 TurnOffCode =  AIR_COND_TURN_OFF;
			 TurnOnCode  =  AIR_COND_TURN_ON;

			LCD_WriteString("Air Cond. S:");
			break;

		}

		SPI_SEND_RECEIVE_DATA(StatusCode);
		_delay_ms(100);
		response = SPI_SEND_RECEIVE_DATA(DEMAND_RESPONSE);

		if (response == ON_STATUS)
		{
			LCD_WriteString("ON");
		}
		else
		{
			LCD_WriteString("OFF");
		}

		LCD_MOVE_CURSOR(2,1);

		LCD_WriteString("1-On 2-Off 0-RET");

		key_pressed =GetKeyPressed(LoginMode);
		_delay_ms(100);

		if (key_pressed == '1')
		{
			SPI_SEND_RECEIVE_DATA(TurnOnCode);
		}
		else if (key_pressed == '2')
		{
			SPI_SEND_RECEIVE_DATA(TurnOffCode);

		}
		else if (key_pressed != NOT_PRESSED && key_pressed != '0')
							{
								LCD_CLEAR_SCREEN();
								LCD_WriteString("wrong input");
								_delay_ms(500);
							}

	}
	while ( ( (key_pressed < '0') || (key_pressed > '2') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out


}


u8 GetKeyPressed(u8 LoginMode){

	u8 key_pressed = NOT_PRESSED;

	while (key_pressed == NOT_PRESSED)
	{
		if ((session_counter >= ADMIN_TIMEOUT &&LoginMode == ADMIN) || (session_counter >= GUEST_TIMEOUT && LoginMode == GUEST) )
		{
			timeout_flag =TRUE;
			break;
		}
		key_pressed = Keypad_GetPressedKey();
	}
	return key_pressed;
}


