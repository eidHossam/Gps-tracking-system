#include "SysTick.h"


void initClock()
{
    // Enable the GPIO port that is used for the on-board crystal oscillator
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

    // Enable the crystal oscillator by writing to the appropriate register
    SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;

    // Wait for the crystal oscillator to stabilize
    while(!(SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS));

    // Set the system clock divider to divide by 5 (to get a 16MHz clock frequency)
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400 | (1<<23);

    // Configure the system clock to use the crystal oscillator as the clock source
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_USESYSDIV;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;

    // Wait for the system clock to stabilize
    while(SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS);

    // Enable the PLL and wait for it to stabilize
    SYSCTL_RCC2_R |= (1<<13);
    while(!(SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS));

    // Set the system clock to use the PLL as the clock source
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_USESYSDIV;
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400 | (1<<23);
}

void SysTick_init(void) //intialization of SysTick Counter Timer
{
		NVIC_ST_CTRL_R = NVIC_ST_CTRL_R & ~(0x00000001); //disable Timer
		NVIC_ST_RELOAD_R = (16000000 - 1);			 //1 Second at Reload
		NVIC_ST_CURRENT_R = 0; 			        	   //Clear current to count from 0
		NVIC_ST_CTRL_R |= 0x5; 				 					//to put at source clk 1 to get PROCESOR CLK NOT its 8th only and enable Timer
}

void SysTick_wait(unsigned long delay) //Same as init but for selected delay
{ 
		NVIC_ST_CTRL_R = NVIC_ST_CTRL_R & ~(0x00000001);  
		NVIC_ST_RELOAD_R=delay-1;
		NVIC_ST_CURRENT_R=0;
		NVIC_ST_CTRL_R=0X05;
		while((NVIC_ST_CTRL_R&0x00010000)==0){}
}

void SysTick_wait_1ms(unsigned long count){
		int i; 											//Give it number of desired ms
		for(i=0;i<count;i++){
		SysTick_wait(16000); 				//Wait (count) ms
	}
}

void SysTick_wait_1us(unsigned long count){
		int i; 											//Give it number of desired us
		for(i=0;i<count;i++){
		SysTick_wait(16); 				//Wait (count) us
	}
}
