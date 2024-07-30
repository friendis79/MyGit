#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

// 7-세그먼트 문자표
const uint8_t FND_CHAR[] = {
	0xC0, // 0
	0xF9, // 1
	0xA4, // 2
	0xB0, // 3
	0x99, // 4
	0x92, // 5
	0x82, // 6
	0xF8, // 7
	0x80, // 8
	0x90  // 9
};

// FND의 각 자리를 제어하는 핀 설정
const uint8_t FND_SELECT[] = {
	0x10, // 첫 번째 자리
	0x20, // 두 번째 자리
	0x40, // 세 번째 자리
	0x80  // 네 번째 자리
};

// 키 정보(각 행과 열의 키 값을 나타냄)
int KEY_INFO[16] = {
	1, 2, 3, 100, // 첫 번째 행
	4, 5, 6, 101, // 두 번째 행
	7, 8, 9, 102, // 세 번째 행
	200, 0, 201, 103 // 네 번째 행
};

char row_scan(uint8_t row);
char key_scan(void);
void fnd_display(int value, int show_dot);
void clear_fnd(void);

int main(void)
{
	// 포트 설정
	DDRB = 0xFF; // 포트 B는 FND 제어
	DDRE = 0xF0; // 포트 E는 FND 자리 선택
	DDRC = 0x0F; // 포트 C는 키패드 제어
	DDRD = 0x00; // 포트 D는 키패드 입력

	// 변수 선언
	int value1 = 0, value2 = 0;
	int operation = -1; // -1은 초기 상태
	int result = 0;

	// 메인 루프
	while (1)
	{
		// 키 입력 확인
		char key = key_scan();
		if (key == 0xFF) continue; // 입력이 없으면 루프 계속

		int key_value = KEY_INFO[key]; // 키 값

		// 숫자 입력 처리
		if (key_value >= 0 && key_value <= 9)
		{
			if (operation == -1) // 첫 번째 숫자 입력 중
			{
				value1 = value1 * 10 + key_value; // 입력 값 누적
				fnd_display(value1, 0); // FND에 출력
			}
			else // 두 번째 숫자 입력 중
			{
				value2 = value2 * 10 + key_value;
				fnd_display(value2, 0);
			}
		}
		// 연산 처리
		else if (key_value >= 100 && key_value <= 103)
		{
			operation = key_value; // 연산 저장
		}
		// 결과 계산 및 초기화
		else if (key_value == 201) // '=' 키
		{
			switch (operation)
			{
				case 100: // 덧셈
				result = value1 + value2;
				break;
				case 101: // 뺄셈
				result = value1 - value2;
				break;
				case 102: // 곱셈
				result = value1 * value2;
				break;
				case 103: // 나눗셈
				result = (value2 == 0) ? 0 : (value1 / value2); // 0으로 나누기 방지
				break;
			}
			fnd_display(result, 0); // 결과 출력

			// 값 초기화
			value1 = 0;
			value2 = 0;
			operation = -1;
		}
		else if (key_value == 200) // 'C' 키, 초기화
		{
			clear_fnd(); // FND 초기화
			value1 = 0;
			value2 = 0;
			operation = -1;
		}
	}

	return 0;
}

char row_scan(uint8_t row)
{
	// 해당 행을 활성화하고, 열에서 입력을 읽음
	PORTC = ~(1 << row);
	_delay_us(10); // 짧은 지연
	uint8_t col = PIND >> 4; // 입력을 읽음

	if (col & 0x01) return row * 4; // 첫 번째 열
	if (col & 0x02) return row * 4 + 1; // 두 번째 열
	if (col & 0x04) return row * 4 + 2; // 세 번째 열
	if (col & 0x08) return row * 4 + 3; // 네 번째 열

	return 0xFF; // 입력이 없으면 0xFF
}

char key_scan(void)
{
	for (uint8_t row = 0; row < 4; row++)
	{
		char col = row_scan(row);
		if (col != 0xFF) return col; // 키가 눌린 경우 반환
	}
	return 0xFF; // 아무것도 눌리지 않았으면 0xFF
}

void fnd_display(int value, int show_dot)
{
	for (int i = 3; i >= 0; i--)
	{
		// 자리 선택
		PORTE = FND_SELECT[i];
		
		// 숫자 표시
		int digit = value % 10; // 마지막 자리
		PORTB = FND_CHAR[digit];
		
		// 소수점 표시
		if (show_dot)
		PORTB &= 0x7F; // 소수점 활성화
		
		value /= 10; // 다음 자리
		_delay_ms(2); // 간격 유지
	}
}

void clear_fnd(void)
{
	for (int i = 3; i >= 0; i--)
	{
		// 각 자리 초기화
		PORTE = FND_SELECT[i];
		PORTB = 0xFF; // 모든 세그먼트 끄기
		_delay_ms(2);
	}
}