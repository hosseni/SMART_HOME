#include "Dio_Int.h"
#include "Dio_Reg.h"
#include "util/delay.h"
#include  "Dio_config_Master.h"
#include "LCD_Int.h"

void LCD_Init(void) {

	//data lines
	Dio_SetPinDirection(LCD_PORT, PIN0, OUTPUT);
	Dio_SetPinDirection(LCD_PORT, PIN1, OUTPUT);
	Dio_SetPinDirection(LCD_PORT, PIN2, OUTPUT);
	Dio_SetPinDirection(LCD_PORT, PIN3, OUTPUT);
	Dio_SetPinDirection(LCD_PORT, PIN4, OUTPUT);
	Dio_SetPinDirection(LCD_PORT, PIN5, OUTPUT);
	Dio_SetPinDirection(LCD_PORT, PIN6, OUTPUT);
	Dio_SetPinDirection(LCD_PORT, PIN7, OUTPUT);

	//RS c0
	Dio_SetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, OUTPUT);
	//RW
	Dio_SetPinDirection(LCD_CONTROL_PORT, LCD_RW_PIN, OUTPUT);
	//E
	Dio_SetPinDirection(LCD_CONTROL_PORT, LCD_EN_PIN, OUTPUT);


	Dio_SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, 0);
	LCD_WriteCommand(EIGHT_BIT_MODE); //function set
	LCD_WriteCommand(DISPLAY_ON_CURSOR_ON); //display on/off setting
	LCD_WriteCommand(CLR_SCREEN); //display clear
	_delay_ms(10);
}

void LCD_WriteCommand(u8 Command) {

	PORTA = Command;
	Dio_SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
	Dio_SetPinValue(LCD_CONTROL_PORT,LCD_EN_PIN, HIGH);
	_delay_ms(2);
	Dio_SetPinValue(LCD_CONTROL_PORT,LCD_EN_PIN, LOW);
	_delay_ms(2);



}
void LCD_WriteChar(u8 Data) {
	PORTA = Data;
	Dio_SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN, HIGH);
	Dio_SetPinValue(LCD_CONTROL_PORT,LCD_EN_PIN, HIGH);
		_delay_ms(2);
		Dio_SetPinValue(LCD_CONTROL_PORT,LCD_EN_PIN, LOW);
		_delay_ms(2);

	}
void LCD_WriteString(u8 *Word) {
	u8 index = 0;
	while (Word[index] != '\0') {
		LCD_WriteChar(Word[index]);
		index++;
	}
}

void LCD_CLEAR_SCREEN(void) {

	LCD_WriteCommand(CLR_SCREEN);
}

void LCD_MOVE_CURSOR(u8 row, u8 col) {
	u8 Location;
	if (row == 1)
	{
		Location = 0x80;
	}
	else if (row == 2)
	{
		Location = 0xc0;
	}
	Location += (col-1);

	LCD_WriteCommand(Location);

	}
