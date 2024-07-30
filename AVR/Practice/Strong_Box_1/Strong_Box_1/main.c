#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <stdlib.h>

#define DO  1908 // 262Hz (3817us) 1908us
#define RE  1700 // 294Hz (3401us) 1701us
#define MI  1515 // 330Hz (3030us) 1515us
#define FA  1432 // 349Hz (2865us) 1433us
#define SOL 1275 // 370Hz (2703us) 1351us
#define LA  1136 // 440Hz (2273us) 1136us
#define SI  1012 // 494Hz (2024us) 1012us

// FND 문자표 및 FND포트 핀 설정
unsigned char Port_char[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc4, 0xa1,0x84,0x8e,0xbf}; // 애노드 공통
//port_char 16번째 데이터는 - 표시임을 추가함
unsigned int Port_FND[] ={0x1f,0x2f,0x4f,0x8f}; // FND0 ON, FND1 ON, FND2 ON, FND3 ON
    
unsigned char My_Pass[] ={2,3,0,7}; // password

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
    unsigned char key_scan_line = 0xfe; // 첫 번째 행을 활성화
    unsigned char key_scan_loop=0, getpinData=0, key_num=0;
   
    for(key_scan_loop=0; key_scan_loop<4; key_scan_loop++) {
        PORTC = key_scan_line;
        _delay_ms(1);
      
        getpinData = PINC & 0x0f; // 열의 입력을 읽음
        if(getpinData != 0x0f) { // 입력이 발견되면
            switch(getpinData) {
                case 0x0e: // 첫 번째 열이 활성화된 경우
                    key_num=key_scan_loop*4+1;
                    break;
                case 0x0d: // 두 번째 열이 활성화된 경우
                    key_num=key_scan_loop*4+2;
                    break;
                case 0x0b: // 세 번째 열이 활성화된 경우
                    key_num=key_scan_loop*4+3;
                    break;
                case 0x07: // 네 번째 열이 활성화된 경우
                    key_num=key_scan_loop*4+4;
                    break;
                default:
                    break;
            }
            return key_num;
        } 
        key_scan_line = (key_scan_line << 1); // 다음 행으로 이동
    } 
    return 0;
}


