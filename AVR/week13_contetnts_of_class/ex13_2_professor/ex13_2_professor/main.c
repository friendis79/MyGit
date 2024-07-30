#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

ISR (USART1_RX_vect);
void InterruptInit();
void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);
void LEDOnOff (int number, int onoff);

int ONLED;
int RXNUM;

ISR(USART1_RX_vect)
{
	char rx_data;
	rx_data = UDR1;
	putchar_USART1(rx_data);
	if (rx_data == '\r'){
		ONLED = RXNUM;
		putchar_USART1('\n');
	}
	else if ((rx_data >= '0') & (rx_data <= '7'))	RXNUM = rx_data - '0';
	else if (rx_data == 'q')	RXNUM = -1;
}

int main(void)
{
	Init_USART1();
	InterruptInit();
	
	puts_USART1("Start \r\n");
	
	while(1)
	{
		if (ONLED != -1)
			LEDOnOff(ONLED, 1);
		_delay_ms(1000);
		PORTB = 0xff;
		_delay_ms(1000);
	}
}

void InterruptInit()
{
	UCSR1B |= (1 << RXCIE); // UCSR1B |= 0b10000000; // RXCIE bit (7번)을 1로 바꿈
	sei();
}

void Init_USART1()
{
	// UCSR1A = UCSR1A | (0b00011000);
	UCSR1B |= (1 << RXEN) | (1 << TXEN); //0b00011000;
	UBRR1L = 95;	// Baud Rate 맞게 설정
}

void putchar_USART1(char data)
{
	while(1) {
		if (UCSR1A = (UCSR1A & UDRE)) { // UDRE = 0b00100000
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

void LEDOnOff (int number, int onoff)
{
	char led_state;
	led_state = ~PORTB;
	
	// 특정 위치를 1로 바꾸고 위치만 1인 비트열을 만듦
	if (onoff == 1) {
		led_state = led_state | (1 << number); // 지정된 위치에만 1을 추가 하고 싶을 때 사용 number 만큼 이동
		PORTB = ~led_state;
	}
	
	else {
		led_state = led_state & ~(1 << number); // 원하는 자리의 LED 끄기
		PORTB = ~led_state;
	}
}