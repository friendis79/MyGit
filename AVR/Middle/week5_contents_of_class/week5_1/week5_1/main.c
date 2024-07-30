// 제일 오른 쪽 장치에서 1초 간격으로 0~F를 반복 출력

#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

void FND_Display(int idx, int number, int dot);

// FND 문자표 및 FND포트 핀 설정
unsigned char Port_char[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6, 0xa1,0x86,0x8e,0xbf}; // 애노드 공통

int main(void)
{
	DDRB = 0xff;
	DDRE = 0xff;
	
	PORTE = 0x80;
	
	int time_count = 0;
	
    /* Replace with your application code */
	while(1)
	{
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 16; j++){
				FND_Display(i, time_count, 0);
				time_count++;
				_delay_ms(250);
			}
			time_count = 0;
		}
	}
}

void FND_Display(int idx, int number, int dot){
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