#ifndef SYSTICK_H
#define SYSTICK_H

#include "tm4c123gh6pm.h"

void initClock(); //Make the clock work at 16MHz not 80MHz

void SysTick_init(void); //intialization of SysTick Counter Timer
	
void SysTick_wait(unsigned long delay); //Wait certain delay

void SysTick_wait_1ms(unsigned long count); //Loop certain ms

void SysTick_wait_1us(unsigned long count); /* micro second delay function */ 

#endif
