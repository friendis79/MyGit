#include <avr/io.h>
#define F_CPU 14.7456E6
#include <avr/interrupt.h>

// FND 문자표 설정
unsigned char Port_char[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf};

void timer0_init();
ISR(TIMER0_COMP_vect);
void FND_Display(int idx, int number, int dot);

int SegIdx = 0;
int SegChangeFlag = 0;	// CPU 부하를 덜 시키는 방법 2

int main(void)
{
	DDRB = 0xff;
	DDRE = 0xff;
	
	PORTB = 0xff;
	PORTE = 0x80;
	
	timer0_init();
	sei();	// UART나 Interrupt 다 포함해서 만들기 위해 사용
	
	int disp_key = 0; // disp_key 변수 초기화
	int idx = 0;      // idx 변수 초기화
	int dot = 0;      // dot 변수 초기화

	while (1)
	{
		if (SegChangeFlag) {
			FND_Display(SegIdx, SegIdx, 0);
			SegChangeFlag = 0;
		}
	}
}

void timer0_init()
{
	// CTC mode setting
	TCCR0 |= (1 << WGM01) | (0 << WGM00);
	TCNT0 = 0;
	OCR0 = 36;
	
	// OCIE (Output Compare Match Interrupt Enable)
	TIMSK |= (1 << OCIE0);
	
	// Prescale = 1024
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
}

ISR (TIMER0_COMP_vect) // 2.5ms 마다 호출 ※ ISR에서는 최소한의 작업만 할 것
{
	SegIdx++;
	if (SegIdx == 4)	SegIdx = 0;
	
	// FND_Display(SegIdx, SegIdx, 0);	// CPU를 덜 부하시키는 방법 1 -> 그닥 효율적이진 않음
	
	SegChangeFlag = 1;
}

void FND_Display(int idx, int number, int dot)
{
	if (idx == 0)
	PORTE = 0x10;
	else if (idx == 1)
	PORTE = 0x20;
	else if (idx == 2)
	PORTE = 0x40;
	else if (idx == 3)
	PORTE = 0x80;

	PORTB = Port_char[number];
	
	if (dot == 1)
	PORTB = PORTB & 0x7f;
}