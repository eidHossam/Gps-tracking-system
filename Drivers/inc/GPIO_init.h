#ifndef GPIO_INIT_H
#define GPIO_INIT_H

#include "tm4c123gh6pm.h"

#define redLED 		0x02
#define blueLED 	0x04
#define greenLED 	0x08
	
void PortF_init();
void PortB_init();
void PortD_init();
void PortE_init();
void RGB_output(unsigned char color);
unsigned char SW1_input(void);
unsigned char SW2_input(void);

#endif
