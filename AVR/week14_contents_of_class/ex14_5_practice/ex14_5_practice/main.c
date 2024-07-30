#include <avr/io.h>
#define F_CPU 14.7456E6
#include <avr/interrupt.h>

// FND 문자표 설정
unsigned char Port_char[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf};

void timer0_init();
ISR(TIMER0_COMP_vect);
void FND_Display(int idx, char c);

ISR (USART1_RX_vect);
void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);

int SegIdx = 0;
int SegChangeFlag = 0;
char SegChar[4] = {0, }; // 4자리 문자를 저장할 배열
char RXChar[4]; // 입력 받은 4자리 문자를 임시 저장할 배열
int RXCNT = 0; // 입력받은 문자의 카운트

ISR(USART1_RX_vect)
{
    char rx_data;
    rx_data = UDR1;
    putchar_USART1(rx_data);
    if (rx_data == '\r'){
        for (int i = 0; i < 4; i++) {
            if (i < RXCNT) {
                SegChar[i] = RXChar[RXCNT - 1 - i]; // 오른쪽에서 왼쪽으로 문자를 채움
            }
            else {
                SegChar[i] = ' '; // 나머지 자리는 공백으로 채움
            }
        }
        RXCNT = 0;
        putchar_USART1('\n');
    }
    else if ((rx_data >= '0' && rx_data <= '9') || 
			(rx_data >= 'A' && rx_data <= 'Z') || 
			(rx_data >= 'a' && rx_data <= 'z')) {
        if (RXCNT < 4) {
            RXChar[RXCNT] = rx_data;
            RXCNT++;
        }
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

    puts_USART1("Start \r\n");
    
    while (1)
    {
        if(SegChangeFlag) {
            FND_Display(SegIdx, SegChar[SegIdx]);
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

void FND_Display(int idx, char c)
{
	if (idx == 3)		PORTE = 0x10;
	else if (idx == 2)	PORTE = 0x20;
	else if (idx == 1)	PORTE = 0x40;
	else if (idx == 0)	PORTE = 0x80;

switch (c)
{
	// Uppercase letters
	case 'A' : PORTB = ~0x77;    break;
	// case 'B' : PORTB = ~0x7C;    break; -> 8과 같음 사용 X
	case 'C' : PORTB = ~0x39;    break;
	//case 'D' : PORTB = ~0x5E;    break; -> 0과 같음 사용 X
	case 'E' : PORTB = ~0x79;    break;
	case 'F' : PORTB = ~0x71;    break;
	case 'G' : PORTB = ~0x3D;    break; // 이거 가능?
	case 'H' : PORTB = ~0x76;    break;
	case 'I' : PORTB = ~0x30;    break; // 대문자 소문가 같음 (I = i)
	case 'J' : PORTB = ~0x1E;    break;
	case 'K' : PORTB = ~0x75;    break; // 대문자 소문자 같음 (K = k)
	case 'L' : PORTB = ~0x38;    break;
	case 'M' : PORTB = ~0x37;    break;
	case 'N' : PORTB = ~0x54;    break;
	case 'O' : PORTB = ~0x3F;    break;
	case 'P' : PORTB = ~0x73;    break;
	case 'Q' : PORTB = ~0x67;    break;
	case 'R' : PORTB = ~0x50;    break;
	case 'S' : PORTB = ~0x6D;    break;
	case 'T' : PORTB = ~0x78;    break;
	case 'U' : PORTB = ~0x3E;    break;
	case 'V' : PORTB = ~0x3E;    break;
	case 'W' : PORTB = ~0x2A;    break;
	case 'X' : PORTB = ~0x76;    break;
	case 'Y' : PORTB = ~0x6E;    break;
	case 'Z' : PORTB = ~0x5B;    break;
	
	// Lowercase letters
	case 'a' : PORTB = ~0x5F;    break;
	case 'b' : PORTB = ~0x7C;    break;
	case 'c' : PORTB = ~0x58;    break;
	case 'd' : PORTB = ~0x5E;    break;
	case 'e' : PORTB = ~0x7B;    break;
	case 'f' : PORTB = ~0x71;    break;
	case 'g' : PORTB = ~0x6F;    break;
	case 'h' : PORTB = ~0x74;    break;
	case 'i' : PORTB = ~0x10;    break;
	case 'j' : PORTB = ~0x0E;    break;
	case 'k' : PORTB = ~0x75;    break;
	case 'l' : PORTB = ~0x06;    break;
	case 'm' : PORTB = ~0x54;    break;
	case 'n' : PORTB = ~0x54;    break;
	case 'o' : PORTB = ~0x5C;    break;
	case 'p' : PORTB = ~0x73;    break;
	case 'q' : PORTB = ~0x67;    break;
	case 'r' : PORTB = ~0x50;    break;
	case 's' : PORTB = ~0x6D;    break;
	case 't' : PORTB = ~0x78;    break;
	case 'u' : PORTB = ~0x1C;    break;
	case 'v' : PORTB = ~0x1C;    break;
	case 'w' : PORTB = ~0x2A;    break;
	case 'x' : PORTB = ~0x76;    break;
	case 'y' : PORTB = ~0x6E;    break;
	case 'z' : PORTB = ~0x5B;    break;
	
	default :  PORTB = 0xff;
}
}