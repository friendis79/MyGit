#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

int main(void)
{
	/* Replace with your application code */
	DDRB = 0xff;
	DDRD = 0x00;

	while(1)
	{
		switch(PIND)
		{
			case 0xfe: // 0, 전부 켜기
			PORTB = 0xff;
			_delay_ms(500);
			PORTB = 0x00;
			_delay_ms(500);
			break;

			case 0xfd: //1, 1칸씩 왼쪽으로
			PORTB = 0b01010101;
			_delay_ms(500);
			PORTB = 0xff;
			break;

			case 0xfb: //2, 1칸씩 오른쪽으로
			PORTB = 0xfe;
			_delay_ms(200);
			PORTB = 0b10101010;
			_delay_ms(500);
			PORTB = 0xff;
			break;
		}
	}

}