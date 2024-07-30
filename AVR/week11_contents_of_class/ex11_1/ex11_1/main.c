#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <stdlib.h>

void Init_USART1();
void putchar_USART1(char data);

int main(void)
{	
	/* Replace with your application code */
	Init_USART1();
	putchar_USART1('H');
	putchar_USART1('e');
	putchar_USART1('l');
	putchar_USART1('l');
	putchar_USART1('o');
	
	while (1)
	{
		
	}
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