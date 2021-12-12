#include "SPI_INIT.h"
#include "Dio_Int.h"
#include "Dio_Reg.h"
#include "Utilites.h"
#include "Std_Types.h"
void SPI_INIT_MASTER(void) {

	// MOSI, CLK, CS as output

	Dio_SetPinDirection(GroupB, PIN4, OUTPUT); //CS
	Dio_SetPinDirection(GroupB, PIN5, OUTPUT); //MOSI
	Dio_SetPinDirection(GroupB, PIN7, OUTPUT); //CLK

	Dio_SetPinDirection(GroupB, PIN6, INPUT); // MISO input

	SET_BIT(SPCR, 4); // MASTER

	SET_BIT(SPCR,0);

	SET_BIT(SPCR, 6); //enable SPI

	CLR_BIT(SPCR, 3); // raising

/*

	DDRB |=(1<<5) |(1<<4)|(1<<7);//Set the port B mosi(master out slave in ) ,port B ss(slave select),sck(spi clock)  pins as output
		SPCR |= (1<<6)|(1<<4)|(1<<0);//Enable the SPI,master mode ,Set the clock speed to F/16
*/

}
void SPI_INIT_SLAVE(void) {

	Dio_SetPinDirection(GroupB, PIN6, OUTPUT); // MISO input

	// MOSI, CLK, CS as input
	Dio_SetPinDirection(GroupB, PIN4, INPUT); //CS
	Dio_SetPinDirection(GroupB, PIN5, INPUT); //MOSI
	Dio_SetPinDirection(GroupB, PIN7, INPUT); //CLK


	CLR_BIT(SPCR, 4); // SLAVE

	SET_BIT(SPCR, 6); //enable SPI

}


u8 SPI_SEND_RECEIVE_DATA(u8 data) {


	SPDR = data;
	while (((GET_BIT(SPSR, 7))  == 0));

	//while (((SPSR&(1<<7))>>7)==0);	//wait till the transmitting is done
									//SPI flag is set to one if the transmission is done
	return SPDR;
}
