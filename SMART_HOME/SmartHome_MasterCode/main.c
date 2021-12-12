#include "main_config.h"
#include "Dio_config_Master.h"
#include "LCD_Int.h"
#include "timer0_driver.h"
#include "SPI_INIT.h"
#include "LED.h"
#include "menu.h"
#include "keypad_driver.h"
#include "EEPROM_Int.h"
#include <avr/delay.h>

volatile u16 session_counter = 0;
u8 timeout_flag = FALSE;

int main (void)
{

	u8 temperatue = 0;
	u8 temp_ones = NOT_SELECTED;
	u8 temp_tens = NOT_SELECTED;


	u8 login_mode = NO_MODE;
	u8 block_mode_flag = FALSE;
	u8 key_pressed = NOT_PRESSED;

	LED_Init(ADMIN_LED_PORT, ADMIN_LED_PIN);
	LED_Init(GUEST_LED_PORT, GUEST_LED_PIN);
	LED_Init(BLOCK_LED_PORT, BLOCK_LED_PIN);

	LCD_Init();

	Keypad_Init();

	SPI_INIT_MASTER();

	LCD_WriteString("Welcome to smart");
	LCD_MOVE_CURSOR(2,1);
	LCD_WriteString("home system");
	_delay_ms(1000);
	LCD_CLEAR_SCREEN();

	if ((EEPROM_ReadByteFromAddress(ADMIN_PASS_STATUS_ADDRESS) != PASS_SET)
		|| (EEPROM_ReadByteFromAddress(GUEST_PASS_STATUS_ADDRESS) != PASS_SET))
	{
		LCD_WriteString("login for");
		LCD_MOVE_CURSOR(2,1);
		LCD_WriteString("first time ");
		_delay_ms(1000);
		LCD_CLEAR_SCREEN();
		LCD_WriteString("set admin pass ");
		LCD_MOVE_CURSOR(2,1);
		LCD_WriteString("admin pass:");

		u8 pass_counter = 0;
		u8 pass[PASS_SIZE] = {NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
		while(pass_counter <PASS_SIZE)
		{
			key_pressed =NOT_PRESSED;
			while (key_pressed == NOT_PRESSED)
			{
				key_pressed = Keypad_GetPressedKey();
			}
			pass[pass_counter] = key_pressed;
			LCD_WriteChar(key_pressed);
			_delay_ms(CHARACTER_PREVIEW_TIME);
			LCD_MOVE_CURSOR(2,12+pass_counter);
			LCD_WriteChar(PASSWORD_SYMBOL);
			_delay_ms(100);
			pass_counter++;
		}

		EEPROM_WriteBlockToAddress(EEPROM_ADMIN_ADDRESS,pass, PASS_SIZE);
		EEPROM_WriteByteToAddress(ADMIN_PASS_STATUS_ADDRESS, PASS_SET);

		LCD_CLEAR_SCREEN();
		LCD_WriteString("pass saved");
		_delay_ms(500);
		LCD_CLEAR_SCREEN();


		pass_counter = 0;
		LCD_WriteString("set guest pass");
		LCD_MOVE_CURSOR(2,1);
		LCD_WriteString("guest pass:");
		while(pass_counter <PASS_SIZE)
				{
					key_pressed =NOT_PRESSED;
					while (key_pressed == NOT_PRESSED)
					{
						key_pressed = Keypad_GetPressedKey();
					}
					pass[pass_counter] = key_pressed;
					LCD_WriteChar(key_pressed);
					_delay_ms(CHARACTER_PREVIEW_TIME);
					LCD_MOVE_CURSOR(2,12+pass_counter);
					LCD_WriteChar(PASSWORD_SYMBOL);
					_delay_ms(100);
					pass_counter++;
				}

				EEPROM_WriteBlockToAddress(EEPROM_GUEST_ADDRESS,pass, PASS_SIZE);
				EEPROM_WriteByteToAddress(GUEST_PASS_STATUS_ADDRESS, PASS_SET);

				LCD_CLEAR_SCREEN();
				LCD_WriteString("pass saved");
				_delay_ms(500);
				LCD_CLEAR_SCREEN();

	}
	else
	{
		block_mode_flag =FALSE;
	}

	while (1)
	{
		key_pressed = NOT_PRESSED;
		u8 pass_tries_count = 0;

		if (timeout_flag == TRUE)
		{
			timer0_stop();
			session_counter = 0;
			timeout_flag = FALSE;
			login_mode = NO_MODE;
			key_pressed = NOT_PRESSED;
			LED_TurnOff(ADMIN_LED_PORT, ADMIN_LED_PIN);
			LED_TurnOff(GUEST_LED_PORT, GUEST_LED_PIN);
			LCD_CLEAR_SCREEN();
			LCD_WriteString("session timeout");
			_delay_ms(1000);
		}

		while(login_mode == NO_MODE)
		{
			if (block_mode_flag == TRUE)
			{
				LCD_CLEAR_SCREEN();
				LCD_WriteString("login blocked");
				LCD_MOVE_CURSOR(2,1);
				LCD_WriteString("wait 5 seconds");
				LED_TurnOn(BLOCK_LED_PORT, BLOCK_LED_PIN);
				_delay_ms(BLOCK_MODE_TIME);

				pass_tries_count = 0;
				block_mode_flag = FALSE;
				LED_TurnOff(BLOCK_LED_PORT, BLOCK_LED_PIN);
				block_mode_flag = FALSE;
			}
			LCD_CLEAR_SCREEN();
			LCD_WriteString("select mode : ");
			LCD_MOVE_CURSOR(2,1);
			LCD_WriteString("0:Admin 1:Guest");
			while (key_pressed== NOT_PRESSED)
			{
				key_pressed = Keypad_GetPressedKey();
			}
			if (key_pressed != CHECK_ADMIN_MODE && key_pressed != CHECK_GUEST_MODE)
			{
				LCD_CLEAR_SCREEN();
				LCD_WriteString("wrong output");
				key_pressed = NOT_PRESSED;
				_delay_ms(1000);
				continue;
			}

			u8 pass_counter = 0;
			u8 pass[PASS_SIZE] = {NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
			u8 stored_pass[PASS_SIZE] = {NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};

			switch (key_pressed)
			{
			case CHECK_ADMIN_MODE:
				while (login_mode != ADMIN)
				{
					key_pressed = NOT_PRESSED;
					LCD_CLEAR_SCREEN();
					LCD_WriteString("admin mode");
					LCD_MOVE_CURSOR(2,1);
					LCD_WriteString("enter pass:");
					_delay_ms(200);
					pass_counter = 0;

					while (pass_counter<PASS_SIZE)
					{
						while (key_pressed == NOT_PRESSED)
						{
							key_pressed = Keypad_GetPressedKey();
						}
						pass[pass_counter] = key_pressed;
						LCD_WriteChar(key_pressed);
						_delay_ms(CHARACTER_PREVIEW_TIME);
						LCD_MOVE_CURSOR(2,12+pass_counter);
						LCD_WriteChar(PASSWORD_SYMBOL);
						_delay_ms(100);
						pass_counter++;
						key_pressed = NOT_PRESSED;
					}
					EEPROM_ReadBlockFromAddress(EEPROM_ADMIN_ADDRESS, stored_pass, PASS_SIZE);

					if ((ComparePass(pass, stored_pass, PASS_SIZE)) == TRUE)
					{
						login_mode =ADMIN;
						pass_tries_count = 0;
						LCD_CLEAR_SCREEN();
						LCD_WriteString("right pass");
						LCD_MOVE_CURSOR(2,1);
						LCD_WriteString("admin mode");
						_delay_ms(500);
						LED_TurnOn(ADMIN_LED_PORT, ADMIN_LED_PIN);
						timer0_initializeCTC();
						LCD_CLEAR_SCREEN();
					}
					else
					{
						pass_tries_count++;
						login_mode = NO_MODE;
						LCD_CLEAR_SCREEN();
						LCD_WriteString("wrong pass");
						LCD_MOVE_CURSOR(2,1);
						LCD_WriteString("tries left:");
						LCD_WriteChar(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);
						_delay_ms(500);
						LCD_CLEAR_SCREEN();
						if (pass_tries_count>= TRIES_ALLOWED)
						{
							block_mode_flag = TRUE;
							break;
						}

					}
				}
				break;

			case CHECK_GUEST_MODE:
				while (login_mode != GUEST)
				{
					key_pressed = NOT_PRESSED;
					LCD_CLEAR_SCREEN();
					LCD_WriteString("guest mode");
					LCD_MOVE_CURSOR(2,1);
					LCD_WriteString("guest pass:");
					_delay_ms(200);
					pass_counter = 0;

					while (pass_counter < PASS_SIZE)
					{
						while(key_pressed == NOT_PRESSED)
						{
							key_pressed = Keypad_GetPressedKey();
						}

						pass[pass_counter] = key_pressed;
						LCD_WriteChar(key_pressed);
						_delay_ms(CHARACTER_PREVIEW_TIME);
						LCD_MOVE_CURSOR(2,12+pass_counter);
						LCD_WriteChar(PASSWORD_SYMBOL);
						_delay_ms(100);
						pass_counter++;
						key_pressed = NOT_PRESSED;
					}
					EEPROM_ReadBlockFromAddress(EEPROM_GUEST_ADDRESS, stored_pass, PASS_SIZE);

					if ((ComparePass(pass, stored_pass, PASS_SIZE)) == TRUE)
					{
						login_mode =GUEST;
						pass_tries_count = 0;
						LCD_CLEAR_SCREEN();
						LCD_WriteString("right pass");
						LCD_MOVE_CURSOR(2,1);
						LCD_WriteString("guest mode");
						_delay_ms(500);
						LED_TurnOn(GUEST_LED_PORT, GUEST_LED_PIN);
						timer0_initializeCTC();
						LCD_CLEAR_SCREEN();
					}
					else
					{
						pass_tries_count++;
						login_mode = NO_MODE;
						LCD_CLEAR_SCREEN();
						LCD_WriteString("wrong pass");
						LCD_MOVE_CURSOR(2,1);
						LCD_WriteString("tries left:");
						LCD_WriteChar(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);
						_delay_ms(500);
						LCD_CLEAR_SCREEN();
						if (pass_tries_count>= TRIES_ALLOWED)
						{
							block_mode_flag = TRUE;
							break;
						}

					}
				}
				break;


			}
		}

		u8 show_menu = MAIN_MENU;
		while (timeout_flag != TRUE)
		{
			key_pressed = NOT_PRESSED;
			switch(show_menu)
			{
			case MAIN_MENU:
				do{
					LCD_CLEAR_SCREEN();
					LCD_WriteString("1:Room1 2:Room2");
					LCD_MOVE_CURSOR(2,1);
					if (login_mode ==ADMIN)
					{
						LCD_WriteString("3:Room3 4:More ");
					}
					else if (login_mode == GUEST)
					{
						LCD_WriteString("3:Room3 4:ROOM4 ");

					}

					key_pressed = GetKeyPressed(login_mode);
					_delay_ms(100);

					if (key_pressed == SELECT_ROOM1)
					{
						show_menu = ROOM1_MENU;
					}
					else if (key_pressed ==  SELECT_ROOM2)
					{
						show_menu = ROOM2_MENU;
					}
					else if(key_pressed == SELECT_ROOM3)
					{
						show_menu = ROOM3_MENU;
					}
					else if ((key_pressed == SELECT_ROOM4) && (login_mode == GUEST))
					{
						show_menu =ROOM4_MENU;
					}
					else if ((key_pressed == ADMIN_MORE_OPTION) && (login_mode == ADMIN))
					{
						show_menu = MORE_MENU;
					}
					else if (key_pressed != NOT_PRESSED && key_pressed != '0')
										{
											LCD_CLEAR_SCREEN();
											LCD_WriteString("wrong input");
											_delay_ms(500);
										}

				}while ( ((key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE) );//break the loop in case of valid key or time is out

				break; // end of MAIN_MENU case

			case MORE_MENU :
				do
				{
					LCD_CLEAR_SCREEN();
					LCD_WriteString("1:Room4    2:TV   ");
					LCD_MOVE_CURSOR(2,1);
					LCD_WriteString("3:Air Cond.4:RET");

					key_pressed = GetKeyPressed(login_mode);
					_delay_ms(100);

					if (key_pressed == SELECT_ROOM4_ADMIN)
					{
						show_menu = ROOM4_MENU;
					}
					else if (key_pressed == SELECT_TV)
					{
						show_menu = TV_MENU;
					}
					else if (key_pressed == SELECT_AIR_CONDITIONING)
					{
						show_menu = AIRCONDITIONING_MENU;
					}
					else if (key_pressed == ADMIN_RET_OPTION)
					{
						show_menu = MAIN_MENU;
					}
					else if (key_pressed != NOT_PRESSED && key_pressed != '0')
										{
											LCD_CLEAR_SCREEN();
											LCD_WriteString("wrong input");
											_delay_ms(500);
										}

				}while (( (key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out

				break;//End of MORE_MENU case

			case AIRCONDITIONING_MENU:
				do {
					LCD_CLEAR_SCREEN();
					LCD_WriteString("1:Set temperature ");
					LCD_MOVE_CURSOR(2,1);
					LCD_WriteString("2:Control  0:RET");
					key_pressed = GetKeyPressed(login_mode);
					_delay_ms(100);

					if (key_pressed == SELECT_SET_TEMPERATURE)
					{
						show_menu = TEMPERATURE_MENU;
					}
					else if (key_pressed == SELECT_AIR_COND_CTRL)
					{
						show_menu = AIRCOND_CTRL_MENU;
					}
					else if (key_pressed == SELECT_AIR_COND_RET)
					{
						show_menu = MORE_MENU;
					}
					else if (key_pressed != NOT_PRESSED && key_pressed != '0')
					{
						LCD_CLEAR_SCREEN();
						LCD_WriteString("wrong input");
						_delay_ms(500);
					}

				}while (( (key_pressed < '0') || (key_pressed > '2') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out
				break;//End of air conditioning menu case

			case ROOM1_MENU:
				menuOption(ROOM1_MENU, login_mode);
				show_menu = MAIN_MENU;
				break;

			case ROOM2_MENU:
				menuOption(ROOM2_MENU, login_mode);
				show_menu = MAIN_MENU;
				break;

			case ROOM3_MENU:
				menuOption(ROOM3_MENU, login_mode);
				show_menu = MAIN_MENU;
				break;

			case ROOM4_MENU:
				menuOption(ROOM4_MENU, login_mode);
				if (login_mode == ADMIN)
				{
					show_menu = MORE_MENU;
				}
				else
				{
					show_menu = MAIN_MENU;
				}

				break;

			case TV_MENU :
				menuOption(TV_MENU, login_mode);
				show_menu = MAIN_MENU;
				break;

			case AIRCOND_CTRL_MENU:
				menuOption(AIRCONDITIONING_MENU, login_mode);
				show_menu = AIRCONDITIONING_MENU;
				break;

			case TEMPERATURE_MENU:
				temperatue = 0;

				while(temperatue == 0 && timeout_flag == FALSE)
				{
					key_pressed = NOT_PRESSED;
					LCD_CLEAR_SCREEN();
					LCD_WriteString("Set temp :__ ");
					LCD_WriteChar(DEGREES_SYMBOL);
					LCD_WriteChar('C');
					LCD_MOVE_CURSOR(1,11);
					_delay_ms(200);

					key_pressed = GetKeyPressed(login_mode);
					_delay_ms(250);

					if (timeout_flag == TRUE)
					{
						break;
					}
					if (key_pressed < '0' || key_pressed > '9')
					{
						LCD_CLEAR_SCREEN();
						LCD_WriteString("wrong input");
						_delay_ms(500);
						continue;
					}
					else
					{
						LCD_WriteChar(key_pressed);
						temp_tens = key_pressed -ASCII_ZERO;
						key_pressed = NOT_PRESSED;
					}
					key_pressed = GetKeyPressed(login_mode);
					_delay_ms(250);

					if (timeout_flag == TRUE)
					{
						break;
					}
					if (key_pressed < '0' || key_pressed > '9')
					{
						LCD_CLEAR_SCREEN();
						LCD_WriteString("wrong input");
						_delay_ms(500);
						continue;
					}
					else
					{
						LCD_WriteChar(key_pressed);
						temp_ones = key_pressed -ASCII_ZERO;
						key_pressed = NOT_PRESSED;
					}
					temperatue = (temp_tens*10) + temp_ones;
					SPI_SEND_RECEIVE_DATA(SET_TEMPERATURE);
					_delay_ms(200);
					SPI_SEND_RECEIVE_DATA(temperatue);
					LCD_CLEAR_SCREEN();
					LCD_WriteString("temperature sent");
					_delay_ms(500);
				}
				show_menu = AIRCONDITIONING_MENU;
				break;
			}
		}
	}
}

ISR(TIMER0_COMP_vect)
{
	session_counter++;
}



