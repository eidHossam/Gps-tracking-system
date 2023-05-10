#include "Delay.h"
void SysTick_wait(unsigned long delay){
NVIC_ST_CTRL_R=0;
NVIC_ST_RELOAD_R=delay-1;
NVIC_ST_CURRENT_R=0;
NVIC_ST_CTRL_R=0X05;
while((NVIC_ST_CTRL_R&0x00010000)==0){}
}

void SysTick_wait_loop(unsigned long count){
	int i;
	for(i=0;i<count;i++){
	SysTick_wait(16000);
	}

}



void SystemInit(void)
{
    // This function is called by the startup code before main()

    // Configure the system clock to run at 16 MHz
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;         // Use RCC2 for advanced features
    SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;         // Set the crystal frequency
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;         // Use the PLL
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;           // Divide the input frequency by 400
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000)   // Clear system clock divider
                    + (4<<22);                     // configure for 16 MHz clock

    // Wait for the PLL to lock to the desired frequency
    while((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0){};
    
    // Enable the use of the PLL
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}
