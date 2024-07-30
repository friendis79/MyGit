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
	PORTB = 0xff; // ������ Ű�� �� ���� �ʱ갪�� ����
	
	DDRD = 0;
	
	unsigned time_count = 0;
	
	while(1)
	{
		if (PushButtonDet(0)){
			time_count++;
			LEDTimeOnOFF(time_count);
		}
		
		else{
			time_count = 0;
			PORTB = 0xff;
			_delay_ms(500);
			PORTB = 0x00;
			_delay_ms(500);
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
	LEDOnOff(i, 1);
	
	if (t_s >= 0)
	LEDOnOff(i, 1);
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1) // ��Ʈ ������ (~) : 0000 0000 -> 1111 1111
	return 1;
	
	else
	return 0;
}

void LEDOnOff (int number, int onoff)
{
	char led_state;
	led_state = ~PORTB;
	
	// Ư�� ��ġ�� 1�� �ٲٰ� ��ġ�� 1�� ��Ʈ���� ����
	if (onoff == 1){
		led_state = led_state | (1 << number); // ������ ��ġ���� 1�� �߰� �ϰ� ���� �� ��� number ��ŭ �̵�
		PORTB = ~led_state;
	}
	
	else{
		led_state = led_state & ~(1 << number); // ���ϴ� �ڸ��� LED ����
		PORTB = ~led_state;
	}
}

int ClickDet (int number, int polarity)
{
	int button;
	
	if (polarity == 1){   // ��ư�� ���� ���� ����
		button = PushButtonDet(number);
		if (button == 0){
			_delay_ms(1);
			button = PushButtonDet(number);
			if (button == 1)
			return 1;
		}
	}
	
	else {	// ��ư�� ������ ���� ����
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