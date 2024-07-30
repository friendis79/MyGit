#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <stdlib.h>

void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);
unsigned char getchar_USART1();

int main(void)
{
	char rx_data;
	Init_USART1();
	
	puts_USART1("Start \r\n");
	while (1)
	{
		rx_data = getchar_USART1();
		putchar_USART1(rx_data);
		if (rx_data == '\r')	putchar_USART1('\n');
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

void puts_USART1(char *str)
{
	/*
	int i =0;
	
	for (i; str[i]; i++) {		 // null 문자('\0')를 만날 때까지 반복
		putchar_USART1(str[i]); // 바이트 단위로 출력
	}
	*/
	
	/*
	while(*str){
		putchar_USART1(*str);
		str++;
	}
	*/
	
	/* while(1){	-> 교수님 코드
		//if (str[i] == 0)	break;
		//putchar_USART1(str[i]);
		//i++;
	//}
	*/
	
	// 고인물 방식
	while (*str != 0){
		putchar_USART1(*str);
		str++;
	}
}

unsigned char getchar_USART1()
{
	while(1){
		if (UCSR1A & 0x80){	// if (UCSR1A & (1<<RXC1), 0x80 = 0b10000000;
			return (UDR1);
		}
	}
}