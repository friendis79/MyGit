#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

// FND 문자표 및 FND포트 핀 설정
unsigned char Port_char[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0xbf}; // 애노드 공통
int key_info[16] = {1, 2, 3, 102, 4, 5, 6, 103, 7, 8, 9, 104, 101, 0, 105, 106}; // key값을 key_info 전역변수로 만들어 저장

char row_scan(char row);
char key_scan(void);
void FND_Display(int idx, int number, int dot);
void debounce_delay(void);

int main(void)
{
	DDRB = 0xff;
	DDRC = 0x0f;
	DDRD = 0;
	DDRE = 0xff;

	PORTE = 0x80;

	int prev_key = 0xff;
	int idx = 0;
	int number[4] = {0, 0, 0, 0};
	int i;
	int operand1 = 0, operand2 = 0, result = 0;
	char operation = 0;

	/* Replace with your application code */
	while (1)
	{
		char key = key_scan();
		int key_value = key_info[key];

		if ((key != 0xff) && (prev_key == 0xff))
		{
			if ((key_value >= 0) && (key_value <= 9))
			{
				for (i = 3; i > 0; i--)
				number[i] = number[i - 1];
				number[0] = key_value;
			}
			else if (key_value == 100)
			{
				for (i = 0; i < 4; i++)
				number[i] = number[i + 1];
				number[3] = 0;
			}
			else if (key_value == 101)
			{
				for (i = 0; i < 4; i++)
				number[i] = 0;
				operand1 = operand2 = result = 0;
				operation = 0;
			}
			else if (key_value == 102 || key_value == 103 || key_value == 104 || key_value == 105)
			{
				operand1 = number[3] * 1000 + number[2] * 100 + number[1] * 10 + number[0];
				operation = key_value;
				for (i = 0; i < 4; i++)
				number[i] = 0;
			}
			else if (key_value == 106)
			{
				operand2 = number[3] * 1000 + number[2] * 100 + number[1] * 10 + number[0];
				switch (operation)
				{
					case 102:
					result = operand1 + operand2;
					break;
					case 103:
					result = operand1 - operand2;
					break;
					case 104:
					result = operand1 * operand2;
					break;
					case 105:
					if (operand2 != 0)
					result = operand1 / operand2;
					break;
					default:
					result = 0;
					break;
				}
				number[0] = result % 10;
				number[1] = (result / 10) % 10;
				number[2] = (result / 100) % 10;
				number[3] = (result / 1000) % 10;
			}
		}

		if (idx == 3)
		idx = 0;
		else
		idx++;

		FND_Display(idx, number[idx], 0);

		_delay_us(1);
		prev_key = key;
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
			debounce_delay(); // 디바운싱 딜레이 추가
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

void debounce_delay(void)
{
	_delay_ms(50); // 50ms 디바운싱 딜레이
}