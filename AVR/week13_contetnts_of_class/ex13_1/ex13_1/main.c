#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

void InterruptInit();
ISR(INT0_vect);
ISR(INT1_vect);
int PushButtonDet (int number);

void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);
unsigned char getchar_USART1();
void LEDOnOff(int number, int onoff);

int BtnPressed = 0;

int main(void)
{
	DDRB = 0xff;
	DDRD = 0x0;
	
	PORTB = 0xff;
	
	InterruptInit();
	
	char rx_data;
	Init_USART1();
	
	puts_USART1("Start \r\n");
	
	while (1)
	{
		if (BtnPressed) {
			PORTB = (1 << PORTB);
			BtnPressed = 0;
		}
		
		rx_data = getchar_USART1();
		putchar_USART1(rx_data);
		if (rx_data == '\r')	putchar_USART1('\n');
		
		if ((rx_data >= '0') && (rx_data <= '7')) {
			LEDOnOff(rx_data - '0', 1);
		}
		
		else if (rx_data == 'q') {
			PORTB = 0xff;
		}
	}
}

ISR(INT0_vect)
{
	// 100ms 이후에도 버튼이 눌려있어야 눌렸다고 판단함.
	_delay_ms(100);
	if(!PushButtonDet(0))	BtnPressed = 1;
	
	// 불안정한 신호에 의해서 발생한 인터럽트는 무시함.
	EIFR = 1 << INTF0; //0x1;	// 0b000_0001 => 인터럽트 플래그 clear
}

ISR(INT1_vect)
{
	// 100ms 이후에 버튼이 때져야 땠다고 판단함.
	_delay_ms(100);
	if(PushButtonDet(1))	BtnPressed = 1;
	
	// 불안정한 신호에 의해서 발생한 인터럽트는 무시함.
	EIFR = 1 << INTF1; //0x2;	// 0b000_0010 => 인터럽트 플래그 clear
}

void InterruptInit()
{
	// PORTD 0 = INT0 외부 인터럽트 사용 설정, 하강 엣지 감지
	// PORTD 1 = INT1 외부 인터럽트 사용 설정, 상승 엣지 감지
	EICRA = (2 << ISC00) | (3 << ISC10); // 0b00001110; // INT0 하강 엣지, INT1 상승 엣지
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

void Init_USART1()
{
	// UCSR1A = UCSR1A | (0b00011000);
	UCSR1B |= 0b00011000;
	UBRR1L = 95;	// Baud Rate에 맞게 설정
}

void putchar_USART1(char data)
{
	while(1){
		if (UCSR1A = (UCSR1A & 0b00100000)){
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

unsigned char getchar_USART1()
{
	while(1){
		if (UCSR1A & 0x80) {	// if (UCSR1A & (1<<RXC1), 0x80 = 0b10000000;
			return (UDR1);
		}
		else if (BtnPressed)	break;
	}
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
	
	else {
		led_state = led_state & ~(1 << number); // 원하는 자리의 LED 끄기
		PORTB = ~led_state;
	}
}