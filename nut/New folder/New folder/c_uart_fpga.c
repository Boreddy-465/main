/*****************************************************************************
------------------------------------------------------------------------------
------------------------------------------------------------------------------
--                                                                          --
-- QUALCOMM Proprietary                                                     --
-- Copyright (c) 1999-2008  QUALCOMM Incorporated.  All rights reserved.    --
--                                                                          --
-- All data and information contained in or disclosed by this document are  --
-- confidential and proprietary information of QUALCOMM Incorporated, and   --
-- all rights therein are expressly reserved. By accepting this material,   --
-- the recipient agrees that this material and the information contained    --
-- therein are held in confidence and in trust and will not be used,        --
-- copied, reproduced in whole or in part, nor its contents revealed in     --
-- any manner to others without the express written permission of QUALCOMM  --
-- Incorporated.                                                            --
--                                                                          --
-- This technology was exported from the United States in accordance with   --
-- the Export Administration Regulations. Diversion contrary to U.S. law    --
-- prohibited.                                                              --
--                                                                          --
------------------------------------------------------------------------------
------------------------------------------------------------------------------
-- Author      : Abhijit Mohod                                                   --
-- Description : Testcase to check the interrupt from UART to NVIC in Cortex M3                                                    --
-- Notes       :                                                            --
------------------------------------------------------------------------------
*****************************************************************************/


#include "vv_test.h"
#include "vv_test_result.h"
#include "vv_msg.h"
#include "main.h"
  #include "VVDRV_prontoss_FreqPlan.h"
  #include <rt_misc.h>

#define VV_MSG_FILE_NUMBER 0

//typedef  unsigned long int  uint32; //AM 
                                        

#define NATIVE_CTL0_ADDR  0x000FFF00
#define PASS_FLAG         0x07770000
#define FAIL_FLAG         0x09110000
#define CDAHB_VERSION_ADDR  0x011a0090


#define NVIC_BASE         0xE000E100 
#define NVIC_ICTR         0xE000E004    //Interrupt Controller type reg     
#define R_SCS_NVIC_ISER0  0xE000E100    //Irq 0 to 31 Set Enable Register
#define R_SCS_NVIC_ICER0  0xE000E180    //Irq 0 to 31 Clear Enable Register
#define R_SCS_NVIC_IABR0  0xE000E300    //Irq 0 to 31 Active Bit Register
#define R_SCS_ICSR        0xE000E300    //Interrupt Control State Register  

#define NUM_OF_INTR       0x1           //32 to 63 interrupts 
#define UART_INTR_EN      0x8  

#define CMEM_START_ADDR     0x00001000 
#define PMU_SPARE_OUT      (0x011AF490)                

#define UART_MSR 	0x01233818
#define UART_LCR	0x0123380c
#define UART_LSR	0x01233814
#define UART_FAR	0x01233870
#define UART_RBR	0x01233800
#define UART_THR	0x01233800
#define UART_DLH	0x01233804
#define UART_DLL	0x01233800	
#define UART_MCR	0x01233810
#define UART_FCR	0x01233808
#define UART_IER        0x01233804
#define UART_TFR	0x01233874		// To Transmitt data from transmit buffer if FIFO is enable
#define ROOT_CLK_ENABLE 0x011af41c
 
#define UART_RFW        0x01233878		// To Read data from RX buffer if FIFO is Enable

#define CMEM_END_ADDR     0x0007F000


extern  unsigned int err_count= 0;
extern  unsigned int err_bit= 1;  

volatile int flag = 1 ;    

