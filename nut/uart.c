
#define UART_BASE_ADDRESS  
#define UART_MCR_REG   (BASE_ADDRESS + 0x10)
#define UART_LCR_REG   (BASE_ADDRESS + 0x0c)
#define UART_USR_REG   (BASE_ADDRESS + 0x7c)
#define UART_DLL_REG   (BASE_ADDRESS + 0x00)
#define UART_THR_REG   (BASE_ADDRESS + 0x00)
#define UART_DLH_REG   (BASE_ADDRESS + 0x04)
#define UART_LSR_REG   (BASE_ADDRESS + 0x14)
#define UART_IIR_REG   (BASE_ADDRESS + 0x08)
#define UART_FIFO_CTL_REG (BASE_ADDRESS + 0x08)
#define UART_BUSY_BIT   0x01
#define UART_IER_REG   (BASE_ADDRESS + 0x04)
#define UART_RBR_REG   (BASE_ADDRESS + 0x00)
//#define UART_LCR_DLB    0x80
uint32_t uart_init_rs232(void)
{
	
	uint32_t value=0,Divisor;
	WriteRegister(UART_MCR_REG,0x50); // LOOP back is enabled and sir is enabled.
	while(ReadRegister((UART_USR_REG) & (UART_USR_BUSY_BIT));
	WriteRegister(UART_LCR_REG,0x80);//DLB is enabled.
	WriteRegister(UART_DLL_REG,0x08);
	WriteRegister(UART_DLH_REG,0x00);// setting up divisior for setting baudrate 115200 for both side RX/TX .
	WriteRegister(UART_LCR_REG,0x00);//DLB is disabled.
	WriteRegister(UART_LCR_REG,0x03);//Enable the charachters in Line control register.
	WriteRegister(UART_IER_REG,0x8f);//Enable the Interrupt enable bit.
	WriteRegister(UART_THR_REG,0xff);//Enable the Transmit HoldRegister.
	WriteRegister(UART_FIFO_CTL_REG,0x00);//disable the FIFO and THRE is set.
  return 0;
}

/* Function to transmit a char */
void uart_sendchar(unsigned char ch)
{
	
		WriteRegister(UART_RBR_REG,ch);
    while(!(UART_IER_REG & 0x02);
    WriteRegister(UART_IIR_REG,0x00);	

}
/*unsigned char uart_receive_char(void)
{
	uint8_t ch;//,value;
	
	// Wait till the data is received
	while((QWLAN_UART_UART_LSR_REG & 0x0));
	ch = ReadRegister(QWLAN_UART_UART_RBR_REG);


	 // Read received data

    return ch;
}

void uart_send_string(char *data,unsigned int size)
{
	//uint32_t value;
	while(size--)
	{
		uart_sendchar(*data++);
	}
}
unsigned int uart_receive_string(char *data)
{
	unsigned int count=0;
	while(*data == '\r')
	{
	 *data++ = uart_receive_char();
	 count++;
	}
	return count;
}*/



