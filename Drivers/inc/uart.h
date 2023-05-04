#include <string.h>
#include <stdint.h>




////////////uart0
void UART0_INIT(unsigned double boudrate);
void UART0_writechar(char data);    //transmitter
char UART0_readchar();              //recieve
void UART0_writestring(char* str);
void UART0_readstring(char* str,char stopchar);

 /////////uart1

void UART1_INIT(unsigned double boudrate);
void UART1_writechar(char data);    //transmitter
char UART1_readchar();              //recieve
void UART1_writestring(char* str);
void UART1_readstring(char* str,char stopchar);