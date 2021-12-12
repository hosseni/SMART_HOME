/*

 Dio_config_Master.h
 *
 *  Created on: Dec 12, 2021
 *      Author: ELHOSSENI
 */


#ifndef DIO_CONFIG_MASTER_H_
#define DIO_CONFIG_MASTER_H_


#define ADMIN_LED_PORT   2 // portC
#define GUEST_LED_PORT   2 // portC
#define BLOCK_LED_PORT   2 // portC


#define ADMIN_LED_PIN    5
#define GUEST_LED_PIN    6
#define BLOCK_LED_PIN    7

// keypad macros
#define KEYPAD_PORT         3 // portD
#define KEYPAD_FIRST_PIN    0
#define KEYPAD_SECOND_PIN   1
#define KEYPAD_THIRD_PIN    2
#define KEYPAD_FOURTH_PIN   3
#define KEYPAD_FIFTH_PIN    4
#define KEYPAD_SIXTH_PIN    5
#define KEYPAD_SEVENTH_PIN  6
#define KEYPAD_EIGHTH_PIN   7

// lcd macros

#define LCD_PORT            0 // portA
							  // lcd pins
#define LCD_FIRST_PIN       0
#define LCD_SECOND_PIN      1
#define LCD_THIRD_PIN       2
#define LCD_FOURTH_PIN      3
#define LCD_FIFTH_PIN       4
#define LCD_SIXTH_PIN       5
#define LCD_SEVENTH_PIN     6
#define LCD_EIGHTH_PIN      7

#define LCD_CONTROL_PORT    1 // portB

#define LCD_EN_PIN			0
#define LCD_RS_PIN			1
#define LCD_RW_PIN			2


#endif // DIO_CONFIG_MASTER_H_
