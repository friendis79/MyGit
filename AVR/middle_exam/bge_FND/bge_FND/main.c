#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

char row_scan(char row);
char key_scan();
void Seg7Display(char segment);

int main(void)
{
	DDRB =0xff;
	DDRC = 0x0f; //반은 출력으로 반은 입력으로 사용(0000_1111)
	DDRE = 0xFF;
	char segment;
	
	int prev_button1 = 0;
	int prev_button2 = 0;
	
	while (1)
	{
		button1 = PushButtonDet(0);
		button2 = PushButtonDet(1);
		
		if ((prev_button1 == 0) && (button1 == 1))
		{
			if (timer_state == 0) timer_state = 1;
			else timer_state = 0;
		}

		segment  = key_scan(); //0(on)
		Seg7Display( segment);
	}
}


int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)
	return 1;
	else
	return 0;
}


char row_scan(char row) // row  0,1,2,3
{
	char col = -1; //0xff
	char pin_info;
	if (row == 0)      PORTC = 0x0e; //1110
	else if (row == 1) PORTC = 0x0d; //1101
	else if (row == 2) PORTC = 0x0b; //1011
	else if (row == 3) PORTC = 0x07; //0111
	
	_delay_us(1);
	pin_info = PINC >> 4;
	
	if (pin_info == 0x1)      col = 0; // 0001
	else if (pin_info == 0x2) col = 1; // 0010
	else if (pin_info == 0x4) col = 2; // 0100
	else if (pin_info == 0x8) col = 3; // 1000
	
	return (col); //0,1,2,3
}

char key_scan()
{
	char col;
	char row;
	char key = 0xff;
	
	for(row = 0; row <4; row ++)
	{
		col = row_scan(row);
		if (col != 0xff)
		{
			key = 4 * row +col;
			return (key);
		}
	}

	return (0xff);
}

void Seg7Display(char segment)
{
	if (segment == 3)
	PORTE = 0x80;
	else if (segment == 7)
	PORTE = 0x40;
	else if (segment == 11)
	PORTE = 0x20;
	else if (segment== 15)
	PORTE = 0x10;

	if (segment == 13)
	PORTB = 0xc0;
	else if (segment == 0)
	PORTB = 0xf9;
	else if (segment == 1)
	PORTB = 0xa4;
	else if (segment == 2)
	PORTB = 0xb0;
	else if (segment == 4)
	PORTB = 0x99;
	else if (segment == 5)
	PORTB = 0x92;
	else if (segment == 6)
	PORTB = 0x82;
	else if (segment == 8)
	PORTB = 0xd8;
	else if (segment == 9)
	PORTB = 0x80;
	else if (segment == 10)
	PORTB = 0x90;
	
	if (segment == 12)
	PORTB = PORTB - 0x80;
	else if (segment == 14)
	PORTB = PORTB - 0x0;
}