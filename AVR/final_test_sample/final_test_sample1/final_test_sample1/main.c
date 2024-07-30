#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>
#include <avr/interrupt.h>

// 주파수 정의
#define DO  3817 // 262Hz (3817us)
#define RE  3401 // 294Hz (3401us)
#define MI  3030 // 330Hz (3030us)
#define FA  2865 // 349Hz (2865us)
#define SOL 2551 // 370Hz (2551us)
#define LA  2273 // 440Hz (2273us)
#define SI  2024 // 494Hz (2024us)

unsigned long int BASE_T = 1000000;

int NOTE1[] = {SOL, SOL, LA, LA, SOL, SOL, MI, SOL, SOL, MI, MI, RE, 0,
SOL, SOL, LA, LA, SOL, SOL, MI, SOL, MI, RE, MI, DO, 0};
int DUR1[] = {4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 1, 4,
4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 1, 4};

int NOTE2[] = {DO, RE, MI, FA, SOL, LA, SI, DO >> 1, 0};
int DUR2[] = {4, 4, 4, 4, 4, 4, 4, 1, 4};

int NOTE3[] = {MI, RE, DO, RE, MI, MI, MI, RE, RE, RE, MI, SOL, SOL, 0};
int DUR3[] = {4, 4, 4, 4, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4};

void MakeSound(int period);
void StopSound();
void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(const char *str);
ISR(USART1_RX_vect);

volatile int music_flag = 0; // 음악 재생 상태를 나타내는 플래그
volatile int music_mode = 1; // 현재 음악 모드 (1, 2, 3 중 하나)
char rx_buffer[10]; // UART 입력 버퍼
volatile uint8_t rx_index = 0; // 버퍼 인덱스

ISR(USART1_RX_vect)
{
	char rx_data = UDR1;
	putchar_USART1(rx_data); // Echo back received data for debugging

	if (rx_data == '\r' || rx_data == '\n') { // 엔터키 수신
		rx_buffer[rx_index] = '\0'; // 문자열 종료
		rx_index = 0; // 버퍼 인덱스 초기화

		if (strcmp(rx_buffer, "s") == 0) { // 음악 시작 명령어 수신
			music_flag = 1;
			puts_USART1("Music started\r\n");
			} else if (strcmp(rx_buffer, "e") == 0) { // 음악 종료 명령어 수신
			music_flag = 0;
			puts_USART1("Music stopped\r\n");
			} else if (strcmp(rx_buffer, "1") == 0) { // 모드 1 설정
			music_mode = 1;
			puts_USART1("Mode 1 selected\r\n");
			} else if (strcmp(rx_buffer, "2") == 0) { // 모드 2 설정
			music_mode = 2;
			puts_USART1("Mode 2 selected\r\n");
			} else if (strcmp(rx_buffer, "3") == 0) { // 모드 3 설정
			music_mode = 3;
			puts_USART1("Mode 3 selected\r\n");
		}
		} else {
		rx_buffer[rx_index++] = rx_data; // 버퍼에 데이터 추가
		if (rx_index >= sizeof(rx_buffer)) rx_index = 0; // 버퍼 오버플로우 방지
	}
}

int main(void)
{
	DDRG = 0xff; // PORTG를 출력으로 설정
	DDRD = 0x00; // PORTD를 입력으로 설정

	// Timer 1 설정
	TCCR1A = (1 << COM1A0); // Toggle OC1A on Compare Match
	TCCR1B = (1 << WGM12) | (1 << CS10); // CTC mode, no prescaling
	OCR1A = 0; // Compare Match 값 초기화

	Init_USART1();
	sei(); // 전체 인터럽트를 활성화

	puts_USART1("Start \r\n");

	while (1)
	{
		if (music_flag) {
			switch (music_mode) {
				case 1:
				PlayMusic(NOTE1, DUR1, sizeof(NOTE1) / sizeof(int));
				break;
				case 2:
				PlayMusic(NOTE2, DUR2, sizeof(NOTE2) / sizeof(int));
				break;
				case 3:
				PlayMusic(NOTE3, DUR3, sizeof(NOTE3) / sizeof(int));
				break;
			}
			} else {
			StopSound(); // 음악 멈추기
		}
	}
}

void PlayMusic(int *notes, int *durs, int len)
{
	for (int i = 0; i < len; i++) {
		if (!music_flag) break;
		unsigned long int duration = BASE_T / (unsigned long int)durs[i];
		if (notes[i] != 0) MakeSound(notes[i]);
		else myDelay_us(duration);
	}
}

void MakeSound(int period)
{
	int duty = period >> 1; // 50% 듀티 사이클
	OCR1A = period; // Set compare match value
	OCR1B = duty; // Set duty cycle
	TCCR1A |= (1 << COM1A0) | (1 << COM1B1); // Connect OC1A pin
}

void StopSound()
{
	TCCR1A &= ~((1 << COM1A0) | (1 << COM1B1)); // Disconnect OC1A pin
}

void Init_USART1()
{
	// Set baud rate
	uint16_t ubrr = (F_CPU / 16 / 9600) - 1;
	UBRR1H = (unsigned char)(ubrr >> 8);
	UBRR1L = (unsigned char)ubrr;

	UCSR1B = (1 << RXEN1) | (1 << TXEN1); // Enable receiver and transmitter
	UCSR1B |= (1 << RXCIE1); // RX Complete Interrupt Enable
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // Set frame: 8data, 1 stop
}

void putchar_USART1(char data)
{
	while (!(UCSR1A & (1 << UDRE1))); // Wait until buffer is empty
	UDR1 = data; // Transmit data
}

void puts_USART1(const char *str)
{
	while (*str) {
		putchar_USART1(*str);
		str++;
	}
}

void myDelay_us(unsigned long int delay)
{
	unsigned long int i;
	for (i = 0; i < delay; i++) _delay_us(1);
}