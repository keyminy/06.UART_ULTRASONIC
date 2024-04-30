/*
 * 04.TIMER_TEST.c
 *
 * Created: 2024-04-26 오후 3:23:34
 * Author : HARMAN-27
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>   // printf scanf fgets 등이 정의 되어 있다.

#include "def.h"
#include "extern.h"

void init_timer0();
void init_uart0(void);

//stidio.h에 file구조체가 들어있다
// 1. for printf
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit,NULL, _FDEV_SETUP_WRITE);

//led를 가동해보자(전역변수 선언)
// ISR안에 쓰는 변수는 변수 type앞에 volatile써야한다.
// 이유는 최적화 방지를 위함이다.(내가 작성한 코드 일일이 수행하게 해줘)
volatile uint32_t ms_count = 0; // ms count

//타이머 관련, 전역변수로 선언
volatile uint32_t shift_timer = 0;

// 256개의 pulse(=1ms)를 count하면 이곳으로 자동적으로 진입한다.
// 즉, 256개의 pulse == 1ms
ISR(TIMER0_OVF_vect){
	/* 인터럽트 루틴을 가능한 짧게 짜라, ms_count만 증가시키고 빠져나오게함 */
	TCNT0=6; // 6 ~ 256개의 pulse카운트 --> 1ms를 맞춰주기 위해서 TCNT0을 6으로 설정
	ms_count++;
	//ms_count delay없애는 작업필요함
	shift_timer++;
}


int main(void)
{
	int job = 0; //동시 실행 문제
	init_timer0();
	init_uart0();
	stdout = &OUTPUT; // 2. printf가 동작되도록 stdout에 OUTPUT파일 포인터를 assign한다.
	// fprintf(stdout,"test"); == printf("test\n");
	// scanf("%s",buff); --> stdin
	// fgets(input,100,stdin); //여기서 stdin이 가리키는 것은 키보드입니다.
	
	sei(); // 전역적으로 인터럽트를 허용하겠다
	
	//led A레지스터
	DDRA = 0xff; //출력모드 설정
	PORTA = 0x00; // led all off
	
	/* UART통신, main의 while문 진입전 테스트*/
	//printf("UART TEST!!!!\n");

    while (1) 
    {
		// UART ISR에서, rx_ready_flag = 1;된후 
		// command parsing작업 필요
		pc_command_processing(&job);
    }
}

//timer0를 초기화 한다.
void init_timer0(){
	//8bit timer, timer 0번과 2번 사용한다.
	//분주비를 64로 설정한다.
	// 1.분주비 계산
	// 16000000Hz/64 = 250,000Hz
	
	// 2.T(주기) : pulse 1개가 잡아 먹는 시간(주파수의 역수 : 1/f)
	// 1 / 250,000 = 0.000004sec(=4us,0.004ms)
	// 3. 8bit timer overflow : 0.004ms * 256개 카운트 = 0.001024sec = 1.024ms
	// 1ms가 정확히 안되자너... 1ms가 정확히 될려면 어떻게 해야하나?
	// 0.004ms * 250 = 0.001(=1ms)
	
	//진짜 나중에 추가한 코드임
	TCNT0 = 6; // 6부터 count하는것임, TCNT : 0~256카운트하기때문에, 정확히 1ms마다 TIMER0_OVF_vect로 진입한다.
	
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00); // (1)분주비 64로 셋팅(p.296 표13-1 참고)
	TIMSK = 1 << TOIE0; // (2) TIMER0 overflow interrupt허용

	
}
