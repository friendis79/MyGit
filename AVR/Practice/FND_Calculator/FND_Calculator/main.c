#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

// FND 문자표 및 FND포트 핀 설정
unsigned char Port_char[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6, 0xa1,0x86,0x8e,0xbf}; // 애노드 공통
//port_char 16번째 데이터는 - 표시임을 추가함
unsigned int Port_fnd[] ={0x1f,0x2f,0x4f,0x8f}; // FND0 ON, FND1 ON, FND2 ON, FND3 ON

void PORT_Init(void)
{
	DDRE = 0xf0; // PORTE4~PORTE7 FND 출력 선택
	// (PE4 : FND0, PE5, FND1, PE6 : FND2, PE7 : FND3)
	DDRB = 0xff; // 세그먼트의 문자포트 출력
	// (PB0:a, PB1:b, PB2:c, PB3:d, PB4:e, PB5:f, PB6:g, PB7:dot)
	DDRC = 0x0f;
}

void Num_divide(unsigned char* divide_num, unsigned int num)
{
	int buffer=0;

	divide_num[3] = num/1000;
	buffer= num%1000;
	divide_num[2] = buffer/100;
	buffer= buffer%100;
	divide_num[1] = buffer/10;
	divide_num[0] = buffer%10;
}

unsigned char keyScan(void)
{
	unsigned char key_scan_line = 0xF7;
	unsigned char key_scan_loop=0, getpinData=0, key_num=0;

	for(key_scan_loop=0; key_scan_loop<4; key_scan_loop++)
	{
		PORTC = key_scan_line;
		_delay_ms(1);

		getpinData = PINC & 0xF0;
		if(getpinData != 0)
		{
			switch(getpinData)
			{
				case 0x10:
				key_num=key_scan_loop*4+1;
				break;
				case 0x20:
				key_num=key_scan_loop*4+2;
				break;
				case 0x40:
				key_num=key_scan_loop*4+3;
				break;
				case 0x80:
				key_num=key_scan_loop*4+4;
				break;
				default:
				break;
			} return key_num;
		} key_scan_line = (key_scan_line >> 1);
	} return 0;
}

unsigned char key_decodes(unsigned int key_in)
{
	//숫자가 입력되면 키패드의 숫자를 0~9로 바꿈
	unsigned char Key_Num = 0;

	if(key_in) //key_in 값이 입력이 되었을 때
	{
		if(key_in%4 != 0)
		{
			Key_Num = (key_in/4)*3 + (key_in%4);

			if(Key_Num >= 10)
			{
				switch(Key_Num)
				{
					case 10:
					Key_Num = 20;
					break;
					case 11:
					Key_Num = 0;
					break;
					case 12:
					Key_Num = 30;
					break;
					default:break;
				}
			}
			else;
		}
		else
		Key_Num = (key_in/4)+9;
	}
	else;

	return Key_Num;
}

int main(void)
{
	unsigned char FND_Print[4] = {0,};
	unsigned char value1[4] = {0,}, value2[4] = {0,};

	int key_in_value = 0;

	int value_2=0;

	unsigned char calculation=0, negative_flag=0;;

	PORT_Init();

	/* Replace with your application code */
	while (1)
	{

		key_in_value = keyScan();
		_delay_ms(20);

		if(key_in_value)
		{

			key_in_value = (int)key_decodes(key_in_value);

			if(key_in_value < 10)
			{

				if(calculation)
				{
					if(value2[3] == 0)
					{
							value2[3] = value2[2]; // 입력되는 숫자를 왼쪽으로 옮겨 줌
							value2[2] = value2[1];
							value2[1] = value2[0];
						}
						else;

						value2[0] = key_in_value;
						key_in_value = value_2 = 1000*value2[3] + 100*value2[2] + 10*value2[1] + value2[0];

					}
					else
					key_in_value = value_2; //1000*value2[3] + 100*value2[2] + 10*value2[1] + value2[0];
				}
			}
		else
		{
			PORTE = Port_fnd[0];
			PORTB = Port_char[FND_Print[0]] + (negative_flag*0x80); //negative num 표시 dot 으로 정의
			_delay_ms(2.5);

			PORTE = Port_fnd[1];
			PORTB = Port_char[FND_Print[1]];
			_delay_ms(10);

			PORTE = Port_fnd[2];
			PORTB = Port_char[FND_Print[2]];
			_delay_ms(2.5);

			PORTE = Port_fnd[3];
			PORTB = Port_char[FND_Print[3]];
			_delay_ms(2.5);
		}
	}
}