unsigned char key_decodes(unsigned int key_in)
{
   //숫자가 입력되면 키패드의 숫자를 0~9로 바꾸고, 나머지 숫자는 연산자로 바꿈
   unsigned char Key_Num = 0;
   
   if(key_in) {//key_in 값이 입력이 되었을 때
      if(key_in%4 != 0) {
         Key_Num = (key_in/4)*3 + (key_in%4);
         
         if(Key_Num >= 10) {
            switch(Key_Num) {
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

void Error_FND(void)
{
   unsigned char FND_Out_Num=0;
   
   for(FND_Out_Num=0; FND_Out_Num<4; FND_Out_Num++) {
      PORTE = Port_FND[FND_Out_Num];
      PORTB = Port_char[16];
      _delay_ms(2.5);   
   }
}

void myDelay_us(unsigned int delay){
    int i;
    for(i=0; i<delay; i++){
        _delay_us(1);
    }
}

void SSound(int time) {
    int i, tim;
    tim = 50000 / time;
    for(i=0; i<tim; i++) {
        PORTG |= (1<<PG4); //buzzer on, PORTG의 4번 핀 off(out 1)
        myDelay_us(time);
        PORTG &= ~(1<<PG4); //buzzer off, PORTG의 4번 핀 on(out 0)
        myDelay_us(time);
    }
    PORTG |= (1<<PG4); //buzzer off, PORTG의 4번 핀 off(out 0)
}

int main(void)
{
   unsigned char FND_Print[4] = {0,};
   unsigned char value1[4] = {0,}, value2[4] = {0,};
   
   int key_in_value = 0, COMP_Pass=0;
   
   int value_1=0 ,value_2=0;
   
   unsigned char Key_In_OVF=0, Key_off_flag=0;
   unsigned char calculation=0, negative_flag=0;;
   
   PORT_Init();
    
    DDRG |= (1<<PG4);   // 부저와 연결되는 PORTG.4를 출력으로 설정!
    PORTG |= (1<<PG4);  // 교육용 보드의 BUZZ는 회로가 Active-Low 로 되어있음으로 HIGH 상태 출력하여 부저 동작을 차단함.

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
               /*
                    if(value2[3] == 0)
               {
                  if(Key_off_flag)
                  {
                     value2[3] = value2[2];
                     value2[2] = value2[1];
                     value2[1] = value2[0];
                                    
                     Key_off_flag = 0;
                  }
                  else;
                                 
                  value2[0] = key_in_value;
                  key_in_value = value_2 = 1000*value2[3] + 100*value2[2] + 10*value2[1] + value2[0];
                                 
               }
               else
                  key_in_value = value_2; //1000*value2[3] + 100*value2[2] + 10*value2[1] + value2[0];   
               */               
            }
            else
            {
               if(value1[3] == 0)
               {               
                  if(Key_off_flag)
                  {
                        value1[3] = value1[2];
                        value1[2] = value1[1];
                        value1[1] = value1[0];
                              
                        Key_off_flag = 0;
                  }
                  else;
                  
                  value1[0] = key_in_value;
                  key_in_value = value_1 = 1000*value1[3] + 100*value1[2] + 10*value1[1] + value1[0];
                  
               }
               else
                  key_in_value = value_1; // 1000*value1[3] + 100*value1[2] + 10*value1[1] + value1[0];            
            }
         }
         else
         {
               
            if(key_in_value == 20)
            {
               key_in_value=calculation=negative_flag=value_1=value_2=Key_In_OVF=0;
                            
               for(int i=0;i<4;i++)
                  value1[i] = value2[i] = 0;

            }
            else if(key_in_value == 30)
            {
                    
                    COMP_Pass = My_Pass[0]*1000 + My_Pass[1]*100 + My_Pass[2]*10 + My_Pass[3];
                    
                    if(abs(COMP_Pass - value_1))
                    {
                        PORTE = 0xF0;
                        PORTB = Port_char[16];
                        
                        SSound(DO);
                        _delay_ms(1);
                        SSound(DO);  
                    }
                    else
                    {
                        PORTE = 0x60;
                        PORTB = 0xDC;
                        
                        SSound(DO/2);  
                        SSound(RE/2);
                        SSound(MI/2);
                        SSound(FA/2);
                        SSound(SOL/2);
                        SSound(LA/2);
                        SSound(SI/2);
                        SSound(DO/4);                         
                    }
                    
                    
                    for(int i=0;i<4;i++)
                        value1[i] = 0;
                    
                    key_in_value = 0;
                    
               /*
               switch(calculation)
               {
                  case 10: key_in_value = value_1 - value_2;
                  
                           //negative num 예외 처리
                           if(key_in_value < 0 )
                           {
                              //key_in_value *=-1;
                              key_in_value = abs(key_in_value);
                              negative_flag=1;

                           }
                           else
                           negative_flag=0;
                  
                      break;
                  case 11: key_in_value = value_1 * value_2;
                     break;
                  case 12: 
                         if(value_2 == 0)
                           key_in_value = 0;
                         else
                           key_in_value = value_1 / value_2;
                     break;
                  case 13: key_in_value = value_1 + value_2;
                     break;
                  default: key_in_value =0;
                     break;
               }
               
               if(key_in_value>9999)
                  Key_In_OVF=1;
               else
                  Key_In_OVF=0;   
                        
                    */
            }
            else if(key_in_value <= 13 && key_in_value >= 10)
            {
               calculation = key_in_value;
               key_in_value = value_1;
            }
            else;
         }
                  
         Num_divide(FND_Print, key_in_value);
      }
      else
         Key_off_flag=1;
      

      if(Key_In_OVF)
      {
         //Key_In_OVF = 0;
         Error_FND();
      }   
      else
      {
         PORTE = Port_FND[0];
         PORTB = Port_char[FND_Print[0]] + (negative_flag*0x80); //negative num 표시 dot 으로 정의
         _delay_ms(2.5);
               
         PORTE = Port_FND[1];
         PORTB = Port_char[FND_Print[1]];
         _delay_ms(2.5);
               
         PORTE = Port_FND[2];
         PORTB = Port_char[FND_Print[2]];
         _delay_ms(2.5);
               
         PORTE = Port_FND[3];
         PORTB = Port_char[FND_Print[3]];
         _delay_ms(2.5);
      }
    }
}