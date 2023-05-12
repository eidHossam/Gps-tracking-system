#include "States.h"
#include <string.h>

geoPoint_t currPosition, destination, startPosition;
char command[128],distance[6]; //= "$GPRMC,141848.00,A,4075.63306,N,-7399.86316,E,0.553,,100418,,,A*73";
float totalDistance, distanceTraveled, distanceLeft;

int main()
{
	gps_init(16000000, 9600);
	UART0_INIT(9600);
	PortF_init();
	LCD_init();

	LCD_writeString("Enter the");
	LCD_cursor_pos(0,1);
	LCD_writeString("Destination:");
	destination = getDestination();
	
	// Waiting for the gps to locate the satellites the LED will be blue in this state
	locatingSatellite(command, &startPosition);

	// Wait until Sw1 is pressed and the LED will be purple to indicate we are in the ready state
	readyState();

	// Getting the starting position and ending the program if we can't get the location
	if (!getStartingPosition(command, &startPosition))
		return 0;

	// Getting the total distance between the start and end points
	totalDistance = calculateDistance(startPosition, destination);

	while (1)
	{

		SysTick_wait_1ms(500);
		gpsGetCommand(command, BUFFER_SIZE);

		if (get_current_position(command, &currPosition))
		{

			distanceTraveled += calculateDistance(startPosition, currPosition);

			distanceLeft = calculateDistance(currPosition, destination);

			float deltaLat = destination.latitude_d - currPosition.latitude_d;
			float deltaLon = destination.longitude_d - currPosition.longitude_d;
			sprintf(distance, "%.2g", distanceTraveled);
			
			// If the destination is reached turn LED green and end the program
			if (distanceLeft < 1.0 || (fabs(deltaLat) < 0.00002 && fabs(deltaLon) < 0.00002))
			{
				destinationReached();
				LCD_showDistance("Total Distance: ", distance);

				return 0;
			}
			else if (distanceLeft < 5.0 || (fabs(deltaLat) < 0.00007 && fabs(deltaLon) < 0.00007))
				reachingState(); // If destination is less than 5m away turn the yellow LED on
			else
				destiationIsFar(); // If the destination is more than 5m away turn the red LED on

			startPosition = currPosition;
		}
		
		LCD_showDistance("Dist Traveled: ", distance);
		
		memset(command, 0, 128);
		memset(distance, 0, 6);
	}
}
