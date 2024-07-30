// 마스터와 슬레이브의 역할을 컴파일 타임에 결정
// #define IS_MASTER를 1로 설정하면 마스터로, 0으로 설정하면 슬레이브로 작동
// 마스터는 'A'를 송신하고, 슬레이브는 이를 수신하여 'B'로 응답, 마스터는 'B'를 수신하면 LED를 토글

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

// 함수 프로토타입
void Init_USART1();
void UART_transmit(unsigned char data);
unsigned char UART_receive();
void LEDOnOff(int number, int onoff); // 1 -> LED ON, 0 -> LED OFF

// 전역 변수
int isMaster = 1;  // 1: 마스터, 0: 슬레이브

void Init_USART1()
{
	UCSR1B |= 0b00011000;  // 송신 및 수신 활성화
	UBRR1L = 95;    // 보드레이트 설정
}

void UART_transmit(unsigned char data)
{
	while (!(UCSR1A & (1 << UDRE1)));  // 데이터 레지스터가 비워질 때까지 대기
	UDR1 = data;  // 데이터 송신
}

unsigned char UART_receive()
{
	while (!(UCSR1A & (1 << RXC1)));  // 데이터 수신 대기
	return UDR1;  // 수신된 데이터 반환
}

void LEDOnOff(int number, int onoff)
{
	char led_state;
	led_state = ~PORTB;
	
	if (onoff == 1) {
		led_state = led_state | (1 << number);  // LED 켜기
		PORTB = ~led_state;
	}
	else {
		led_state = led_state & ~(1 << number);  // LED 끄기
		PORTB = ~led_state;
	}
}

int main(void)
{
	DDRB = 0xff;  // 포트 B를 출력으로 설정
	PORTB = 0xff; // 모든 포트 B 핀을 HIGH로 설정
	Init_USART1();  // UART 초기화
	
	while (1)
	{
		if (isMaster) {
			// 마스터 역할: 'A'를 송신하고 'B'를 수신하면 LED를 토글
			UART_transmit('A');  // 'A' 문자 송신
			_delay_ms(1000);  // 1초 대기

			unsigned char rx_data = UART_receive();  // UART로부터 데이터 수신

			if (rx_data == 'B') {
				PORTB = ~PORTB;  // 'B'를 수신하면 LED를 토글
			}
		} 
			
			else {
			// 슬레이브 역할: 'A'를 수신하면 'B'를 송신
			unsigned char rx_data = UART_receive();  // UART로부터 데이터 수신

			if (rx_data == 'A') {
				UART_transmit('B');  // 'A'를 수신하면 'B' 송신
			}
		}
	}
}