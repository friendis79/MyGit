#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

char row_scan(char row);
char key_scan();

int main(void)
{
	DDRB = 0xff;
	DDRC = 0x0f;
	DDRD = 0;
	DDRE = 0xff;
		
	PORTE = 0x80;
	
	/* Replace with your application code */
	while (1)
	{
		PORTB = key_scan();
	}
}

char row_scan(char row) // row  0,1,2,3
{
	char col = -1; //0xff
	char pin_info;
	if (row == 0)      PORTC = 0x0e; //1110
	else if (row == 1) PORTC = 0x0d; //1101
	else if (row == 2) PORTC = 0x0b; //1011
	else if (row == 3) PORTC = 0x07; //0111
	
	_delay_us(1);
	pin_info = PINC >> 4;
	
	if (pin_info == 0x1)      col = 0; // 0001
	else if (pin_info == 0x2) col = 1; // 0010
	else if (pin_info == 0x4) col = 2; // 0100
	else if (pin_info == 0x8) col = 3; // 1000
	
	return (col); //0,1,2,3
}

char key_scan()
{
	char col;
	char row;
	char key = 0xff;
	
	for(row = 0; row <4; row ++)
	{
		col = row_scan(row);
		if (col != 0xff)
		{
			key = 4 * row +col;
			return (key);
		}
	}

	return (0xff);
}