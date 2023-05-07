#include "stdint.h"
#include "tm4c123gh6pm_real.h"
#include "GPIO_init.h"



void PortF_init(){
		SYSCTL_RCGCGPIO_R |=0x20;
		while((SYSCTL_PRGPIO_R & 0x20) ==0){};
			GPIO_PORTF_LOCK_R=GPIO_LOCK_KEY;
			GPIO_PORTF_CR_R=0x1F;
			GPIO_PORTF_AMSEL_R=0x00;
			GPIO_PORTF_AFSEL_R  =0x00;
			GPIO_PORTF_DEN_R=0x1F;
			GPIO_PORTF_PCTL_R =0x00;
			GPIO_PORTF_DIR_R =0x0E;
			GPIO_PORTF_PUR_R= 0x11;		
			
}
void PortB_init(){
		SYSCTL_RCGCGPIO_R |=0x02;
		while((SYSCTL_PRGPIO_R & 0x02) ==0){};
			
			GPIO_PORTB_CR_R=0xFF;
			GPIO_PORTB_AMSEL_R=0x00;
			GPIO_PORTB_AFSEL_R  =0x00;
			GPIO_PORTB_DEN_R=0xFF;
			GPIO_PORTB_PCTL_R =0x00;
			GPIO_PORTB_DIR_R =0x00;
			//GPIO_PORTB_PUR_R= 0x00;		
			
}
void PortD_init(){
		SYSCTL_RCGCGPIO_R |=0x08;
		while((SYSCTL_PRGPIO_R & 0x08) ==0){};
			GPIO_PORTD_LOCK_R=GPIO_LOCK_KEY;
			GPIO_PORTD_CR_R=0xFF;
			GPIO_PORTD_AMSEL_R=0x00;
			GPIO_PORTD_AFSEL_R  =0x00;
			GPIO_PORTD_DEN_R=0xFF;
			GPIO_PORTD_PCTL_R =0x00;
			GPIO_PORTD_DIR_R =0x00;
			//GPIO_PORTD_PUR_R= 0x00;		
			
}
void PortE_init(){
		SYSCTL_RCGCGPIO_R |=0x10;
		while((SYSCTL_PRGPIO_R & 0x10) ==0){};
			
			GPIO_PORTE_CR_R=0x2F;
			GPIO_PORTE_AMSEL_R=0x00;
			GPIO_PORTE_AFSEL_R  =0x00;
			GPIO_PORTE_DEN_R=0x2F;
			GPIO_PORTE_PCTL_R =0x00;
			GPIO_PORTE_DIR_R =0x00;
			//GPIO_PORTE_PUR_R= 0x11;		
			
}
void RGB_output(unsigned char color){
GPIO_PORTF_DATA_R &=~ 0x0E;
GPIO_PORTF_DATA_R |=color;
}
unsigned char SW1_input(void){
return GPIO_PORTF_DATA_R&0x10;//returns 00 if pressed ,10 if not
}
unsigned char SW2_input(void){
return GPIO_PORTF_DATA_R&0x01;//returns 00 if pressed ,01 if not
}

