#ifndef UART0_H_
#define UART0_H_

//uart0로 부터 들어온 문자를 저장하는 버퍼
//interrupt루틴에서 사용하는 변수는 최적화방지를위해 volatile키워드
volatile uint8_t rx_buff[100];
//기본 : 0으로 set해줍니다
volatile uint8_t rx_ready_flag = 0; // 완전한 문장(\n)을 만나면 1로 set된다.

void init_uart0(void);
void UART0_transmit(uint8_t data);

#endif /* UART0_H_ */