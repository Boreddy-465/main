; int.s
; ****************************************************************************

#include "BSP/scf_constants.h"

		IMPORT IRQ_Handler
                IMPORT UART_IRQ_Handler 
		IMPORT __use_no_semihosting 
		;IMPORT __use_no_heap_region

WarmBootFlagSz	EQU	4	
ContextSize	EQU	128		


		AREA	CONTEXT_DATA, NOINIT, READWRITE, ALIGN=3
ContextMem	SPACE 	ContextSize
WarmBootFlag	SPACE 	WarmBootFlagSz
InitialContext	EQU	ContextMem + ContextSize
		
	
	;; defined in "e2e/regs/shared_data_loc.h"
Stack_Size      EQU     0x00000800
Heap_Size       EQU     0x00000000

		AREA    STACK, NOINIT, READWRITE, ALIGN=3
	
		; The linker uses these three symbols exactly as named below.
		EXPORT __initial_sp
    EXPORT __heap_base
    EXPORT __heap_limit
		EXPORT WarmBootFlag
		EXPORT InitialContext
	
__heap_base
		;**************************************************************
		; Set aside "Heap_Size" #bytes for heap usage.
		;**************************************************************		
Heap_Mem        SPACE   Heap_Size

		;**************************************************************
		; Set aside "Stack_Size" #bytes for stack usage.
		;**************************************************************	
Stack_Mem       SPACE   Stack_Size  

		;**************************************************************
		; __initial_sp points to the highest address of the stack space.
		;**************************************************************
__initial_sp
	

__heap_limit	EQU 	__heap_base +  Heap_Size

		;**********************************
		;* VECTOR TABLE                   *
		;**********************************
		PRESERVE8
		THUMB

		AREA    VECTORS, CODE, ALIGN=2
		EXPORT  ResetEntryPoint

		; Define standard ARM vector table
		EXPORT  __Vectors
		EXPORT  __Vectors_End
		EXPORT  __Vectors_Size

__Vectors
		DCD     __initial_sp                  ; Top of Stack
		DCD     ResetEntryPoint		      ; Reset Vector
		DCD     Fatal_Handler_asm             ; NMI Handler
		DCD     Fatal_Handler_asm             ; Hard Fault Handler
		DCD     Fatal_Handler_asm             ; MPU Fault Handler
		DCD     Fatal_Handler_asm             ; Bus Fault Handler
		DCD     Fatal_Handler_asm             ; Usage Fault Handler
		DCD     Fatal_Handler_asm             ; Reserved
		DCD     Fatal_Handler_asm             ; Reserved
		DCD     Fatal_Handler_asm             ; Reserved
		DCD     Fatal_Handler_asm             ; Reserved
		DCD     Fatal_Handler_asm             ; SVCall Handler
		DCD     Fatal_Handler_asm             ; Debug Monitor Handler
		DCD     Fatal_Handler_asm             ; Reserved
		DCD     Fatal_Handler_asm             ; PendSV Handler
		DCD     Fatal_Handler_asm             ; SysTick Handler

		; External Interrupts
		DCD     IRQ_Handler                   ;IRQ0
		DCD     IRQ_Handler                   ;IRQ1
		DCD     IRQ_Handler                   ;IRQ2
		DCD     UART_IRQ_Handler              ;IRQ3 UART
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
		DCD     IRQ_Handler
__Vectors_End

__Vectors_Size 	EQU 	__Vectors_End - __Vectors


ResetEntryPoint	PROC
		;might include more initial code
		;may contain temp stack stetup, m3 preloaderInit
		;mode setup; cache/MPU, Timer, ...

		;**********************************************
		; Enable SysTick
		;*********************************************
		MOV	 r0, #0xe010
		MOVT r0, #0xe000
		MOV  r1, #0
		STR  r1, [r0] ;stop the sysTick firstly
		MVN  r2, #0xff000000
		STR  r2, [r0, #4] ;reload value 0xffffff
		STR  r1, [r0, #8] ;any write to clear the CVR value
		MOV  r1, #5
		STR  r1, [r0] ;cpu clock source, systick enable

		;Jump to __main (scatter-loader engine and C/C++ library
		;initialization code) 

		; Bypass the scatter-load engine and jump directly to 
		; the C/C++ library initialization code followed by 
		; a jump to the application entry point.

		IMPORT __rt_lib_init
		IMPORT main
		IMPORT exit
		IMPORT CheckRestore
		;;;;BL CheckRestore
		BL __rt_lib_init
		BL main
		BL exit
		ENDP

		; Dummy Exception Handlers (infinite loops which can be modified)
		MACRO
		DEFAULT_HANDLER $Handler
$Handler PROC
		EXPORT $Handler				[WEAK]
		B	.
		ENDP
		MEND


Fatal_Handler_asm PROC
    IMPORT Fatal_Handler
    EXPORT Fatal_Handler_asm
    TST LR, #4
    ITE EQ
    MRSEQ R0, MSP
    MRSNE R0, PSP
    B Fatal_Handler
    ENDP

    DEFAULT_HANDLER PendSV_Handler
    ALIGN 
    END
