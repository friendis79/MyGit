#include <avr/io.h>
#define F_CPU 14.7456E6
#include <avr/interrupt.h>

// FND 문자표 설정
unsigned char Port_char[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf};


void timer0_init();
ISR(TIMER0_COMP_vect);
void FND_Display(int idx, int number, int dot);

ISR (USART1_RX_vect);
void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);

int SegIdx = 0;
int SegChangeFlag = 0;
int RXNUM[4] = {0, }; // 입력 받은 4자리 숫자를 임시 저장할 배열

ISR(USART1_RX_vect)
{
	char rx_data;
	rx_data = UDR1;
	putchar_USART1(rx_data);
	if (rx_data == '\r') {
		putchar_USART1('\n');
	}
	else if ((rx_data >= '0') && (rx_data <= '9')) {
		// 숫자 입력되면 한 칸 씩 좌로 이동
		RXNUM[3] = RXNUM[2];
		RXNUM[2] = RXNUM[1];
		RXNUM[1] = RXNUM[0];
		RXNUM[0] = rx_data - '0';  // 새 숫자는 제일 우측에
	}
}

int main(void)
{
	DDRB = 0xff;
	DDRE = 0xff;
	
	PORTB = 0xff;
	PORTE = 0x80;
	
	// TImer, UART 초기화 및 Interrupt 활성
	Init_USART1();
	timer0_init();
	sei(); // UART와 Interrupt 다 포함해서 만들기 위해 사용

	puts_USART1("7 Segment Control Program \r\n");
	
	while (1)
	{
		if(SegChangeFlag) {
			FND_Display(SegIdx, RXNUM[3-SegIdx], 0);
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

ISR (TIMER0_COMP_vect)	// 2.5ms마다 Segment의 값 변경
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
	
	if (dot == 1)		PORTB = PORTB & 0x7f;
}