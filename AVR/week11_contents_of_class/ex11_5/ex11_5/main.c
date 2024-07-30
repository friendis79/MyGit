#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <stdlib.h> // atoi 함수 사용하기 위해 include
#include <string.h> // strcmp 함수 사용하기 위해 include

void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);
unsigned char getchar_USART1();
void LEDOnOff(int number, int onoff); // 1 -> LED ON, 0 -> LED OFF
void process_command(char *command);

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff;

	char rx_data;
	char command_buffer[10];
	int buffer_index = 0;
	Init_USART1();
	
	puts_USART1("Start \r\n");
	while (1)
	{
		rx_data = getchar_USART1();
		putchar_USART1(rx_data);
		if (rx_data == '\r') {
			putchar_USART1('\n');
			command_buffer[buffer_index] = '\0';
			process_command(command_buffer);
			buffer_index = 0;
			} 
			
		else {
			command_buffer[buffer_index++] = rx_data;
			if (buffer_index >= sizeof(command_buffer) - 1) {
				buffer_index = 0; // prevent overflow
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

/* atoi = int string_to_int(char *str, int start)
{
	int result = 0;
	while (str[start] >= '0' && str[start] <= '9') {
		result = result * 10 + (str[start] - '0');
		start++;
	}
	return result;
}
*/

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