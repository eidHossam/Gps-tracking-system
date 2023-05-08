#include "States.h"

void locatingSatellite(char* command, geoPoint_t* currPosition)
{
		RGB_output(blueLED);
	
		while(!get_current_position(command, currPosition))
		{
				LCD_Clearscreen();
				LCD_cursor_pos(0,0);
				LCD_writeString("Searching");
		}
		
		SysTick_wait_1ms(5000);
}

void readyState()
{
		RGB_output((blueLED | redLED));
		
		LCD_Clearscreen();
		LCD_cursor_pos(0,5);
		LCD_writeString("Ready");
	
		LCD_cursor_pos(1,2);
		LCD_writeString("Press Sw1 to start");
		
		while(SW1_input() != 0);
}