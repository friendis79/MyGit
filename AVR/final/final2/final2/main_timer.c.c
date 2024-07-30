// 타이머 만들기

#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <avr/interrupt.h>

// FND 문자표 및 FND포트 핀 설정
unsigned char Port_char[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6, 0xa1,0x86,0x8e,0xbf}; // 애노드 공통

// 함수 선언
// 시간
void timer0_init();
ISR(TIMER0_COMP_vect);

// UART 통신
ISR (USART1_RX_vect);
void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);

// FND
void FND_Display(int idx, int number, int dot);
void FND_Timer(int time_cont);

// 전역 변수 선언
int SegIdx = 0; // 현재 표시할 FND 세그먼트 인덱스
int SegChangeFlag = 0; // FND 세그먼트 변경 플래그
int SegNumber[4] = {0, }; // FND에 표시할 4자리 숫자를 저장할 배열
int RXNUM[4] = {0, }; // UART로 입력받은 4자리 숫자를 임시 저장할 배열
int RXCNT = 0; // 입력받은 숫자의 개수 카운트
int time_count = 0;

// UART1 수신 인터럽트 서비스 루틴
ISR(USART1_RX_vect)
{
	char rx_data; // 수신된 데이터를 저장할 변수
	rx_data = UDR1; // UDR1 레지스터에서 수신 데이터를 읽음
	putchar_USART1(rx_data); // 에코(수신된 데이터를 다시 송신)

	if (rx_data == '\r'){ // 수신된 데이터가 엔터키인 경우
		for (int i = 0; i < 4; i++) {
			if (i < RXCNT) {
				SegNumber[i] = RXNUM[RXCNT - 1- i]; // 오른쪽에서 왼쪽으로 숫자를 채움
			}
			else {
				SegNumber[i] = 0; // 나머지 자리는 0으로 채움
			}
		}
		RXCNT = 0; // 입력 카운트를 리셋
		putchar_USART1('\n'); // 줄 바꿈 문자를 송신
	}
	else if ((rx_data >= '0') & (rx_data <= '9')) { // 수신된 데이터가 숫자인 경우
		if (RXCNT < 4) { // 입력받은 숫자가 4개 미만인 경우
			RXNUM[RXCNT] = rx_data - '0'; // 숫자를 RXNUM 배열에 저장
			RXCNT++; // 입력 카운트를 증가
		}
	}
	else if (rx_data == 'S') { // 수신된 데이터가 'S'인 경우
		if (time_count > 0)				FND_Timer(time_count);
		else if (time_count = 0)		puts_USART1("\r\n Not Ready \r\n");
	}
	else if (rx_data == 'P') {
		puts_USART1("\r\n Timer Pause \r\n");
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

	puts_USART1("\r\n Timer Program \r\n");
	
	while (1)
	{
		if(SegChangeFlag) { // 세그먼트 변경 플래그가 설정된 경우
			FND_Display(SegIdx, SegNumber[SegIdx], 0); // 현재 세그먼트에 숫자를 표시
			SegChangeFlag = 0; // 세그먼트 변경 플래그를 리셋
		}
	}
}

// 타이머0 초기화 함수
void timer0_init()
{
	// CTC (Clear Timer on Compare Match) 모드 설정
	TCCR0 |= (1 << WGM01) | (0 << WGM00);
	TCNT0 = 0; // 타이머 카운터 초기화
	OCR0 = 36; // 출력 비교 레지스터 설정 (타이머가 이 값에 도달하면 비교 인터럽트 발생)
	
	// 출력 비교 일치 인터럽트 활성화
	TIMSK |= (1 << OCIE0);
	
	// 프리스케일러 설정 (1024)
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
}

// 타이머0 비교 일치 인터럽트 서비스 루틴
ISR (TIMER0_COMP_vect) // 2.5ms 마다 호출 ※ ISR에서는 최소한의 작업만 할 것
{
	SegIdx++;
	if (SegIdx == 4)	SegIdx = 0;
	
	// FND_Display(SegIdx, SegIdx, 0);	// CPU를 덜 부하시키는 방법 1 -> 그닥 효율적이진 않음
	
	SegChangeFlag = 1;
}

// USART1 초기화 함수
void Init_USART1()
{
	UCSR1B |= (1 << RXCIE); // RXCIE 비트 (수신 완료 인터럽트 활성화)
	UCSR1B |= (1 << RXEN) | (1 << TXEN); // RXEN, TXEN 설정 (수신, 송신 활성화)
	UBRR1L = 95; // Baud Rate 설정 (9600bps 기준)
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

void FND_Display(int idx, int number, int dot){
	if (idx == 3)		PORTE = 0x10;
	else if (idx == 2)	PORTE = 0x20;
	else if (idx == 1)	PORTE = 0x40;
	else if (idx == 0)	PORTE = 0x80;
	
	PORTB = Port_char[number];
	
	if (dot == 1)		PORTB = PORTB & 0x7f;
}

void FND_Timer(int time){
	int buffer = 0;
	
	FND_Display(0, time / 1000, 0);
	buffer= time%1000;
	_delay_ms(2.5);
	
	FND_Display(1, buffer / 100, 0);
	buffer= buffer%100;
	_delay_ms(2.5);
	
	FND_Display(2, buffer / 10 , 1);
	buffer= buffer%100;
	_delay_ms(2.5);
	
	FND_Display(3, buffer % 10, 0);
	_delay_ms(2.5);
}