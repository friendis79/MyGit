#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

// 7-세그먼트 디스플레이 문자표 (애노드 공통)
unsigned char Port_char[] = {
	0b11000000,  // 0
	0b11111001,  // 1
	0b10100100,  // 2
	0b10110000,  // 3
	0b10011001,  // 4
	0b10010010,  // 5
	0b10000010,  // 6
	0b11111000,  // 7
	0b10000000,  // 8
	0b10010000   // 9
};

// 키패드 인덱스 매핑
int key_info[16] = {
	1, 2, 3, 10,
	4, 5, 6, 11,
	7, 8, 9, 12,
	-1, 0, -2, 13
};

char row_scan(char row); // 행 스캔 함수
char key_scan(void); // 키패드 스캔 함수
void FND_Display(int number); // FND 디스플레이 함수

int main(void)
{
	// I/O 설정
	DDRB = 0xff; // 7-세그먼트 디스플레이
	DDRC = 0x0f; // 키패드
	PORTE = 0xff; // FND 제어

	// 변수 초기화
	int current_value = 0; // 현재 입력된 값

	while (1)
	{
		// 키패드 입력 처리
		char key = key_scan(); // 키패드 스캔
		if (key != -1) // 유효한 입력이 있을 경우
		{
			if (key >= 0 && key <= 9) // 숫자 입력
			{
				current_value = current_value * 10 + key; // 입력된 숫자 누적
				FND_Display(current_value); // FND 표시
			}
			else if (key == 10) // 초기화
			{
				current_value = 0; // 값 초기화
				FND_Display(current_value); // FND 표시
			}
		}
	}
}

// FND 숫자 표시 함수
void FND_Display(int number)
{
	for (int i = 0; i < 4; i++) // 각 자리에 디스플레이
	{
		int digit = (number / (int)pow(10, 3 - i)) % 10; // 자릿수 추출
		PORTB = Port_char[digit]; // 숫자 설정
		_delay_ms(1); // 딜레이
		PORTE = ~(1 << (4 + i)); // FND의 각 자리 선택
	}
}

// 키패드 행 스캔 함수
char row_scan(char row)
{
	PORTC = ~(1 << (3 - row)); // 각 행 설정
	_delay_us(10); // 안정화 시간
	
	char col = (PINC >> 4) & 0x0f; // 열 읽기
	if (col == 0x01) return 0;
	if (col == 0x02) return 1;
	if (col == 0x04) return 2;
	if (col == 0x08) return 3;
	
	return -1; // 입력이 없는 경우
}

// 키패드 스캔 함수
char key_scan()
{
	for (char row = 0; row < 4; row++) // 각 행 스캔
	{
		char col = row_scan(row); // 열 스캔
		if (col != -1)
		{
			return 4 * row + col; // 키 인덱스 반환
		}
	}
	return -1; // 입력이 없는 경우
}