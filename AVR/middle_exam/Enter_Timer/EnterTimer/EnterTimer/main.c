#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

// FND 문자표 및 FND포트 핀 설정
unsigned char Port_char[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0xbf}; // 애노드 공통
int key_info[16] = {1, 2, 3, 100, 4, 5, 6, 101, 7, 8, 9, 102, 200, 0, 201, 103}; // key값을 key_info 전연변수로 만들어 저장

char row_scan(char row);
char key_scan(void);
void FND_Display(int idx, int number, int dot);

int main(void)
{
	DDRB = 0xff;
	DDRC = 0x0f;
	DDRD = 0;
	DDRE = 0xff;

	PORTE = 0x80;

	int countdown_value = 0; // 사용자가 입력한 카운트다운 값
	int timer_running = 0;   // 타이머 실행 여부를 추적하는 변수

	FND_Display(0, 0, 0);

	/* Replace with your application code */
	while (1)
	{
		char key = key_scan();
		int key_value = key_info[key];
		if (key != 0xff)
		{
			if (key_value == 201) // 엔터키를 누르면 타이머를 시작 또는 정지하도록 수정
			{
				if (timer_running == 0)
				{
					timer_running = 1; // 타이머 시작
				}
			}

			if (key_value == 200) // 왼쪽 하단 버튼을 누르면 카운트다운 값을 입력 받음
			{
				countdown_value = 0;
				while (1)
				{
					char key_input = key_scan();
					int key_input_value = key_info[key_input];
					if ((key_input_value >= 0) && (key_input_value <= 9))
					{
						countdown_value = countdown_value * 10 + key_input_value;
						FND_Display(0, countdown_value, 0);
					}
					else if (key_input_value == 201) // 엔터키를 누르면 입력을 완료하고 빠져나감
					{
						break;
					}
				}
			}

			if (timer_running == 1 && countdown_value > 0) // 타이머가 실행 중이고 카운트다운 값이 0보다 크면 시간을 표시하고 감소
			{
				FND_Display(0, countdown_value, 0);
				_delay_ms(1000); // 1초 대기
				countdown_value--; // 1초씩 카운트다운
			}
		}
	}
}

char row_scan(char row) // row  0,1,2,3
{
	char col = -1; //0xff
	char pin_info;
	if (row == 0)
	PORTC = 0x0e; //1110
	else if (row == 1)
	PORTC = 0x0d; //1101
	else if (row == 2)
	PORTC = 0x0b; //1011
	else if (row == 3)
	PORTC = 0x07; //0111

	_delay_us(10);

	pin_info = PINC >> 4;

	if (pin_info == 0x1)
	col = 0; // 0001
	else if (pin_info == 0x2)
	col = 1; // 0010
	else if (pin_info == 0x4)
	col = 2; // 0100
	else if (pin_info == 0x8)
	col = 3; // 1000

	return (col); //0,1,2,3
}

char key_scan()
{
	char col;
	char row;
	char key = 0xff;

	for (row = 0; row < 4; row++)
	{
		col = row_scan(row);
		if (col != 0xff)
		{
			key = 4 * row + col;
			return key; // key 변수 할당 없이 바로 반환
			break;
		}
	}

	return (0xff);
}

void FND_Display(int idx, int number, int dot)
{
	if (idx == 0)
	PORTE = 0x10;
	else if (idx == 1)
	PORTE = 0x20;
	else if (idx == 2)
	PORTE = 0x40;
	else if (idx == 3)
	PORTE = 0x80;

	PORTB = Port_char[number];

	if (dot == 1)
	PORTB = PORTB & 0x7f;
}