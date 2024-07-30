#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <stdlib.h>

int NOTE[8] = {3817, 3401, 3030, 2865, 2551, 2273, 2024, 1908};
unsigned long int BASE_T = 1000000;

void MakeSound(int period);
void MakeSound2(int period, unsigned long int duration);
void myDelay_us(unsigned int delay);
int PushButtonDet(int number);

int main(void)
{
	DDRG = 0xff;
	
	int i;

	/* Replace with your application code */
	while (1)
	{
		if (PIND != 0xff)
		{
			for (i = 0; i < 8; i++)
			{
				if (PushButtonDet(i))	break;
			}
			MakeSound2(NOTE[i], BASE_T);
		}
		
	}
}

void MakeSound(int period)
{
	int duty;
	duty = period >> 1;	// 나누기는 연산 시간이 다른 연산 (더하기, 빼기에 비해 연산시간이 더 오래 걸림) -> 비트 연산자 사용하는 것이 좋음
	
	PORTG = PORTG | (1 << 4);	//출력
	myDelay_us(duty);	//period 절반 시간 지남
	PORTG = PORTG & ~(1 << 4);	// 0출력
	myDelay_us(duty);	// period 절반 시간 지남
}

void MakeSound2(int period, unsigned long int duration)
{
	int i;
	unsigned long int t_elased = 0;
	int duty;
	duty = period >> 1;
	
	while(1)
	{
		PORTG = PORTG | (1 << 4);	//출력
		for (i = 0; i < duty; i++)	_delay_us(1);	//period 절반 시간 지남
		PORTG = PORTG & ~(1 << 4);	// 0출력
		for (i = 0; i < duty; i++)	_delay_us(1);	// period 절반 시간 지남
		
		t_elased += period;
		if(t_elased >= duration)	break;
	}
	
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)		return 1;
	
	else                                    return 0;
}