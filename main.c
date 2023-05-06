#include "GPS.h"
#include <string.h>

		
		
int main()
{
		char command[] = "$GPRMC,141848.00,A,4075.63306,N,-7399.86316,E,0.553,,100418,,,A*73";
		float distance = 0.0;
		

		geoPoint_t currPosition, destination;
		destination.latitude_d = DEG_TO_RAD(30.17);
		destination.longitude_d = DEG_TO_RAD(31.47);
		 
		
	gps_init(16000000, 9600);
	
	while(1)
	{
		//gpsGetCommand(command, BUFFER_SIZE);
		
		if(get_current_position(command, &currPosition))
					distance = calculateDistance(currPosition, destination);
		else
					distance = 69.69;
		
		memset(command,0 , 67);
	}	
}
