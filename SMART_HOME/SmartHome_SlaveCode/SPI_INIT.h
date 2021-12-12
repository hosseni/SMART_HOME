#ifndef SPI_INIT_H_
#define SPI_INIT_H_

#define SPCR *((volatile u8 *)0x2D)
#define SPDR *((volatile u8 *)0x2F)
#define SPSR *((volatile u8 *)0x2E)

#include "Std_Types.h"

void SPI_INIT_MASTER(void);
void SPI_INIT_SLAVE(void);
u8 SPI_SEND_RECEIVE_DATA(u8 data);

#endif
