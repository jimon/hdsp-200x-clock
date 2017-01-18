#include <avr/io.h>
#include <util/delay.h>
// #include "USI_TWI_Master.h"
#include "hw_hcms_200x.h"

int main (void)
{
	hcms_200x_start();
	// USI_TWI_Master_Initialise();
	// set PB3 to be output
	//DDRB = 0b00001000;
	while (1)
	{
		// flash# 1:
		// set PB3 high
		//PORTB = 0b00001000; 
		//_delay_ms(20);
		// set PB3 low
		//PORTB = 0b00000000;
		//_delay_ms(20);

		// flash# 2:
		// set PB3 high
		//PORTB = 0b00001000; 
		//_delay_ms(100);
		//// set PB3 low
		//PORTB = 0b00000000;
		//_delay_ms(1000);
	}

	return 0;
}