#include "States.h"

void locatingSatellite(char *command, geoPoint_t *currPosition)
{
    RGB_output(blueLED);

    gpsGetCommand(command, BUFFER_SIZE);
    while (!get_current_position(command, currPosition))
    {
        LCD_Clearscreen();
        LCD_cursor_pos(0, 0);
        LCD_writeString("Searching");
        gpsGetCommand(command, BUFFER_SIZE);
    }

    //SysTick_wait_1ms(5000);
}

void readyState()
{
    RGB_output((blueLED | redLED));

    LCD_Clearscreen();
    LCD_cursor_pos(0, 5);
    LCD_writeString("Ready");

    LCD_cursor_pos(1, 2);
    LCD_writeString("Press Sw1 to start");

    while (SW1_input() != 0)
        ;
}


////White color when we encounter an error 
void errorState()
{
	
	RGB_output((blueLED | greenLED | redLED));

    LCD_Clearscreen();
    LCD_cursor_pos(0, 0);
    LCD_writeString("Error: sat not found");
	
	SysTick_wait_1ms(5000);
}

void reachingState()
{	
	//Yellow color
	RGB_output(redLED | greenLED);
}

//This means the target is farther than 5m
void destiationIsFar()
{
	RGB_output(redLED); 
}

void destinationReached()
{
	RGB_output(greenLED);
	
	LCD_Clearscreen();
    LCD_cursor_pos(0, 0);
    LCD_writeString("Destination reached!.");
	
	SysTick_wait_1ms(10000); 
}

bool getStartingPosition(char* command, geoPoint_t* currPosition)
{
	int errorCounter = 0;
	gpsGetCommand(command, BUFFER_SIZE);
	//Loop until we get a valid reading
	while(errorCounter < MAX_ALLOWED_ERRORS)
	{
		if(get_current_position(command, currPosition))
			return true;
		
		gpsGetCommand(command, BUFFER_SIZE);
		errorCounter++;
	}
	
	errorState();
	return false;
}