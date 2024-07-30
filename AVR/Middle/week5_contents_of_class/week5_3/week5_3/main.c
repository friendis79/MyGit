// 스탑워치 만들기

#include <avr/io.h>
#define F_CPU 14.7456E6
#include <util/delay.h>

void FND_Display(int idx, int number, int dot);
void FND_Timer(int time_conut);
int PushButtonDet (int number);

// FND 문자표 및 FND포트 핀 설정
unsigned char Port_char[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6, 0xa1,0x86,0x8e,0xbf}; // 애노드 공통

int main(void)
{
	DDRD = 0;
	DDRB = 0xff;
	DDRE = 0xff;
	
	PORTE = 0x80;
	
	int time_count = 0;
	int button_press_count = 0; // 버튼 누름 횟수를 나타내는 변수
	int timer_started = 0; // 타이머 시작 여부를 나타내는 변수
	int prev_button_state = 0; // 이전 버튼 상태를 저장하는 변수
	int stopped_time = 0; // 타이머가 멈춘 시간을 나타내는 변수
	int display_zero = 0; // 초기화를 기다리는 동안 0을 표시할 변수
	int timer_stopped = 0; // 타이머가 멈추었는지를 나타내는 변수

	while (1) {
		int button_state = PushButtonDet(0); // 현재 버튼 상태 확인

		// 0번 버튼이 눌리지 않았을 때만 0을 표시하고 타이머가 실행 중이 아니면 초기화 가능
		if (!display_zero && !timer_stopped) {
			for (int i = 0; i < 4; i++) {
				FND_Display(i, 0, 0);
			}
		}

		// 버튼이 눌린 상태에서 이전에 눌리지 않았을 경우
		if (button_state == 1 && prev_button_state == 0) {
			button_press_count++;
			if (button_press_count == 1) { // 0번 버튼을 처음 누른 경우
				timer_started = 1; // 타이머 시작
				display_zero = 1; // 0 표시 중지
				timer_stopped = 0; // 타이머 멈춤 상태 해제
				}
				
			else if (button_press_count == 2) { // 0번 버튼을 두 번째 누른 경우
				stopped_time = time_count; // 타이머가 멈춘 시간 기록
				timer_started = 0; // 타이머 멈춤
				button_press_count = 0; // 버튼 누름 횟수 초기화
				display_zero = 0; // 0 표시 시작
				timer_stopped = 1; // 타이머 멈춤 상태 설정
			}
		}

		if (timer_started) { // 타이머가 시작된 경우에만 실행
			FND_Timer(time_count);
			time_count++;
			}
			
		else { // 타이머가 멈춘 경우
			FND_Timer(stopped_time); // 멈춘 시간 표시
		}

		prev_button_state = button_state; // 현재 버튼 상태를 이전 버튼 상태로 저장

		// 1번 버튼을 누를 경우 초기화
		if (PushButtonDet(1) == 1 && !timer_started) { // 타이머가 실행 중이 아닐 때만 초기화 가능
			time_count = 0;
			button_press_count = 0; // 버튼 누름 횟수를 나타내는 변수
			timer_started = 0; // 타이머 시작 여부를 나타내는 변수
			prev_button_state = 0; // 이전 버튼 상태를 저장하는 변수
			stopped_time = 0; // 타이머가 멈춘 시간을 나타내는 변수
			display_zero = 0; // 0 표시 시작
			timer_stopped = 0; // 타이머 멈춤 상태 해제
		}
	}
}

void FND_Display(int idx, int number, int dot){
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

void FND_Timer(int time){
	int buffer = 0;
	
	FND_Display(0, time / 1000, 0);
	buffer= time%1000;
	_delay_ms(2.5);
			
	FND_Display(1, buffer / 100, 1);
	buffer= buffer%100;
	_delay_ms(2.5);
			
	FND_Display(2, buffer / 10 , 0);
	buffer= buffer%100;
	_delay_ms(2.5);
			
	FND_Display(3, buffer % 10, 0);
	_delay_ms(2.5);
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1) // 비트 연산자 (~) : 0000 0000 -> 1111 1111
		return 1;
	
	else
		return 0;
}