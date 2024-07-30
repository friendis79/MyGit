#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
	char temp;
	while(1)
	{
		PORTB = 0xfe; //1111_1110
		temp = ~PORTB;// 0000_0001
		for (int i = 0; i < 7; i++)
			PORTB = ~(temp << i);
	}
}