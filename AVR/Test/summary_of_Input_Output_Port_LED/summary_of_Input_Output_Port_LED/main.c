#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

// 2.1 - LED 번갈아 키기
int main(void)
{
	DDRB = 0xff;
	DDRD = 0xff;
	
	while(1)
	{
		PORTB = 0b01010101;	
	}
}
*/

// 2.2 - 모든 LED 1초마다 깜빡이기
/*
int main()
{
	DDRB = 0xff;
	DDRD = 0xff;
	
	while(1)
	{
		PORTB = 0;
		_delay_ms(100);
	}
}
*/