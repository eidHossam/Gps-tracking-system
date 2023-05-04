void initClock(); //Make the clock work at 16MHz not 80MHz

void SysTick_init(void); //intialization of SysTick Counter Timer
	
void SysTick_wait(unsigned long delay); //Wait certain delay

void SysTick_wait_loop(unsigned long count); //Loob certain ms