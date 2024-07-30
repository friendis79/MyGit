#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);
unsigned char getchar_USART1();
void LEDOnOff(int number, int onoff);
void process_command(char *command);

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff;

	char rx_data;
	char command[10];
	int idx = 0;
	Init_USART1();
	
	puts_USART1("Start \r\n");
	while (1)
	{
		puts_USART1("Enter Command : ");
		while (1)
		{
			rx_data = getchar_USART1();
			if (rx_data == '\r') {
				command[idx] = 0;	// 마지막 NULL 삽입
				puts_USART1("\r \n-- Received Command --");
				puts_USART1(command);
				puts_USART1("\r \n");
				idx = 0;
			
				// Command Interepreter
				if ((command[0] == 'O' && command[1] == 'N')){
					puts_USART1("ON command received \r \n");
					// 3번째 문자가 '0' ~ '7'이면 해당 LED ON
					// 그렇지 않으면, Error 처리
					for(int i = 0; i< 8; i++){
						  if(command[2] == command[i] ) LEDOnOff(i,1);
					  }
				}
				
				else if ((command[0] == 'O' && command[1] == 'F' && command[2] == 'F')){
					puts_USART1("OFF command received \r \n");	
					// 4번 째 문자가 '0' ~ '7'이면 해당 LED ON
					// 그렇지 않으면, Error 처리
					for(int i = 0; i< 8; i++){
						if(command[3] ==  command[i]) LEDOnOff(i,0);
					}
				}
				
				else{
					puts_USART1("Wrong command \r \n");
				}
				break;
				} 
			
			else {
				putchar_USART1(rx_data);
				command[idx] = rx_data;
				idx++;
			
				if(idx == 10) {
					command[idx] = rx_data; // 수신 문자 수집
					puts_USART1("\r \n -- Wrong Command -- \r \n");
					idx = 0;
					break;
				}
			}
		}
	}
}

void Init_USART1()
{
	UCSR1B |= 0b00011000;
	UBRR1L = 95;    // Baud Rate에 맞게 설정
}

void putchar_USART1(char data)
{
	while(1){
		if (UCSR1A & (1 << UDRE1)){
			UDR1 = data;
			break;
		}
	}
}

void puts_USART1(char *str)
{
	while (*str != 0){
		putchar_USART1(*str);
		str++;
	}
}

unsigned char getchar_USART1()
{
	while(1){
		if (UCSR1A & 0x80){
			return (UDR1);
		}
	}
}

void LEDOnOff (int number, int onoff)
{
	char led_state;
	led_state = ~PORTB;
	
	if (onoff == 1){
		led_state = led_state | (1 << number);
		PORTB = ~led_state;
	}
	
	else{
		led_state = led_state & ~(1 << number);
		PORTB = ~led_state;
	}
}

void process_command(char *command)
{
	if (strncmp(command, "ON", 2) == 0) {
		int led_number = atoi(&command[2]); // atoi -> string으로 저장된 값을 정수형으로 변환
		
		if (led_number >= 0 && led_number <= 7) {
			LEDOnOff(led_number, 1);
			puts_USART1("LED ");
			putchar_USART1('0' + led_number);
			puts_USART1(" ON\r\n");
			}
			
		else {
			puts_USART1("Invalid LED number\r\n");
			}
		} 
		
		else if (strncmp(command, "OFF", 3) == 0) {
			int led_number = atoi(&command[3]);
			
			if (led_number >= 0 && led_number <= 7) {
				LEDOnOff(led_number, 0);
				puts_USART1("LED ");
				putchar_USART1('0' + led_number);
				puts_USART1(" OFF\r\n");
				}
				
			else {
				puts_USART1("Invalid LED number\r\n");
			}
		} 
		
		else {
			puts_USART1("Invalid Command\r\n");
		}
}