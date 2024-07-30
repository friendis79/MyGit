#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

// FND 문자표 설정 (각 숫자에 대응하는 7세그먼트 코드)
unsigned char Port_char[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf};

// 함수 선언
int PushButtonDet(int number);
void FND_Display(int idx, int number, int dot);
void FND_cnt(int cnt);

int main(void)
{
	DDRB = 0xff; // 포트 B를 출력으로 설정
	DDRE = 0xff; // 포트 E를 출력으로 설정
	
	PORTB = 0xff; // 포트 B를 초기화 (모든 세그먼트를 끔)
	PORTE = 0x80; // 포트 E를 초기화 (첫 번째 세그먼트를 켬)
	
	int cnt = 0;
	
	while (1)
	{
		if(PushButtonDet(0)) {
			cnt++;
			FND_cnt(cnt);
		}
		else if (PushButtonDet(1)) {
			cnt = 0;
			FND_cnt(cnt);
		}
		else FND_cnt(cnt);
		
	_delay_ms(1);
	}
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1) // 비트 연산자 (~) : 0000 0000 -> 1111 1111
	return 1;
	
	else
	return 0;
}

void FND_cnt(int cnt)
{
	int buffer = 0;
	
	FND_Display(0, cnt / 1000, 0);
	buffer = cnt;
	_delay_ms(2.5);
	
	FND_Display(1, buffer / 100, 0);
	buffer = cnt;
	_delay_ms(2.5);
	
	FND_Display(2, buffer / 10, 0);
	buffer = cnt;
	_delay_ms(2.5);
	
	FND_Display(3, buffer, 0);
	_delay_ms(2.5);
}

// FND에 숫자 표시 함수
void FND_Display(int idx, int number, int dot)
{
	if (idx == 0)        PORTE = 0x10; // 첫 번째 세그먼트 선택
	else if (idx == 1)   PORTE = 0x20; // 두 번째 세그먼트 선택
	else if (idx == 2)   PORTE = 0x40; // 세 번째 세그먼트 선택
	else if (idx == 3)   PORTE = 0x80; // 네 번째 세그먼트 선택

	PORTB = Port_char[number]; // 숫자에 해당하는 7세그먼트 코드 출력
	
	if (dot == 1)        PORTB = PORTB & 0x7f; // 점 표시 (dot 플래그가 설정된 경우)
}