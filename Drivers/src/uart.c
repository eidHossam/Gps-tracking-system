#include"uart.h"
#include"tm4c123gh6pm.h"





void UART0_INIT(unsigned double boudrate)
{
unsigned int UARTFBRD,UARTIBRD;
double calc=(16000000.0)/(16.0*boudrate);
UARTIBRD=(int)calc;
UARTFBRD=(int)((calc-UARTIBRD)*64+0.5);
SYSCTL_RCGCUART_R |=0X0001;//UART0
SYSCTL_RCGCGPIO_R	|=0X0001;//PORTA
UART0_CTL_R &=~0x0001;//disable uart
UART0_IBRD_R=UARTIBRD;//BOUDRATE 9600,  CLK=16MHZ
UART0_FBRD_R=UARTFBRD;	
UART0_CTL_R=0x0301;//RXE   TXE    EN
UART0_LCRH_R |=0x0070;
GPIO_PORTA_AFSEL_R |=0x03;///PA0,PA1
GPIO_PORTA_PCTL_R =	(GPIO_PORTA_PCTL_R &0xFFFFFF00)|0x00000011;//UART PA0, PA1
GPIO_PORTA_AMSEL_R &=~0x03;
GPIO_PORTA_DEN_R |=0x03;
}
//transmitter
void UART0_writechar(char data){
while((UART0_FR_R&0x20)!=0);         //wait
UART0_DR_R=data;
}
//recieve
char UART0_readchar(){
while((UART0_FR_R&0x10)!=0);         //wait
return (char)(UART0_DR_R&0xFF);
}

void UART0_writestring(char* str){
	while(*str){
	UART0_writechar(*str);
	str++;	
}
}
void UART0_readstring(char* str,char stopchar){
char c=UART0_readchar();
while(c&&c !=stopchar){
    *str=c;
    str++;
    c=UART0_readchar();
}
*str=0x00;
}



////////////////////uart 1

void UART1_INIT(unsigned double boudrate)
{
unsigned int UARTFBRD,UARTIBRD;
double calc=(16000000.0)/(16.0*boudrate);
UARTIBRD=(int)calc;
UARTFBRD=(int)((calc-UARTIBRD)*64+0.5);
SYSCTL_RCGCUART_R |=0X0002;//UART1
SYSCTL_RCGCGPIO_R	|=0X0002;//PORTB
UART1_CTL_R &=~0x0001;//disable uart
UART1_IBRD_R=UARTIBRD;//BOUDRATE 9600,  CLK=16MHZ
UART1_FBRD_R=UARTFBRD;	
UART1_CTL_R=0x0301;//RXE   TXE    EN
UART1_LCRH_R |=0x0070;
GPIO_PORTB_AFSEL_R |=0x03;///PB0,PB1
GPIO_PORTB_PCTL_R =	(GPIO_PORTA_PCTL_R &0xFFFFFF00)|0x00000011;//UART PB0, PB1
GPIO_PORTB_AMSEL_R &=~0x03;
GPIO_PORTB_DEN_R |=0x03;
}
//transmitter
void UART1_writechar(char data){
while((UART1_FR_R&0x20)!=0);         //wait
UART1_DR_R=data;
}
//recieve
char UART1_readchar(){
while((UART1_FR_R&0x10)!=0);         //wait
return (char)(UART1_DR_R&0xFF);
}

void UART1_writestring(char* str){
	while(*str){
	UART1_writechar(*str);
	str++;	
}
}
void UART1_readstring(char* str,char stopchar){
char c=UART1_readchar();
while(c&&c !=stopchar){
    *str=c;
    str++;
    c=UART1_readchar();
}
*str=0x00;
}