#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

unsigned char Port_char[] ={0x8C,0xc7,0x88,0x91,0x89, 0x86, 0xc2, 0xa3, 0xa1, 0xc6, 0x92, 0xc1, 0x8f, 0xc0, 0xab,
	0xcf, 0x8e, 0xa1}; // 애노드 공통

void FND_Display(int idx, int number);

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
		if (PIND == 0xff) // 0 PLAY
		{
			FND_Display(0, 0);
			_delay_ms(2.5);
			FND_Display(1, 1);
			_delay_ms(2.5);
			FND_Display(2, 2);
			_delay_ms(2.5);
			FND_Display(3, 3);
			_delay_ms(2.5);
		}
		if (PIND == 0xfe) // 1 HELP
		{
			for (int i = 0 ; i < 4; i++)
				PORTB = 0;
			FND_Display(0, 4);
			_delay_ms(2.5);
			FND_Display(1, 5);
			_delay_ms(2.5);
			FND_Display(2, 1);
			_delay_ms(2.5);
			FND_Display(3, 0);
			_delay_ms(2.5);
		}
		
		if (PIND == 0xfd) // 2 GOOD
		{
			for (int i = 0 ; i < 4; i++)
				PORTB = 0;
			FND_Display(0, 6);
			_delay_ms(2.5);
			FND_Display(1, 7);
			_delay_ms(2.5);
			FND_Display(2, 7);
			_delay_ms(2.5);
			FND_Display(3, 8);
			_delay_ms(2.5);
		}
		
		else if (PIND == 0xfb) // 3 COOL
		{
			for (int i = 0 ; i < 4; i++)
			PORTB = 0;
			FND_Display(0, 9);
			_delay_ms(2.5);
			FND_Display(1, 7);
			_delay_ms(2.5);
			FND_Display(2, 7);
			_delay_ms(2.5);
			FND_Display(3, 1);
			_delay_ms(2.5);
		}	
		
		else if (PIND == 0xf7) // 4 SUrE
		{
			for (int i = 0 ; i < 4; i++)
			PORTB = 0;
			FND_Display(0, 10);
			_delay_ms(2.5);
			FND_Display(1, 11);
			_delay_ms(2.5);
			FND_Display(2, 12);
			_delay_ms(2.5);
			FND_Display(3, 5);
			_delay_ms(2.5);
		}
		
		else if (PIND == 0xef) // 5 OPEn
		{
			for (int i = 0 ; i < 4; i++)
			PORTB = 0;
			FND_Display(0, 13);
			_delay_ms(2.5);
			FND_Display(1, 0);
			_delay_ms(2.5);
			FND_Display(2, 5);
			_delay_ms(2.5);
			FND_Display(3, 14);
			_delay_ms(2.5);
		}
		
		else if (PIND == 0xdf) // 6 LIFE
		{
			for (int i = 0 ; i < 4; i++)
			PORTB = 0;
			FND_Display(0, 1);
			_delay_ms(2.5);
			FND_Display(1, 15);
			_delay_ms(2.5);
			FND_Display(2, 16);
			_delay_ms(2.5);
			FND_Display(3, 5);
			_delay_ms(2.5);
		}
		
		else if (PIND == 0xbf) // 7 CodE
		{
			for (int i = 0 ; i < 4; i++)
			PORTB = 0;
			FND_Display(0, 9);
			_delay_ms(2.5);
			FND_Display(1, 7);
			_delay_ms(2.5);
			FND_Display(2, 17);
			_delay_ms(2.5);
			FND_Display(3, 5);
			_delay_ms(2.5);
		}
	}
}

void FND_Display(int idx, int number)
{
	if (idx == 0)
	PORTE = 0x10;
	else if (idx == 1)
	PORTE = 0x20;
	else if (idx == 2)
	PORTE = 0x40;
	else if (idx == 3)
	PORTE = 0x80;

	PORTB = Port_char[number];
}