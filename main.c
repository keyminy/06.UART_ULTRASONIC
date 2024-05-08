/*
 * 04.TIMER_TEST.c
 *
 * Created: 2024-04-26 오후 3:23:34
 * Author : HARMAN-27
 */ 

#include "def.h"
#include "extern.h"



//stidio.h에 file구조체가 들어있다
// 1. for printf
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit,NULL, _FDEV_SETUP_WRITE);

int job = 5;

int main(void)
{
	init_timer0();
	init_uart0();
	init_uart1();
	stdout = &OUTPUT; // 2. printf가 동작되도록 stdout에 OUTPUT파일 포인터를 assign한다.
	// fprintf(stdout,"test"); == printf("test\n");
	// scanf("%s",buff); --> stdin
	// fgets(input,100,stdin); //여기서 stdin이 가리키는 것은 키보드입니다.
	
	init_ultrasonic(); // sei전에 초음파관련 initialize
	sei(); // 전역적으로 인터럽트를 허용하겠다
	
	//led A레지스터
	DDRA = 0xff; //출력모드 설정
	PORTA = 0x00; // led all off
	
	/* UART통신, main의 while문 진입전 테스트*/
	printf("UART TEST!!!!\n");

    while (1) 
    {
		// UART ISR에서, rx_ready_flag = 1;된후 
		// command parsing작업 필요
		pc_command_processing();
		bit_command_processing();
		ultrasonic_distance_check();
		
		switch(job)
		{
			case LEFT2RIGHT :
			shift_left22right_keep_ledon();
			break;
			case RIGHT2LEFT :
			shift_right22left_keep_ledon();
			break;
			case FLOWER_ON :
			flower_on2();
			break;
			case FLOWER_OFF :
			flower_off2();
			break;
			case ON_OFF:
			led_all_on_off();
			break;
			default:
			break;
		}
    }
}

