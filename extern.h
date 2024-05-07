/*
 * extern.h
 *
 * Created: 2024-04-29 오전 11:27:41
 *  Author: HARMAN-27
 */ 
#ifndef EXTERN_H_
#define EXTERN_H_
#include <stdint.h>
// led
extern void shift_left2right_keep_ledon(int* pjob);
extern void shift_right2left_keep_ledon(int* pjob);
extern void shift_left22right_keep_ledon();
extern void shift_right22left_keep_ledon();
extern void led_all_on_off();
extern void flower_on(int* pjob);
extern void flower_off(int* pjob);
extern void flower_on2();
extern void flower_off2();

// button
extern void init_button(void);
extern int get_button(int button_pin, int button_number);
extern void led_all_on_off(void);
extern void init_uart0(void);

//uart
extern void init_uart0(void);
extern void UART0_transmit(uint8_t data);
extern void pc_command_processing(void);

// uart1
extern void init_uart1(void);
extern void bit_command_processing(void);

extern volatile uint32_t shift_timer; //led.c에서도 쓰기 위위함
extern volatile uint32_t ms_count;

extern int job;

#endif /* LED_H_ */
