#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define DO  3817 // 262Hz (3817us) 1908us
#define RE  3401 // 294Hz (3401us) 1701us
#define MI  3030 // 330Hz (3030us) 1515us
#define FA  2865 // 349Hz (2865us) 1433us
#define SOL 2551 // 370Hz (2551us) 1276us
#define LA  2273 // 440Hz (2273us) 1136us
#define SI  2024 // 494Hz (2024us) 1012us

void MakeSound(int period);
void myDelay_us(unsigned int delay);

ISR (USART1_RX_vect);
void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);

// 전역 변수 선언
char RXNUM = 0; // 입력받은 숫자

// UART1 수신 인터럽트 서비스 루틴
ISR(USART1_RX_vect)
{	
	char rx_data; // 수신된 데이터를 저장할 변수
	rx_data = UDR1; // UDR1 레지스터에서 수신 데이터를 읽음
	putchar_USART1(rx_data); // 에코(수신된 데이터를 다시 송신)

	if (rx_data == '\r'){ // 수신된 데이터가 캐리지 리턴(엔터키)인 경우
		putchar_USART1('\n'); // 줄 바꿈 문자를 송신
	}
	
	else if ((rx_data >= '1') & (rx_data <= '7')) { // 수신된 데이터가 숫자인 경우
		RXNUM = rx_data;
		}
}


int main(void)
{
	DDRG = 0xff;
	DDRB = 0xff; // 포트 B를 출력으로 설정
	DDRE = 0xff; // 포트 E를 출력으로 설정
	
	Init_USART1(); // USART1 초기화
	sei(); // 글로벌 인터럽트 활성화
	
	puts_USART1("Start \r\n"); // "Start \r\n" 메시지 송신

	/* Replace with your application code */
	while (1)
	{
		if(RXNUM == '1')		MakeSound(DO);
		else if(RXNUM == '2')	MakeSound(RE);
		else if(RXNUM == '3')	MakeSound(MI);
		else if(RXNUM == '4')	MakeSound(FA);
		else if(RXNUM == '5')	MakeSound(SOL);
		else if(RXNUM == '6')	MakeSound(LA);
		else if(RXNUM == '7')	MakeSound(SI);
	}
}

void MakeSound(int period)
{
	int duty = period >> 1;	// 나누기는 연산 시간이 다른 연산 (더하기, 빼기에 비해 연산시간이 더 오래 걸림) -> 비트 연산자 사용하는 것이 좋음
	
	PORTG = PORTG | (1 << 4);	//출력
	myDelay_us(duty);	//period 절반 시간 지남
	PORTG = PORTG & ~(1 << 4);	// 0출력
	myDelay_us(duty);	// period 절반 시간 지남
	
	period = 0;
}

void myDelay_us(unsigned int delay){
	int i;
	for(i=0; i<delay; i++)		_delay_us(1);
	PORTG |= (1<<4);
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)		return 1;
	
	else                                    return 0;
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