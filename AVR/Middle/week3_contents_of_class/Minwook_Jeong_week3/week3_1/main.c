#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

int PushButtonDet (int number);
void LEDOnOff (int number, int onoff);
int ClickDet (int number, int polarity);

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff; // 전원을 키고 난 후의 초깃값을 지정
	
	DDRD = 0;
	
	int led_state = 0;
	
	while(1)
	{
		if (ClickDet(0, 1)){
			led_state = !led_state; // 논리 연산자 (!) : 0000 0000 -> 0000 0001
			LEDOnOff(0, led_state);
		}
	}
	return 0;
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1) // 비트 연산자 (~) : 0000 0000 -> 1111 1111
	return 1;
	
	else
	return 0;
}

void LEDOnOff (int number, int onoff)
{
	char led_state;
	led_state = ~PORTB;
	
	if (onoff == 1){
		led_state = led_state | (1 << number); // 지정된 위치에만 1을 추가 하고 싶을 때 사용
		PORTB = ~led_state;
	}
	
	else{
		led_state = led_state & ~(1 << number); // 원하는 자리의 LED 끄기
		PORTB = ~led_state;
	}
}

int ClickDet (int number, int polarity)
{
	int button;
	
	if (polarity == 1){   // 버튼을 누를 때를 감지
		button = PushButtonDet(number);
		if (button == 0){
			_delay_ms(1);
			button = PushButtonDet(number);
			if (button == 1)
				return 1;
		}
	}
	
	else {	// 버튼이 떨어질 때
		button = PushButtonDet(number);
		if (button == 1){
			_delay_ms(1);
			button = PushButtonDet(number);
			if (button == 0)
				return 1;
		}
	}
	return 0;
}