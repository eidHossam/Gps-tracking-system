#include "States.h"
#include <string.h>

geoPoint_t currPosition, destination;
char command[] = "$GPRMC,141848.00,A,4075.63306,N,-7399.86316,E,0.553,,100418,,,A*73";
float distance;

int main()
{
		gps_init(16000000, 9600);
		UART0_INIT(9600);
		PortF_init();
		LCD_setup(); //Must be fixed
	
		destination = getDestination();
		
		//Waiting for the gps to locate the satellites the LED will be blue in this state
		locatingSatellite(command, &currPosition);
		
		//Wait until Sw1 is pressed and the LED will be purple to indicate we are in the ready state
		readyState();
		
		while(1)
		{
				//gpsGetCommand(command, BUFFER_SIZE);
		
				if(get_current_position(command, &currPosition))
						distance = calculateDistance(currPosition, destination);
				else
						distance = 69.69;
		
				memset(command,0 , 66);
		}	
}

