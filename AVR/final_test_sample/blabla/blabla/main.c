#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// UART 초기화
void UART_init(unsigned int baud) {
	unsigned int ubrr = F_CPU/16/baud-1;
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1<<RXEN) | (1<<TXEN);  // 수신 및 송신 활성화
	UCSRC = (1<<URSEL) | (3<<UCSZ0); // 8 data bits, 1 stop bit
}

// UART 데이터 송신
void UART_transmit(unsigned char data) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = data;
}

// UART 데이터 수신
unsigned char UART_receive(void) {
	while (!(UCSRA & (1<<RXC)));
	return UDR;
}

// 키패드 입력 처리
#define KEYPAD_PORT PORTC
#define KEYPAD_DDR  DDRC
#define KEYPAD_PIN  PINC

char get_key() {
	KEYPAD_PORT = 0xF0; // 상위 4비트를 출력으로 설정
	_delay_ms(1);
	
	uint8_t row = KEYPAD_PIN & 0xF0;
	if (row == 0xF0) return 0; // 키 입력 없음

	KEYPAD_PORT = 0x0F; // 하위 4비트를 출력으로 설정
	_delay_ms(1);
	
	uint8_t col = KEYPAD_PIN & 0x0F;
	if (col == 0x0F) return 0; // 키 입력 없음

	// 행과 열을 이용해 어떤 키가 눌렸는지 계산
	// 여기서는 간단하게 '1' 키만 반환하는 예시
	return '1';
}

// UART 수신 인터럽트 서비스 루틴
ISR(USART_RXC_vect) {
	unsigned char received = UART_receive();
	if (received == 'A') {
		// 특정 명령어가 수신되면 인터럽트 처리
		// 예: LED 토글
		PORTB ^= (1 << PB0);
	}
}

// UART 인터럽트 활성화
void USART_enable_interrupt() {
	UCSRB |= (1<<RXCIE); // 수신 인터럽트 활성화
	sei(); // 전역 인터럽트 활성화
}

// 타이머 오버플로우 인터럽트 서비스 루틴
ISR(TIMER0_OVF_vect) {
	// 타이머 오버플로우 인터럽트 처리 코드
	// 예: 주기적인 LED 깜박임
	PORTB ^= (1 << PB1);
}

// 타이머 초기화
void timer0_init() {
	TCCR0 = (1<<CS02) | (1<<CS00); // 프리스케일러 설정 (1024)
	TIMSK = (1<<TOIE0); // 타이머 오버플로우 인터럽트 활성화
	sei(); // 전역 인터럽트 활성화
}

int main(void) {
	// 초기화
	UART_init(9600); // UART 초기화
	USART_enable_interrupt(); // UART 인터럽트 활성화
	timer0_init(); // 타이머 초기화
	
	KEYPAD_DDR = 0x0F; // 상위 4비트 입력, 하위 4비트 출력 설정
	KEYPAD_PORT = 0xFF; // 풀업 저항 활성화
	
	DDRB |= (1 << PB0) | (1 << PB1); // LED 연결 핀 출력으로 설정

	while (1) {
		char key = get_key();
		if (key) {
			UART_transmit(key); // 키 입력을 UART로 전송
		}
	}
	return 0;
}
