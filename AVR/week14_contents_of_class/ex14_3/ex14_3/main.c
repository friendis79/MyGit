#include <avr/io.h>
#define F_CPU 14.7456E6
#include <avr/interrupt.h>

void timer0_init();
ISR(TIMER0_COMP_vect);

int Num0TInt = 0;

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff;
	
	timer0_init();
	sei();	// UART나 Interrupt 다 포함해서 만들기 위해 사용
	while (1)
	{
	}
}

void timer0_init()
{
	// CTC mode setting
	TCCR0 |= (1 << WGM01) | (0 << WGM00);
	TCNT0 = 0;
	OCR0 = 144;
	
	// OCIE (Output Compare Match Interrupt Enable)
	TIMSK |= (1 << OCIE0);
	
	// Prescale = 1024
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
}

ISR (TIMER0_COMP_vect)
{
	Num0TInt++;
	if (Num0TInt == 99) {	// 99번이 1초 -> Interrupt 1번당 10ms
		PORTB = ~PORTB;
		Num0TInt = 0;
	}
}