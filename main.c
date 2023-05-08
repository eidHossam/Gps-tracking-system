#include "States.h"
#include <string.h>

geoPoint_t currPosition, destination, startPosition;
char command[128]; //= "$GPRMC,141848.00,A,4075.63306,N,-7399.86316,E,0.553,,100418,,,A*73";
float totalDistance, distanceTraveled, distanceLeft;

int main()
{
    gps_init(16000000, 9600);
    UART0_INIT(9600);
    PortF_init();
    LCD_setup(); // Must be fixed

    destination = getDestination();

    // Waiting for the gps to locate the satellites the LED will be blue in this state
    locatingSatellite(command, &startPosition);

    // Getting the total distance between the start and end points
    totalDistance = calculateDistance(currPosition, destination);

    // Wait until Sw1 is pressed and the LED will be purple to indicate we are in the ready state
    readyState();
	
	//Getting the starting position and ending the program if we can't get the location
	if(!getStartingPosition(command, &startPosition))
		return 0;
	
    while (1)
    {
        gpsGetCommand(command, BUFFER_SIZE);

        if (get_current_position(command, &currPosition))
        {
			
            distanceTraveled += calculateDistance(startPosition, currPosition);
			
			distanceLeft = calculateDistance(currPosition, destination);
			
			//The LED will be turned on Yellow when there is less than 5 meters
			//to reach the destination
			if(distanceLeft < 5)
				reachingState();
			else if(distanceLeft < 1)
			{
				destinationReached();
				return 0;
			}
			else
				destiationIsFar();
			
			
			startPosition = currPosition;
        }

        memset(command, 0, 66);
    }
}
