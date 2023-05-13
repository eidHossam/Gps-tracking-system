#include "LCD.h"

void LCD_init(void)
{
    SYSCTL->RCGCGPIO |= 0x18; // enable clock for PORTD and PORTE
    SysTick_wait_1ms(10);              // delay 10 ms for enable the clock of PORTB
    LCD->DIR |= 0x0F;         // let PORTD as output pins
    LCD->DEN |= 0x0F;         // enable PORTD digital IO pins
    CONTROL_LCD->DIR |= 0x0E; // let PORTE as output pins
    CONTROL_LCD->DEN |= 0x0E; // enable PORTE digital IO pins

    LCD_Cmd(Function_set_4bit); // 2 lines and 5x7 character (4-bit data, D4 to D7)
    LCD_Cmd(moveCursorRight);   // Automatic Increment cursor (shift cursor to right)
    LCD_Cmd(clear_display);     // Clear display screen
    LCD_Cmd(cursorOff);       // Display on, cursor blinking
}

void LCD_WriteNibble(unsigned char data, unsigned char control)
{
    LCD->DATA = data;
    CONTROL_LCD->DATA = (GPIOE->DATA & ~(RS)) | control | EN;		//Chooisng either command or a text and EN on
    CONTROL_LCD->DATA &= ~(RW);			//RW = 0 to choose write mode
    SysTick_wait_1us(0); // delay for pulsing EN
    CONTROL_LCD->DATA &= ~(EN);			//EN off for the data to be sent
}

void LCD_writeString(char *str)
{
    volatile int i = 0; // volatile is important

    while (*(str + i) != '\0') // until the end of the string
    {
        LCD_writeChar(*(str + i)); // Write each character of string
        i++;                       // increment for next character
    }
}

void LCD_Cmd(unsigned char command)
{
    LCD_WriteNibble(command >> 4, 0);   // upper nibble first
    LCD_WriteNibble(command & 0x0F, 0); // then lower nibble

    if (command < 4)
        SysTick_wait_1ms(2); // commands 1 and 2 need up to 1.64ms
    else
        SysTick_wait_1us(40); // all others 40 us
}

void LCD_writeChar(unsigned char data)
{
    LCD_WriteNibble(data >> 4, RS);   // upper nibble first
    LCD_WriteNibble(data & 0x0F, RS); // then lower nibble
    SysTick_wait_1us(40);                      // delay for LCD (MCU is faster than LCD)
}

void LCD_cursor_pos(unsigned char col, unsigned char row)
{

    unsigned char adress;
    if (row == 0)
        adress = 0x80;
    else
        adress = 0xC0;

    if (col < 16)
        adress += col;

    LCD_Cmd(adress);
}

void LCD_Clearscreen(void){
	
	LCD_Cmd(0x01);
	SysTick_wait_1us(2);
}

void LCD_showDistance(char* text, char* data)
{
	LCD_Clearscreen();
	LCD_cursor_pos(0,0);
	LCD_writeString(text);
	LCD_cursor_pos(2,1);
	LCD_writeString(data);
	LCD_cursor_pos(6,1);
	LCD_writeChar('m');
}	
