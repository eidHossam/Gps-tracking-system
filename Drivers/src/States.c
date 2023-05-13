#include "States.h"

void locatingSatellite(char *command, geoPoint_t *currPosition)
{
    RGB_output(blueLED);
	
	LCD_Clearscreen();
    LCD_cursor_pos(3, 0);
    LCD_writeString("Searching");
    LCD_cursor_pos(0, 1);
	LCD_writeString("For Satellites");
	
	gpsGetCommand(command, BUFFER_SIZE);
    while (!get_current_position(command, currPosition))
        gpsGetCommand(command, BUFFER_SIZE);
	
	LCD_Clearscreen();
}

void readyState()
{
    RGB_output((blueLED | redLED));

    LCD_Clearscreen();
    LCD_cursor_pos(3, 0);
    LCD_writeString("GPS Ready");

    LCD_cursor_pos(2, 1);
    LCD_writeString("Sw1 to start");

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
    LCD_writeString("Destination");
		LCD_cursor_pos(2,1);
		LCD_writeString("Reached!");
	
		SysTick_wait_1ms(5000); 
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