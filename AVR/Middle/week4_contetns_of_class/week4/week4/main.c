#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

int PushButtonDet (int number);
void LEDOnOff (int number, int onoff);
int ClickDet (int number, int polarity);
void LEDTimeOnOFF(unsigned t);

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff; // 전원을 키고 난 후의 초깃값을 지정
	
	DDRD = 0;
	
	unsigned time_count = 0;
	
	while(1)
	{
		if (PushButtonDet(1)){
			time_count++;
			LEDTimeOnOFF(time_count);
		}
		
		else{
			time_count = 0;
		}
		_delay_ms(1);
	}
	return 0;
}

void LEDTimeOnOFF(unsigned t)
{
	int i;
	unsigned t_s;
	t_s = t / 1000;
	
	for (i=0; i<8; i++)
	LEDOnOff(i, 0);
	
	if ((t_s >= 1) && (t_s <= 8))
	LEDOnOff(t_s-1, 1);
	
	else if (t_s == 9){
		for (i=0; i<4; i++)
		LEDOnOff(i, 1);
	}
	
	else if (t_s == 10){
		for (i=4; i<8; i++)
		LEDOnOff(i, 1);
	}
	
	else if (t_s >= 11){
		for (i=0; i<8; i++)
		LEDOnOff(i, 1);
	}
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