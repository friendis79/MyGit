#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

int PushButtonDet (int number);
void LEDOnOff (int number, int onoff);
int ClickDet (int number, int polarity);

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff; // 전원을 키고 난 후의 초깃값을 지정
	
	DDRD = 0;
	
	int led_OnOff = 0; // 초기에는 LED가 꺼져있으므로 0으로 초기화
	
	while(1)
	{
		if (ClickDet(0, 0)){	// 버튼 클릭을 감지 -> 버튼이 클릭되면 LED의 상태를 반전 시키고 LEDOnOff 함수 호출
			led_OnOff = !led_OnOff; // 논리 연산자 (!) : 0000 0000 -> 0000 0001
			LEDOnOff(0, led_OnOff);
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

void LEDOnOff (int number, int onoff) // on -> 1, off -> 0
{
	char led_state;
	led_state = ~PORTB;
	

	// 특정 위치를 1로 바꾸고 위치만 1인 비트열을 만듦
	if (onoff == 1){
		led_state = led_state | (1 << number); // 지정된 위치에만 1을 추가 하고 싶을 때 사용 number 만큼 이동
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
	
	else {	// 버튼이 떨어질 때를 감지
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