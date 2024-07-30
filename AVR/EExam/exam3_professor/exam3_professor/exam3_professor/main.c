#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

unsigned char Word[8][4] = {{'P', 'L', 'A', 'y'}, {'H', 'E', 'L', 'P'}, {'G', 'o', 'o', 'd'}, {'C', 'o', 'o', 'L'},
							{'S', 'U', 'r', 'E'},{'O', 'P', 'E', 'n'}, {'L', 'I', 'F', 'E'}, {'C', 'o', 'd', 'E'}};

void FND_Display(int idx, char c);
int PushButtonDet (int number);

int main(void)
{
	DDRB = 0xff;
	DDRC = 0x0f;
	DDRD = 0;
	DDRE = 0xff;

	PORTE = 0x80;
	
	int idx = 0;
	int word_idx = 0;
	int i;
	/* Replace with your application code */
	while (1)
	{	
		if (idx == 3)	idx = 0;
		else            idx++;
		
		for (i = 0; i < 8; i++)
		{
			if(PushButtonDet(i))
			{
				word_idx = i;
				break;
			}
		}
		FND_Display(idx, Word[word_idx][idx]);
		_delay_ms(2.5);
	}
}

void FND_Display(int idx, char c)
{
	if (idx == 0)
	PORTE = 0x10;
	else if (idx == 1)
	PORTE = 0x20;
	else if (idx == 2)
	PORTE = 0x40;
	else if (idx == 3)
	PORTE = 0x80;

	switch (c)
	{
		case 'P' : PORTB = ~0x73;	break;
		case 'L' : PORTB = ~0x38;	break;
		case 'A' : PORTB = ~0x77;	break;
		case 'y' : PORTB = ~0x6e;	break;
		case 'H' : PORTB = ~0x76;	break;
		case 'E' : PORTB = ~0x79;	break;
		case 'G' : PORTB = ~0x3d;	break;
		case 'o' : PORTB = ~0x5c;	break;
		case 'd' : PORTB = ~0x5e;	break;
		case 'C' : PORTB = ~0x39;	break;
		case 'S' : PORTB = ~0x6d;	break;
		case 'U' : PORTB = ~0x3e;	break;
		case 'r' : PORTB = ~0x50;	break;
		case 'O' : PORTB = ~0x3f;	break;
		case 'n' : PORTB = ~0x54;	break;
		case 'I' : PORTB = ~0x30;	break;
		case 'F' : PORTB = ~0x71;	break;
		default :  PORTB = 0xff; 
	}
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1) // 비트 연산자 (~) : 0000 0000 -> 1111 1111
	return 1;
	
	else
	return 0;
}