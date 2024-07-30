#include <avr/io.h>
#define F_CPU 14.7456E6
#include <avr/interrupt.h>

// FND 문자표 설정
unsigned char Port_char[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf};

void timer0_init();
ISR(TIMER0_COMP_vect);
void FND_Display(int idx, int number, int dot);

ISR (USART1_RX_vect);
void InterruptInit();
void putchar_USART1(char data);
void puts_USART1(char *str);

int SegIdx = 0;
int SegChangeFlag = 0;
int SegNumber[4] = {0, }; // 4자리 숫자를 저장할 배열
int RXNUM[4]; // 입력 받은 4자리 숫자를 임시 저장할 배열
int RXCNT = 0; // 입력받은 숫자의 카운트

ISR(USART1_RX_vect)
{
	char rx_data;
	rx_data = UDR1;
	putchar_USART1(rx_data);
	if (rx_data == '\r'){
		for (int i = 0; i < 4; i++) {
			if (i < RXCNT) {
				SegNumber[3 - i] = RXNUM[RXCNT - 1 - i]; // 오른쪽에서 왼쪽으로 숫자를 채움
			}
			else {
				SegNumber[3 - i] = 0; // 나머지 자리는 0으로 채움
			}
		}
		RXCNT = 0;
		putchar_USART1('\n');
	}
	else if ((rx_data >= '0') & (rx_data <= '9')) {
		if (RXCNT < 4) {
			RXNUM[RXCNT] = rx_data - '0';
			RXCNT++;
		}
	}
	else if (rx_data == 'q') {
		RXNUM[RXCNT] = 45;
	}
}

int main(void)
{
	DDRB = 0xff;
	DDRE = 0xff;
	
	PORTB = 0xff;
	PORTE = 0x80;
	
	Init_USART1();
	timer0_init();
	sei(); // UART나 Interrupt 다 포함해서 만들기 위해 사용

	puts_USART1("\r\n7 Segment Control Program \r\n");
	
	while (1)
	{
		if(SegChangeFlag) {
			FND_Display(SegIdx, SegNumber[SegIdx], 0);
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

ISR (TIMER0_COMP_vect)
{
	SegIdx++;
	if (SegIdx == 4) SegIdx = 0;
	SegChangeFlag = 1;
}

void Init_USART1()
{
	UCSR1B |= (1 << RXCIE); // RXCIE bit (7번)을 1로 바꿈
	UCSR1B |= (1 << RXEN) | (1 << TXEN); // RXEN, TXEN 설정
	UBRR1L = 95; // Baud Rate 맞게 설정
}

void putchar_USART1(char data)
{
	while(1) {
		if (UCSR1A & (1 << UDRE)) { // UDRE 확인
			UDR1 = data;
			break;
		}
	}
}

void puts_USART1(char *str)
{
	while (*str != 0) {
		putchar_USART1(*str);
		str++;
	}
}

void FND_Display(int idx, int number, int dot)
{
	if (idx == 0)		PORTE = 0x10;
	else if (idx == 1)	PORTE = 0x20;
	else if (idx == 2)	PORTE = 0x40;
	else if (idx == 3)	PORTE = 0x80;

	PORTB = Port_char[number];
	
	if (dot == 1)
	PORTB = PORTB & 0x7f;
}