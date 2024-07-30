#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

void InterruptInit();
ISR(INT0_vect);
ISR(INT1_vect);
int PushButtonDet(int number);

void Init_USART1();
void putchar_USART1(char data);
void puts_USART1(char *str);
unsigned char getchar_USART1();
void LEDOnOff(int number, int onoff);

int BtnPressed = 0;

int main(void)
{
	DDRB = 0xff;  // Set PORTB as output
	DDRD = 0x0;   // Set PORTD as input

	PORTB = 0xff; // Turn off all LEDs initially

	InterruptInit();

	char rx_data;
	Init_USART1();

	puts_USART1("Start \r\n");

	while (1)
	{
		if (BtnPressed) {
			PORTB = ~(1 << ((~PORTB & 0xff) + 1) % 8);
			BtnPressed = 0;
		}

		rx_data = getchar_USART1();
		putchar_USART1(rx_data);
		if (rx_data == '\r') putchar_USART1('\n');

		if ((rx_data >= '0') && (rx_data <= '7')) {
			LEDOnOff(rx_data - '0', 1);
			} else if (rx_data == 'q') {
			PORTB = 0xff;
		}
	}
}

ISR(INT0_vect)
{
	_delay_ms(100);
	if (!PushButtonDet(0)) BtnPressed = 1;
	EIFR = 1 << INTF0;
}

ISR(INT1_vect)
{
	_delay_ms(100);
	if (PushButtonDet(1)) BtnPressed = 1;
	EIFR = 1 << INTF1;
}

void InterruptInit()
{
	EICRA = (1 << ISC01) | (1 << ISC11) | (1 << ISC10); // Falling edge on INT0, Rising edge on INT1
	EIMSK = (1 << INT0) | (1 << INT1);
	sei(); // Enable global interrupts
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)
	return 1;
	else
	return 0;
}

void Init_USART1()
{
	UCSR1B |= 0b00011000; // Enable transmitter and receiver
	UBRR1L = 95; // Set baud rate for 14.7456 MHz and 9600 baud
}

void putchar_USART1(char data)
{
	while (!(UCSR1A & 0b00100000)); // Wait for empty transmit buffer
	UDR1 = data; // Send data
}

void puts_USART1(char *str)
{
	while (*str != 0) {
		putchar_USART1(*str);
		str++;
	}
}

unsigned char getchar_USART1()
{
	while (!(UCSR1A & 0x80)); // Wait for data to be received
	return UDR1;
}

void LEDOnOff(int number, int onoff)
{
	char led_state = ~PORTB;

	if (onoff == 1) {
		led_state |= (1 << number);
		PORTB = ~led_state;
		} else {
		led_state &= ~(1 << number);
		PORTB = ~led_state;
	}
}