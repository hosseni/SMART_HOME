/*
 * menu.h
 *
 *  Created on: Dec 11, 2021
 *      Author: ELKHOLY
 */

#ifndef MENU_H_
#define MENU_H_


#include  "main_config.h"
#include  "STD_MESSAGES.h"
#include  "Std_Types.h"
#include  "keypad_driver.h"
#include  "SPI_INIT.h"
#include  "LCD_Int.h"
#include <avr/delay.h>


u8 ComparePass( u8* pass1, u8* pass2, u8 size);
void menuOption(u8 SelectedRoom, u8 LoginMode);
u8 GetKeyPressed(u8 LoginMode);

#endif /* MENU_H_ */
