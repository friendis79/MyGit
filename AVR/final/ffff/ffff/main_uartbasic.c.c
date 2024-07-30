#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (USART1_RX_vect);
void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);

// UART1 수신 인터럽트 서비스 루틴
ISR(USART1_RX_vect)
{
	char rx_data; // 수신된 데이터를 저장할 변수
	rx_data = UDR1; // UDR1 레지스터에서 수신 데이터를 읽음
	putchar_USART1(rx_data); // 에코(수신된 데이터를 다시 송신)

	if (rx_data == '\r'){ // 수신된 데이터가 캐리지 리턴(엔터키)인 경우
		puts_USART1("\r\n #################### \r\n");
		puts_USART1("\r\n ##ATmega128 Ready \r\n");
		puts_USART1("\r\n #################### \r\n");
	}
}


int main(void)
{
	DDRG = 0xff;
	DDRB = 0xff; // 포트 B를 출력으로 설정
	DDRE = 0xff; // 포트 E를 출력으로 설정
	
	Init_USART1(); // USART1 초기화
	sei(); // 글로벌 인터럽트 활성화

	/* Replace with your application code */
	while (1)
	{
	}
}

// USART1 초기화 함수
void Init_USART1()
{
	UCSR1B |= (1 << RXCIE); // RXCIE 비트 (수신 완료 인터럽트 활성화)
	UCSR1B |= (1 << RXEN) | (1 << TXEN); // RXEN, TXEN 설정 (수신, 송신 활성화)
	UBRR1L = 7; // Baud Rate 설정 (115200bps 기준)
}

// USART1 송신 함수 (한 문자)
void putchar_USART1(char data)
{
	while(1) {
		if (UCSR1A & (1 << UDRE)) { // UDRE 비트 확인 (송신 버퍼가 비어있는지 확인)
			UDR1 = data; // 송신 데이터를 UDR1 레지스터에 저장
			break;
		}
	}
}

// USART1 송신 함수 (문자열)
void puts_USART1(char *str)
{
	while (*str != 0) { // 문자열의 끝을 만날 때까지
		putchar_USART1(*str); // 한 문자씩 송신
		str++; // 다음 문자로 이동
	}
}