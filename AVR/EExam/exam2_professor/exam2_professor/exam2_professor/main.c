#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

int PushButtonDet (int number);

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff; // 전원을 키고 난 후의 초깃값을 지정
	
	DDRD = 0;
	
	int led_state = 0;
	int time_count_1s = 0;
	int button0, button1, button2;
	int prev_button0 = 0, prev_button1 = 0, prev_button2 = 0;
	int mode;
	
	while(1)
	{
		if (led_state == 0)		PORTB = 0xff;
		else
		{
			if (mode == 0)		PORTB = 0x0;
			else if (mode == 1)	PORTB = 0x55;
			else if (mode == 2)	PORTB = 0xaa;
		}

		button0 = PushButtonDet(0);
		button1 = PushButtonDet(1);
		button2 = PushButtonDet(2);
		
		if ((button0 == 1) && (prev_button0))	mode = 0;
		if ((button1 == 1) && (prev_button1))	mode = 1;
		if ((button2 == 1) && (prev_button2))	mode = 2;
		
		_delay_ms(1);
		time_count_1s++;
		
		if (time_count_1s == 1000)
		{
			time_count_1s = 0;
			led_state = !led_state;
		}
		
		prev_button0 = button0;
		prev_button1 = button1;
		prev_button2 = button2;
		
	}
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1) // 비트 연산자 (~) : 0000 0000 -> 1111 1111
	return 1;
	
	else
	return 0;
}