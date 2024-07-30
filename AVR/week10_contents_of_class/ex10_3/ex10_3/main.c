#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

#define DO  3817 // 262Hz (3817us)
#define RE  3401 // 294Hz (3401us)
#define MI  3030 // 330Hz (3030us)
#define FA  2865 // 349Hz (2865us)
#define SOL 2551 // 370Hz (2551us)
#define LA  2273 // 440Hz (2273us)
#define SI  2024 // 494Hz (2024us)

unsigned long int BASE_T = 1000000;

int NOTE[] = {SOL, SOL, LA, LA, SOL, SOL, MI, SOL, SOL, MI, MI, RE, 0,
				SOL, SOL, LA, LA, SOL, SOL, MI, SOL, MI, RE, MI, DO, 0};

int DUR[] = {4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 1, 4, 
				4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 1, 4};

void MakeSound(int period);
void MakeSound2(int period, unsigned long int duration);
void myDelay_us(unsigned long int delay);
int PushButtonDet(int number);

int main(void)
{
	DDRG = 0xff;
	DDRD = 0;
	
	int i;
	unsigned long int duration;	// 정수가 표현할 수 있는 수의 범위를 초과함 -> unsigned long int 사용
	int note_len = sizeof(NOTE) / sizeof(int);	//Data Type Table 참고
	
	
	while (1)
	{
		if (PIND != 0xff)
		{	
			if((PushButtonDet(0)))			
			{
				for (i = 0; i < note_len; i++)
				{
					duration = BASE_T/(unsigned long int)DUR[i];
					if (NOTE[i] != 0)		MakeSound2(NOTE[i], duration);
					else				myDelay_us(duration);
				}
			}
			
			else if((PushButtonDet(1)))
			{
				for (i = 0; i < note_len; i++)
				{
					duration = BASE_T/(unsigned long int)DUR[i];
					if (NOTE[i] != 0)		MakeSound2(NOTE[i]>>1, duration);
					else					myDelay_us(duration);
				}
			}
			
			else if((PushButtonDet(2)))
			{
				for (i = 0; i < note_len; i++)
				{
					duration = BASE_T/(unsigned long int)DUR[i];
					if (NOTE[i] != 0)		MakeSound2(NOTE[i]>>2, duration);
					else					myDelay_us(duration);
				}
			}
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
	unsigned long int t_elased = 0;
	int duty;
	duty = period >> 1;
	
	while(1)
	{
		PORTG = PORTG | (1 << 4);	//출력
		myDelay_us(duty);	//period 절반 시간 지남
		PORTG = PORTG & ~(1 << 4);	// 0출력
		myDelay_us(duty);	// period 절반 시간 지남
		
		t_elased += period;
		if(t_elased >= duration)	break;
	}
	_delay_ms(100);
}

void myDelay_us(unsigned long int delay){
	unsigned long int i;
	for(i=0; i<delay; i++)		_delay_us(1);
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)		return 1;
	else                                    return 0;
}