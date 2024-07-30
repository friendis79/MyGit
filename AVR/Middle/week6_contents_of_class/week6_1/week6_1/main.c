#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

char row_scan(char row);
char key_Scan(int i);

int main(void)
{
	DDRB = 0xff;
	DDRC = 0x0f;
	
    /* Replace with your application code */
    while (1) 
    {
		/*
		PORTC = 0x0d; // 1110 -> PC3 : 1, PC2 -> 1, PC1 -> 0, PC0 -> 1 => COL2
		PORTB = PINC;
		*/
		for (int i = 0; i <4; i++)		PORTB = key_Scan(i);
    }
}

char row_scan(char row)
{
	char col = -1; // 0xff
	char pin_info;

	pin_info = PINC >> 4; // 5,6,7,8로 비트 연산자를 사용하여 자릿수를 바꿈
	
	if (row == 0)		PORTC = 0x0e;	// 1110
	else if (row == 1)	PORTC = 0x0d;	// 1101
	else if (row == 2)	PORTC = 0x0b;	// 1011
	else if (row == 3)	PORTC = 0x07;	// 0111
		
	if (pin_info == 0x1)		col = 0;	// 0001
	else if (pin_info == 0x2)	col = 1;	// 0010
	else if (pin_info == 0x4)	col = 2;	// 0100
	else if (pin_info == 0x8)	col = 3;	// 1000

	return (col);
}

char key_Scan(int i)
{
	char col;
	char key = 0xff
	
	col = row_scan(i);
		
	if(col != -1){
		key = i * 4 + col;
		return key;
		break;
		}
	}
}