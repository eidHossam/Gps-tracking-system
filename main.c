#include "GPS.h"
#include <string.h>

int main()
{
	
		int length = 128;
		char *command;

	gps_init(16000000, 9600);
	
	while(1)
	{
		gpsGetCommand(command, length);
		SysTick_wait1s(1);
		memset(command,0 , 128);
	}	
}
