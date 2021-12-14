
#ifndef HEADERS_EEPROM_H_
#define HEADERS_EEPROM_H_

#include "STD_Types.h"

u8 EEPROM_ReadByteFromAddress( u16 u16Address);

void EEPROM_ReadBlockFromAddress( u16 u16Address, u8* dist, u16 size);

void EEPROM_WriteByteToAddress( u16 u16Address,  u8 u8Data);

void EEPROM_WriteBlockToAddress( u16 u16Address,  u8* u8Data, u16 size);

#endif /* HEADERS_EEPROM_H_ */
