// 0번 버튼을 누르고 있음에 따라 0.5초마다 5분 단위로 타이머의 시간을 설정할 수 있는 타이머

#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>

void FND_Display(int idx, int number, int dot);
void FND_Timer(int time_count);
int PushButtonDet(int number);

unsigned char Port_char[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0xbf};

int main(void)
{
	DDRD = 0; // 버튼 입력 설정
	DDRB = 0xff; // FND 출력 설정
	DDRE = 0xff; // FND 선택 설정

	PORTE = 0x80; // 초기에는 FND가 모두 꺼져있는 상태로 설정

	int time_count = 0; // 타이머 카운트 변수
	int button_press_count = 0; // 버튼 누른 횟수 카운트 변수
	int timer_started = 0; // 타이머 시작 여부 변수
	int prev_button_state = 0; // 이전 버튼 상태 저장 변수
	int stopped_time = 0; // 타이머가 정지된 시간 저장 변수
	int display_zero = 0; // FND에 0을 표시하는지 여부를 나타내는 변수
	int timer_stopped = 0; // 타이머가 정지되었는지 여부를 나타내는 변수
	int button_timer = 0; // 버튼을 누른 시간을 측정하는 타이머

	while (1)
	{
		int button_state = PushButtonDet(0); // 0번 버튼의 상태 확인

		if (!display_zero && !timer_stopped)
		{
			for (int i = 0; i < 4; i++)
			FND_Display(i, 0, 0); // 타이머가 시작되지 않았을 때 0을 표시
		}

		if (button_state == 1 && prev_button_state == 0)
		{
			button_press_count++;
			if (button_press_count == 1)
			{   // 버튼을 처음 누른 경우
				timer_started = 1;
				display_zero = 1;
				timer_stopped = 0;
				button_timer = 0;
			}
			else if (button_press_count == 2)
			{   // 버튼을 두 번째 누른 경우 (타이머 정지)
				stopped_time = time_count;
				timer_started = 0;
				button_press_count = 0;
				display_zero = 0;
				timer_stopped = 1;
				button_timer = 0;
			}
		}

		if (timer_started)
		{
			button_timer++;
			if (button_timer >= 500) // 0.5초마다
			{
				time_count += 600; // 10분씩 증가
				button_timer = 0;
			}

			FND_Timer(time_count);
			if (time_count >= 5400) // 90분 타이머 설정 (90 * 60 = 5400)
			{
				timer_started = 0;
				timer_stopped = 1;
			}
		}
		else
		{
			FND_Timer(stopped_time);
		}

		prev_button_state = button_state;

		if (PushButtonDet(1) == 1 && timer_stopped)
		{   // 1번 버튼: 타이머 초기화
			time_count = 0; // 타이머 카운트 변수
			button_press_count = 0; // 버튼 누른 횟수 카운트 변수
			timer_started = 0; // 타이머 시작 여부 변수
			prev_button_state = 0; // 이전 버튼 상태 저장 변수
			stopped_time = 0; // 타이머가 정지된 시간 저장 변수
			display_zero = 0; // FND에 0을 표시하는지 여부를 나타내는 변수
			timer_stopped = 0; // 타이머가 정지되었는지 여부를 나타내는 변수
			button_timer = 0; // 버튼을 누른 시간을 측정하는 타이머
		}

		_delay_ms(1); // 약간의 딜레이 추가하여 안정성 향상
	}
}

void FND_Display(int idx, int number, int dot)
{
	if (idx == 0)
	PORTE = 0x10;
	else if (idx == 1)
	PORTE = 0x20;
	else if (idx == 2)
	PORTE = 0x40;
	else if (idx == 3)
	PORTE = 0x80;

	PORTB = Port_char[number];

	if (dot == 1)
	PORTB = PORTB & 0x7f;
}

void FND_Timer(int time)
{
	int minutes = time / 60;
	int seconds = time % 60;

	if (minutes == 0 && seconds == 0)
	{
		FND_Display(0, 0, 0);
		FND_Display(1, 0, 0);
		FND_Display(2, 0, 0);
		FND_Display(3, 0, 0);
	}
	else
	{
		FND_Display(0, minutes / 10, 0);
		FND_Display(1, minutes % 10, 1);
		FND_Display(2, seconds / 10, 0);
		FND_Display(3, seconds % 10, 0);
	}
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x01) == 0x01)
	return 1;
	else
	return 0;
}