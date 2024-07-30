#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>


// FND 문자표 및 FND포트 핀 설정
unsigned char Port_char[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90}; // 애노드 공통
int key_info[16] = {1, 2, 3, 100, 4, 5, 6, 101, 7, 8, 9, 102, 200, 0, 201, 103}; // key값을 key_info 전역변수로 저장

char row_scan(char row);
char key_scan(void);
void FND_Display(int mins);

volatile int minutes = 0;  // 분을 저장할 변수
volatile int seconds = 0;  // 카운트 다운 시 사용할 초 변수

int main(void)
{
	DDRB = 0xff;  // FND 포트
	DDRC = 0x0f;  // 키패드 포트
	DDRE = 0xff;  // FND 디지털 라인 포트

	while (1)
	{
		// 타이머 구현
		if (seconds <= 0 && minutes > 0)
		{
			seconds = 60;  // 1분 = 60초
			minutes--;  // 1분 감소
		}
		
		if (seconds > 0)
		{
			_delay_ms(1000);  // 1초 대기
			seconds--;  // 1초 감소
		}

		// FND 디스플레이
		FND_Display(minutes);

		// 키패드 입력을 통한 시간 설정
		char key = key_scan();
		if (key != 0xff)
		{
			if ((key_info[key] >= 0) && (key_info[key] <= 9))
			{
				minutes = key_info[key];  // 분을 키패드로 설정
				seconds = 0;  // 초 초기화
			}
		}
	}
}

char row_scan(char row)
{
	char col = -1;
	if (row == 0)
	PORTC = 0x0e;
	else if (row == 1)
	PORTC = 0x0d;
	else if (row == 2)
	PORTC = 0x0b;
	else if (row == 3)
	PORTC = 0x07;

	_delay_us(10);
	
	char pin_info = PINC >> 4;

	if (pin_info == 0x1)
	col = 0;
	else if (pin_info == 0x2)
	col = 1;
	else if (pin_info == 0x4)
	col = 2;
	else if (pin_info == 0x8)
	col = 3;

	return col;
}

char key_scan()
{
	for (char row = 0; row < 4; row++)
	{
		char col = row_scan(row);
		if (col != 0xff)
		{
			return 4 * row + col;  // 키패드 위치 반환
		}
	}
	return 0xff;  // 키패드 입력이 없을 경우
}

void FND_Display(int mins)
{
	if (mins >= 10)  // 두 자리 수 처리
	{
		PORTB = Port_char[(mins / 10)];
		PORTE = 0x10;  // 첫 번째 자리
		_delay_ms(500);
	}

	PORTB = Port_char[(mins % 10)];
	PORTE = 0x20;  // 두 번째 자리
	_delay_ms(500);
}