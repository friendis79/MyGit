#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

// LED 1초마다 깜빡이기
int main(void)
{
	DDRB = 0xff;
	DDRD = 0xff;
	
	while(1)
	{
		PORTB = 0;
		_delay_ms(100);
		PORTB = 0x1;
		_delay_ms(100);
	}
}