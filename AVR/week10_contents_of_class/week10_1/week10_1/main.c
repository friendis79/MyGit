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

void MakeSound(int period);
void myDelay_us(unsigned int delay);

int main(void)
{
	DDRG = 0xff;
	
    /* Replace with your application code */
    while (1) 
    {
		MakeSound(100);		
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
	for(i=0; i<delay; i++){
		_delay_us(1);
	}
}