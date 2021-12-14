/*
 * keypad_driver.h
 *
 *  Created on: Oct 12, 2021
 *      Author: ELHOSSENI
 */


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_

#define NOT_PRESSED 0xff


#include "Dio_Int.h"

void Keypad_Init(void);

u8 Keypad_GetPressedKey(void);

#endif // KEYPAD_DRIVER_H_

