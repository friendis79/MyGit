#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	/* Replace with your application code */
	int i = 0;
	DDRB = 0xff;
	DDRD = 0x00;
	
	switch(PIND)
	{
		
		case 0xfe:			
			PORTB = ~(1 << i);
			if (i == 7)
				i = 0;
			else
				i++;
				_delay_ms(200);
		break;
		
		case 0xfd:
			PORTB = 0xfe;
			_delay_ms(200);
			for(i = 0; i<7; i++)
			{
				PORTB = (PORTB << 1) | 0x01;
				_delay_ms(200);
			}
		break;
		
		default:
		PORTB = 0xff;
		break;
	}
	

}