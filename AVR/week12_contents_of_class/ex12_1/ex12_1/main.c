#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

void InterruptInit();
ISR(INT0_vect);
int PushButtonDet (int number);

int BtnPressed = 0;

int main(void)
{
	DDRB = 0xff;
	DDRD = 0x0;
	
	PORTB = 0xff;
	
	InterruptInit();
    while (1) 
    {
		if (BtnPressed) {
			PORTB = ~PORTB;
			BtnPressed = 0;
		}
	}
}

ISR(INT0_vect)
{
	// 100ms 이후에도 버튼이 눌려있어야 눌렸다고 판단함.
	_delay_ms(100);
	if(PushButtonDet(0))	BtnPressed = 1;
	
	// 불안정한 신호에 의해서 발생한 인터럽트는 무시함.
	EIFR = 0x1;	// 0b00000001 => 인터럽트 플래그 clear
}

void InterruptInit()
{
	// PORTD = INIT0 외부 인터럽트 사용 설정, 하강 엣지 감지
	EICRA = 0x2; // EICRA 하강 엣지
	EIMSK = 0x1; // EIMSK 사용 허가
	sei();	// Interrupt 반응하게 만들어줌
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1) // 비트 연산자 (~) : 0000 0000 -> 1111 1111
	return 1;
	
	else
	return 0;
}