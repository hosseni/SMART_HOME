
#include "ADC_Int.h"
#include "util/delay.h"

void ADC_Init(void)
{
	//select voltage reference(AREF), right adjust, channel 0
	SET_BIT(ADMUX,6);
	SET_BIT(ADMUX,7);

	//SET_BIT(ADMUX, 6);
	//enable adc
	SET_BIT(ADCSRA, 7);
	//adc prescaler selcet 8
	SET_BIT(ADCSRA, 0);
	SET_BIT(ADCSRA, 1);
}
u16 ADC_Read(void)
{
	u16 read_val_low, read_val;
	//start conversion
	SET_BIT(ADCSRA, 6);
	//loop until conversion compelete
	while(GET_BIT(ADCSRA, 4)==0);
	//_delay_ms(10);
	//clear ineterrupt flag bit
	SET_BIT(ADCSRA, 4);
	//return ADC value
	read_val_low=(u16)ADCL;
	read_val=(u16)(ADCH<<8);
	read_val=read_val|read_val_low;

return read_val;
}
