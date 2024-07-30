#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <stdlib.h>

void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);

int main(void)
{
	char string[] = "Hello \r \n";	// \r -> 맨앞으로 옮겨라
	Init_USART1();
	
	for (int i = 0; i<5; i++)		puts_USART1(string);
	
	while (1)
	{
		// 프로그램을 계속 실행하기 위한 무한 루프
	}
}

void Init_USART1()
{
	// UCSR1A = UCSR1A | (0b00011000); -> professor typo?
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
	int i =0;
	/*
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
	
	//while(1){	-> 교수님 코드
		//if (str[i] == 0)	break;
		//putchar_USART1(str[i]);
		//i++;
	//}
	
	// 고인물 방식
	while (*str != 0){
		putchar_USART1(*str);
		str++;
	}
}