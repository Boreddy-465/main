#ifndef _UART_H
#define _UART_H
#include <stdint.h>

#define WriteRegister(_reg,_value) *((volatile unsigned long*)(_reg))= (_value)
#define ReadRegister(_reg) *((volatile long*)(_reg))
void delay();
void uart_send_string(char *data,unsigned int size);
unsigned char uart_receive_char(void);
void uart_sendchar(unsigned char ch);
unsigned int uart_receive_string(char *data);
uint32_t uart_init_rs232(uint32_t BaudRate);
#endif
