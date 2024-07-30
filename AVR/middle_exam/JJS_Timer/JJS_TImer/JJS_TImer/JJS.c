#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

void FND_Display(int idx, int number, int dot);
char row_scan(char row);
char key_scan();
int get_value(int display_key[], int count);
void TimeDisplay(int idx, long unsigned int t);

int main(void)
{
    DDRB = 0xFF;
   DDRE = 0xF0;
   DDRD = 0x0;
   DDRC = 0x0f;
   PORTB = 0x0;
   int idx=0;
   int key;
   int seg_delay = 4;
   int Keyinfo[16] = {1,2,3,100,4,5,6,101,7,8,9,102,200,0,201,103};
   int t;
   int timer_state=0;
   int display_key[4]={0,0,0,0};
   FND_Display(0,0,0);
   
    while (1)
    { 
      key = key_scan();
      if (key != 0xff)
      {
         if ((Keyinfo[key-1] >= 0)&&(Keyinfo[key-1] <=9))
			display_key[idx] = Keyinfo[key-1];
         else if (Keyinfo[key-1] == 100)
            idx = 0;
         else if (Keyinfo[key-1] == 101)
            idx = 1;
         else if (Keyinfo[key-1] == 102)
            idx = 2;
         else if (Keyinfo[key-1] == 103)
            idx = 3;
         
         else if (Keyinfo[key-1] == 200 && timer_state == 0){
            for (int i = 0; i < 4; i++) {
               display_key[i] = 0;
            }
       }
         else if (Keyinfo[key-1] == 201){
          if(timer_state==0) timer_state = 1;
          else timer_state = 0;
       }
      }
	  
     t = get_value(display_key,3);
     TimeDisplay(idx,t);
     if(idx == 3)idx = 0;
     else idx++;
     
     if(t <= 0){
        timer_state = 0;
        t = 0;
     }
     
     if(timer_state == 1){
        _delay_ms(seg_delay);
        t -= seg_delay;
     }
   }
}

void FND_Display(int idx, int number, int dot)
{
	if (idx == 0)
	PORTE = 0x80;
	else if (idx == 1)
	PORTE = 0x40;
	else if (idx == 2)
	PORTE = 0x20;
	else if (idx == 3)
	PORTE = 0x10;
	
	if (number == 0)
	PORTB = 0xc0;
	else if (number == 1)
	PORTB = 0xF9;
	else if (number == 2)
	PORTB = 0xa4;
	else if (number == 3)
	PORTB = 0xb0;
	else if (number == 4)
	PORTB = 0x99;
	else if (number == 5)
	PORTB = 0x92;
	else if (number == 6)
	PORTB = 0x82;
	else if (number == 7)
	PORTB = 0xd8;
	else if (number == 8)
	PORTB = 0x80;
	else if (number == 9)
	PORTB = 0x90;
	
	if (dot == 1) PORTB = PORTB - 0x80;      //MSB 1000_0000는 dot 점등 유무를 나타내므로 빼줘서 켜줌(0이 키는거)
	
}

char row_scan(char row)         //char인 이유: 0,1,2,3 반환하기 위해
{
	
	char col = 0xff;
	char pin_info;
	
	if(row == 0) PORTC = 0x0e;         //1110
	else if(row == 1) PORTC = 0x0d;      //1101
	else if(row == 2) PORTC = 0x0b;      //1011
	else if(row == 3) PORTC = 0x07;      //0111         //row어디를 활성화할지? 정하고
	
	_delay_ms(1);
	
	pin_info = PINC >> 4;
	
	if (pin_info == 0x1) col =0;      //0001         //column 버튼을 누를 때 해당 값 반환한다
	else if(pin_info == 0x2) col = 1;   //0010
	else if(pin_info == 0x4) col = 2;   //0100
	else if(pin_info == 0x8) col = 3;   //1000
	
	return (col);
}

char key_scan()      //row scan 반복문 돌려서 0이 되는 곳 col과 row 조합해서 반환
{
	char key_index = 0xff;
	char col_scan;
	char row;
	for(row = 0; row< 4;row ++)
	{
		col_scan = row_scan(row);
		if(col_scan != 0xff){
			key_index = 4 * row + col_scan + 1;
			return key_index;
		}
		
	}
	return(0xff);
}

int get_value(int display_key[], int count)
{
	int v = 0;
	for (int i = 3; i >= 0; i--)
	{
		v += display_key[i] * pow(10, count);
		count -= 1;
	}
	return v;
}


void TimeDisplay(int idx, long unsigned int t)
{
	int number = 0;
	if(idx == 0) number = (t/10)%10;   //일의자리
	else if (idx == 1) number = (t/100)%10;   //십의자리
	else if (idx == 2) number = (t/1000)%10;   //백의자리
	else if (idx == 3) number = (t/10000)%10;   //천의자리
	
	//도트 표시문
	if (idx != 2) FND_Display(idx, number, 0);
	else FND_Display(idx, number, 1);
	
}