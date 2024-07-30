#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>
#include <stdlib.h>

#define DO  3817 // 262Hz (3817us) 1908us
#define RE  3401 // 294Hz (3401us) 1701us
#define MI  3030 // 330Hz (3030us) 1515us
#define FA  2865 // 349Hz (2865us) 1433us
#define SOL 2551 // 370Hz (2551us) 1276us
#define LA  2273 // 440Hz (2273us) 1136us
#define SI  2024 // 494Hz (2024us) 1012us

void MakeSound(int period);
void myDelay_us(unsigned int delay);
int PushButtonDet(int number);

int main(void)
{
	DDRG = 0xff;
	
	/* Replace with your application code */
	while (1)
	{
		if(PushButtonDet(0) == 1)		MakeSound(DO);
		else if(PushButtonDet(1) == 1)	MakeSound(RE);
		else if(PushButtonDet(2) == 1)	MakeSound(MI);
		else if(PushButtonDet(3) == 1)	MakeSound(FA);
		else if(PushButtonDet(4) == 1)	MakeSound(SOL);
		else if(PushButtonDet(5) == 1)	MakeSound(LA);
		else if(PushButtonDet(6) == 1)	MakeSound(SI);
		else if(PushButtonDet(7) == 1)	MakeSound(DO>>1);
		
	}
}

void MakeSound(int period)
{
	int duty = period >> 1;	// 나누기는 연산 시간이 다른 연산 (더하기, 빼기에 비해 연산시간이 더 오래 걸림) -> 비트 연산자 사용하는 것이 좋음
	
	PORTG = PORTG | (1 << 4);	//출력
	myDelay_us(duty);	//period 절반 시간 지남
	PORTG = PORTG & ~(1 << 4);	// 0출력
	myDelay_us(duty);	// period 절반 시간 지남
}

void myDelay_us(unsigned int delay){
	int i;
	for(i=0; i<delay; i++)		_delay_us(1);
	PORTG |= (1<<4);
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)		return 1;
	
	else                                    return 0;
}