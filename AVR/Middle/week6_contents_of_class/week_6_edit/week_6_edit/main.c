#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

void FND_Display(int idx, int number, int dot, int time_count);
int PushButtonDet(int number);

unsigned char Port_char[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0xbf};

int main(void)
{
	DDRD = 0;
	DDRB = 0xff;
	DDRE = 0xff;O
	
	PORTE = 0x80;

	int time_count = 0;
	int timer_started = 0;
	int stopped_time = 0;

	while (1)
	{
		int button_state = PushButtonDet(0);

		if (!timer_started && !stopped_time) {
			for (int i = 0; i < 4; i++)
				FND_Display(0);
		}

		if (button_state && !timer_started) {
			timer_started = 1;
			stopped_time = 0;
		}
		
		else if (button_state && timer_started)	{
			timer_started = 0;
			stopped_time = time_count;
		}

		if (timer_started) {
			for (int i = 0; i < 4; i++)	{
				int digit = time_count % 10;
				FND_Display(digit);
				time_count /= 10;
				_delay_ms(2.5);
			}
			time_count++;
		}
		else
		{
			for (int i = 0; i < 4; i++)	{
				int digit = stopped_time % 10;
				FND_Display(digit);
				stopped_time /= 10;
				_delay_ms(2.5);
			}
		}

		if (PushButtonDet(1) && !timer_started)	{
			time_count = 0;
			stopped_time = 0;
		}
	}
}

void FND_Display(int number)
{
	for (int idx = 0; idx < 4; idx++) {
		PORTE = 1 << (4 + idx);
		PORTB = Port_char[number];
		_delay_ms(2.5);
	}
}

int PushButtonDet(int number)
{
	return ((~PIND >> number) & 0x1);
}