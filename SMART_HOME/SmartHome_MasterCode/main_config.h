/*
 * main_config.h
 *
 *  Created on: Oct 12, 2021
 *      Author: ELHOSSNEI
 */

#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#include "STD_Types.h"

#define NOT_STORED   0xFF
#define NOT_SELECTED 0xFF

#define BLOCK_MODE_TIME		   5000
#define CHARACTER_PREVIEW_TIME 200
#define DEGREES_SYMBOL		   0xDF

/*********************************** PIN Configuration ***********************************/
#define PASS_SIZE       4
#define TRIES_ALLOWED   3
#define PASSWORD_SYMBOL '*'
#define ASCII_ZERO      '0'

#define PASS_NOT_SET 0xFF
#define PASS_SET     0x01

#define ADMIN_PASS_STATUS_ADDRESS 0X100
#define GUEST_PASS_STATUS_ADDRESS 0X101
#define EEPROM_ADMIN_ADDRESS      0X102
#define EEPROM_GUEST_ADDRESS      0X106
#define LOGIN_BLOCKED_ADDRESS     0X10A


/************************************   Login configurations *****************************/
#define NO_MODE 0
#define ADMIN   1
#define GUEST   2


/************************************   Logic values *************************************/
#define FALSE   0
#define TRUE    1

#define CHECK_ADMIN_MODE        '0'
#define CHECK_GUEST_MODE        '1'

#define SELECT_ROOM1            '1'
#define SELECT_ROOM2            '2'
#define SELECT_ROOM3            '3'
#define SELECT_ROOM4            '4'
#define ADMIN_MORE_OPTION       '4'

#define SELECT_ROOM4_ADMIN      '1'
#define SELECT_TV               '2'
#define SELECT_AIR_CONDITIONING '3'
#define ADMIN_RET_OPTION        '4'

#define SELECT_SET_TEMPERATURE  '1'
#define SELECT_AIR_COND_CTRL    '2'
#define SELECT_AIR_COND_RET     '0'

/****************************   number of ticks to run timeout ***************************/
#define ADMIN_TIMEOUT 5000
#define GUEST_TIMEOUT 2000


/****************************   Show menu codes  *****************************************/
#define MAIN_MENU            1
#define MORE_MENU            2
#define ROOM1_MENU           3
#define ROOM2_MENU           4
#define ROOM3_MENU           5
#define ROOM4_MENU           6
#define TV_MENU              7
#define AIRCONDITIONING_MENU 8
#define AIRCOND_CTRL_MENU    9
#define TEMPERATURE_MENU     10




#endif /* MAIN_CONFIG_H_ */
