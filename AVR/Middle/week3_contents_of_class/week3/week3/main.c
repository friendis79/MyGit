#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

int PushButtonDet(int number);
void LedOnOff(int number, int onoff);
int ClickDet (int number, int polarity);

int main(void)
{
	DDRB = 0xff;   // LED
	PORTB = 0xff;    // 전원을 키고 난 후의 초깃값을 지정
	
	DDRD = 0;      // Button PIND
	
	// int onoff = 0;
	int count = 0;
	int i;
	
	while(1)
	{
		if (ClickDet(0, 1))      // (led_num , x) : 누를 때 => 1, 땔 때 => 0
		{
			count++;
			//PORTB = ~count;
		}
		if (ClickDet(7,1))
		{
			count = 0;
			//PORTB = 0xff;
		}
		for (i=0; i<8; i++)
		{
			// count==13 : 0000_1101, LSB부터 MSB까지 차례로 0인지 1인지 확인
			LedOnOff(i, (count>>i) & 0x1);   // LED 좌우반전 : (7-i)
		}
	}
	return 0;
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)
	return 1;
	else
	return 0;
}

void LedOnOff(int number, int onoff)
{
	char led_state;       // char : 8bit
	led_state = ~PORTB;    //현재 PORTB 출력을 읽음, 계산 쉽게 not

	if (onoff == 1)       // 1 => on
	{
		led_state = led_state | (1 << number);   // OR
		PORTB = ~led_state;
	}
	else                // 0 => off
	{
		led_state = led_state & ~(1 <<number);
		PORTB = ~led_state;
	}
}

int ClickDet (int number, int polarity)
{
	int button;
	if (polarity == 1)      // 버튼을 누를 때를 감지
	{
		button = PushButtonDet(number);
		if (button == 0)   // debug -> breakpoint
		{
			_delay_ms(1);   // debug -> comment
			button = PushButtonDet(number);
			if (button == 1)
			return 1;
		}
	}
	else                // 버튼이 떨어질 때
	{
		button = PushButtonDet(number);
		if (button == 1)   // debug -> breakpoint
		{
			_delay_ms(1);   // debug -> comment
			button = PushButtonDet(number);
			if (button == 0)
			return 1;
		}
	}
	return 0;            // no click detection -> 0
}