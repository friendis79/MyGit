#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int tick = 0;
ISR(TIMER1_COMPA_vect) {
	tick = 1;
}
void init_timer(void) {
	TCCR1 |= (1 << WGM12); // CTC mode
	TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare interrupt
	OCR1A = 15624; // Compare value for 1s at 16MHz / 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
	sei(); // Enable global interrupts
}
void USART1_Transmit(char data) {
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = data;
}
void USART1_TransmitString(char str) {
	while (str) {
		USART1_Transmit(*str++);
	}
}
int main(void) {
	init_timer();
	USART1_TransmitString("Timer started...\n");
	while (1) {
		if (tick) {
			USART1_TransmitString("1 second passed\n");
			tick = 0;
		}
	}
}