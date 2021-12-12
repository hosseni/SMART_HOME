/*
 * keyad_driver.c
 *
 *  Created on: Dec 12, 2021
 *      Author: ELHOSSENI
 */


#include "keypad_driver.h"
#include "Dio_config_Master.h"
#include "avr/delay.h"

void Keypad_Init(void){

	Dio_SetPinDirection(KEYPAD_PORT,KEYPAD_FIRST_PIN,  OUTPUT);
	Dio_SetPinDirection(KEYPAD_PORT,KEYPAD_SECOND_PIN, OUTPUT);
	Dio_SetPinDirection(KEYPAD_PORT,KEYPAD_THIRD_PIN,  OUTPUT);
	Dio_SetPinDirection(KEYPAD_PORT,KEYPAD_FOURTH_PIN, OUTPUT);

	Dio_SetPinDirection(KEYPAD_PORT,KEYPAD_FIFTH_PIN,   INPUT);
	Dio_SetPinDirection(KEYPAD_PORT,KEYPAD_SIXTH_PIN,   INPUT);
	Dio_SetPinDirection(KEYPAD_PORT,KEYPAD_SEVENTH_PIN, INPUT);
	Dio_SetPinDirection(KEYPAD_PORT,KEYPAD_EIGHTH_PIN,  INPUT);

	// enable pullup res
	Dio_SetPinValue(KEYPAD_PORT, KEYPAD_FIFTH_PIN,   HIGH);
	Dio_SetPinValue(KEYPAD_PORT, KEYPAD_SIXTH_PIN,   HIGH);
	Dio_SetPinValue(KEYPAD_PORT, KEYPAD_SEVENTH_PIN, HIGH);
	Dio_SetPinValue(KEYPAD_PORT, KEYPAD_EIGHTH_PIN , HIGH);

}

u8 Keypad_GetPressedKey(void){

	u8 return_value = NOT_PRESSED;
	u8 arr[4][4] = {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};
	u8 row,col;
	u8 key_pressed;
	for(row = 0; row < 4; row++){
		Dio_SetPinValue(KEYPAD_PORT,KEYPAD_FIRST_PIN, HIGH);
		Dio_SetPinValue(KEYPAD_PORT,KEYPAD_SECOND_PIN,HIGH);
		Dio_SetPinValue(KEYPAD_PORT,KEYPAD_THIRD_PIN, HIGH);
		Dio_SetPinValue(KEYPAD_PORT,KEYPAD_FOURTH_PIN,HIGH);

		_delay_ms (20);
		Dio_SetPinValue(KEYPAD_PORT, row, LOW);

		for (col = 0; col<4 ;col++)
		{
			key_pressed = Dio_GetPinValue(KEYPAD_PORT, (col+4));

			if (key_pressed == 0)
			{
				return_value = arr[row][col];
				break;
			}
		}
	}
	return return_value;
}

