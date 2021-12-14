

#ifndef LCD_INT_H_
#define LCD_INT_H_

#include "Std_Types.h"

#define CLR_SCREEN           0X01
#define DISPLAY_ON_CURSOR_ON 0X0E
#define EIGHT_BIT_MODE       0X38
#define FOUR_BIT_MODE_I      0X02
#define FOUR_BIT_MODE_II     0X28


void LCD_Init(void);

void LCD_WriteCommand(u8 Command);
void LCD_WriteChar(u8 Data);
void LCD_WriteString(u8 *Word);
void LCD_CLEAR_SCREEN(void);
void LCD_MOVE_CURSOR(u8 row, u8 col);

#endif /* LCD_INT_H_ */
