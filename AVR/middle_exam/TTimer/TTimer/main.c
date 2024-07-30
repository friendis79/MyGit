#include <avr/io.h>
#define F_CPU 14745600
#include <util/delay.h>

char row_scan(char row);
char key_scan();
void SegDisplay(int idx, int number, int dot);

int main(void)
{
   DDRB = 0xff;
   DDRC = 0x0f;   //0: 입력핀, 1: 출력핀 -> 00001111 반반 나눔
   DDRE = 0xFF;
      
   PORTE = 0xFF;
   int idx = 0;
   int seg_delay = 4;   //[ms]
   int number [5] = {0,0,0,0};
   int dot[5] = {0,0,0,0};
   int dic[17] = {1,2,3, 100, 4,5,6, 101, 7,8,9, 102, 201, 0, 200, 103};
   char temp_num;
   int sel = 0;
   
    while (1) 
    {
      //PORTC = 0x0E;   //default -> 0x00, 0000_1110  -> 1열 감지
      //PORTC = 0x0D;   //0000_1101 -> 2열 감지
      //PORTB = PINC;   //0000/1101 -> led4~7은 버튼에 따라 동작 led0~3은 1101에 따라 동작 누르면 1 들어옴
      temp_num = key_scan();
      if (temp_num != 0xff)
      {
         int val = dic[temp_num];
         if((val>=0) && (val<=9))         number[sel] = val;
         else if((val>=100) && (val<=103))   sel = val - 100;
         else if((val>=200) && (val<=201))   dot[sel] = val - 200;
      }
      
      /*
      if (temp_num == 0)         number[sel] = dic[temp_num];
      else if (temp_num == 1)      number[sel] = dic[temp_num];
      else if (temp_num == 2)      number[sel] = dic[temp_num];
      else if (temp_num == 3)      sel = dic[temp_num];
      else if (temp_num == 4)      number[sel] = dic[temp_num];
      else if (temp_num == 5)      number[sel] = dic[temp_num];
      else if (temp_num == 6)      number[sel] = dic[temp_num];
      else if (temp_num == 7)      sel = dic[temp_num];
      else if (temp_num == 8)      number[sel] = dic[temp_num];
      else if (temp_num == 9)      number[sel] = dic[temp_num];
      else if (temp_num == 10)   number[sel] = dic[temp_num];
      else if (temp_num == 11)   sel = dic[temp_num];
      else if (temp_num == 12)   dot[sel] = dic[temp_num] - 200;
      else if (temp_num == 13)   number[sel] = dic[temp_num];
      else if (temp_num == 14)   dot[sel] = dic[temp_num] - 200;
      else if (temp_num == 15)   sel = dic[temp_num];
      */
      
      int number_sel = number[idx];
      int dot_sel = dot[idx];
      Seg7Display(idx, number_sel, dot_sel);
      _delay_ms(seg_delay);
      if (idx==3)
      {
         idx = 0;
      }
      else
      {
         idx ++;
      }
   }
}

//Row Scan Function 0~3
char row_scan(char row)   //row = 0, 1, 2, 3
{
   char col = 0xff;
   char pin_info; 
   
   if (row == 0)      PORTC = 0x0e;   //1110
   else if (row == 1)   PORTC = 0x0D;   //1101
   else if (row == 2)   PORTC = 0x0b;   //1011
   else if (row == 3)  PORTC = 0x07;   //0111
   
   _delay_us(1);
   
   pin_info = PINC >> 4;
   if (pin_info == 0x1)      col = 0;   //0001
   else if (pin_info == 0x2)   col = 1;   //0010
   else if (pin_info == 0x4)   col = 2;   //0100
   else if   (pin_info == 0x8)   col = 3;   //1000

   return col;      //0, 1, 2, 3
}

//KEY Scan Function   0~15
char key_scan()   //row = 0, 1, 2, 3
{
   char row;
   char col;
   char key = 0xff;
   for (row = 0; row < 4; row++)
      {
         col = row_scan(row);
         if (col != 0xff)
         {
            key = row * 4 + col;
            break;
         }
      }
   return key;
}

void Seg7Display(int idx, int number, int dot)
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
      PORTB = 0xf9;
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
   
   if (dot == 1)
      PORTB = PORTB - 0x80;
}