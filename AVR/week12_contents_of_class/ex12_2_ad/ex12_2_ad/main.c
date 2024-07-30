#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

void InterruptInit();
ISR(INT0_vect);
ISR(INT1_vect);
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
	_delay_ms(1000);
	if(!PushButtonDet(0))	BtnPressed = 1;
	
	// 불안정한 신호에 의해서 발생한 인터럽트는 무시함.
	EIFR = 1 << INTF0; //0x1;	// 0b000_0001 => 인터럽트 플래그 clear
}

ISR(INT1_vect)
{
	// 100ms 이후에 버튼이 때져야 땠다고 판단함.
	_delay_ms(1000);
	if(~PushButtonDet(1))	BtnPressed = 1;
	
	// 불안정한 신호에 의해서 발생한 인터럽트는 무시함.
	EIFR = 1 << INTF1; //0x2;	// 0b000_0010 => 인터럽트 플래그 clear
}

void InterruptInit()
{
	// PORTD 0 = INT0 외부 인터럽트 사용 설정, 하강 엣지 감지
	// PORTD 1 = INT1 외부 인터럽트 사용 설정, 상승 엣지 감지
	EICRA = 0b00001011; // INT0 상승 엣지, INT1 하강 엣지 -> 작주랑 다르게 자리를 바꿈
	EIMSK = (1 << INT0) | (1 << INT1); // 0b00000011; // INT0, INT1 사용 허가
	sei();	// Interrupt 반응하게 만들어줌 -> 호출 되어야만 해
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1) // 비트 연산자 (~) : 0000_0000 -> 111_1111
	return 1;
	
	else
	return 0;
}