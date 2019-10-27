# include "uart.h"
#define UART_BAUD_RATE          115200
int main()
{
	//unsigned char size;
	//char *data = {"WELCOME TO XERUSSYSTEMS"};
	uart_init_rs232(UART_BAUD_RATE);
	//uart_send_string(data,sizeof(data));
	//uart_receive_string(data);
	while(1)
	{
		uart_sendchar(0x41);
		 delay();
		 delay();
		 delay();
		 delay();

		//uart_receive_char();
	}
	return 0;
}
void delay()
{
  int j ;
  for(j=0;j<100;j++);
}