int vv_test(void)
{
  // enable_fault_handlers();
  int i ; 
  int addr=0 ; 
  int wr_data = 0xFFFF003F ; 
  int dx_data = 0xFFFFFFFF ; 
  int remap_en ; 
  uint32 read_data = 0;
  uint32 read_data1 = 0;
  uint32 exp_data = 0;
  flag=1 ; 
outp(ROOT_CLK_ENABLE, 0x03EE11); // to enable root clock of UART

  
  //Configure the NVIC to support 64 interrrupts 
  outp(NVIC_ICTR, NUM_OF_INTR); 
  //Enable interrupt for UART 
   outp(R_SCS_NVIC_ISER0,UART_INTR_EN); 
   read_data= inp(R_SCS_NVIC_IABR0); 
//navneet UART testing changes Configuring MCR Register for SIR Mode/Auto Flow Control/Loopback/Modern Control o/p
	outp(UART_FCR,0x05);//enabling FIFO and seting threshold value or tx and rx buffer
//	outp(UART_FAR,0x01);  
	outp(UART_MCR,0x00);
	outp(UART_LCR,0x83); //Setting 7th bit to setbaudrate in DLH reg
	outp(UART_DLL,0x08);
	outp(UART_DLH,0x00); //setting up divisior for Setting baudrate 115200 for both side Rx/Tx . assuming DLH is DLM not DLL
	outp(UART_LCR,0x03); 
	outp(UART_IER,0x01);
	

	//for(int i=0; i<9; i++)
	//outp(UART_THR,dx_data);		// Wrting Data on transmitt buffer
	//delay();
        //To wait till interrupt is generated 
 
       while(flag)
         {
            addr=addr+1 ; 
         }
	

	delay();

	
	read_data=inp(UART_RBR);	// reading data on receive buffer 
	delay();
	outp(UART_THR,read_data+1);	
	//exp_data=dx_data;
  	if (read_data != 0xA5){ 
    	vv_test_fail(); 
    	//wr_val(NATIVE_CTL0_ADDR,FAIL_FLAG );    
	  }
  	else {
    	vv_test_pass();
    	//wr_val(NATIVE_CTL0_ADDR,PASS_FLAG );    
  	}



//   while(flag)
//    {
//   __asm__("nop");
//    }
  
    /*outp(CMEM_START_ADDR,dx_data);
    delay(); 
    read_data = inp(CMEM_START_ADDR); 
    delay(); 
    exp_data = dx_data ; 

  if (exp_data != read_data){ 
    vv_test_fail(); 
    //wr_val(NATIVE_CTL0_ADDR,FAIL_FLAG );    
  }
  else {
    vv_test_pass();
    //wr_val(NATIVE_CTL0_ADDR,PASS_FLAG );    
  }
*/
  return 0;
}

//__irq void UART_IRQ_Handler(void)
void UART_IRQ_Handler(void)
 {
  uint32 rd_data ; 
  uint32 wr_data = 0xFFFF003F ; 
  uint32 read_data1=0;
  //Disable interrupt for UART 
   outp(R_SCS_NVIC_ICER0,UART_INTR_EN); 
	outp(UART_THR,read_data1);    
    outp(A_CMEM_INT_EN,wr_data);
    delay(); 
    rd_data = inp(A_CMEM_INT_EN); 
    outp(PMU_SPARE_OUT,wr_data);
    delay(); 
    flag=0 ;  
  //return 0;
}

  void IRQ_Handler()
  {
       
    outp(CMEM_END_ADDR+0x400,0xAAAAAAAA); 
    outp(CMEM_END_ADDR+0x404,0xAAAAAAAA); 
    outp(CMEM_END_ADDR+0x408,0xAAAAAAAA); 
  }



__asm(".global __use_no_semihosting");

// dummy implementation of TTY I/O.
extern /* "C" */ void   _ttywrch(int ch) { /* No I/O supported */ return; }
// dummy implementation of C library I/O.
extern /* "C" */ char * _sys_command_string (char *cmd, int len) { return (cmd);}

extern /* "C" */ void   _sys_exit(int return_code) { /* Endless loop */ while(1) { volatile int i=0; i++ ; i--;}}
//extern /*"C"*/ void   _sys_open() {} 




