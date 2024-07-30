#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
	DDRD = 0x00;
	
	while(1) 
	{
		PORTB 0xff;
		_delay_ms(100);
		PORTB 0x00;
		_delay_ms(100);
	}
	
}