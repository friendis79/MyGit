#include <avr/io.h>
#define F_CPU 14.7456E6
#include <avr/interrupt.h>

void timer0_init();
ISR(TIMER0_OVF_vect);

int Num0TInt = 0;

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff;
	
	timer0_init();
	sei();	// UART나 Interrupt 다 포함해서 만들기 위해 사용
	/* Replace with your application code */
	while (1)
	{
	}
}

void timer0_init()
{
	// normal mode setting
	TCCR0 = 0;
	TCNT0 = 0;
	
	// TOIE (Timer Overflow Interrupt Enable)
	TIMSK |= (1<< TOIE0);
	
	// Prescale = 256
	TCCR0 |= (1 << CS02) | (1 << CS01) | (0 << CS00);
}

ISR (TIMER0_OVF_vect)
{
	Num0TInt++;
	if (Num0TInt == 225) {	// 225번이 1초
		PORTB = ~PORTB;
		Num0TInt = 0;
	}
}