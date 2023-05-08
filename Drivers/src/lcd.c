
#include "lcd.h"

void LCD_setup(void)
{
		SYSCTL->RCGCGPIO |=(1 << 1); /* Enable Clock to GPIOC */
		LCD->DIR |=0xFF; /* Set GPIOC all pins a digital output pins */
		LCD->DEN |=0xFF; /* Declare GPIOC pins as digital pins */

	
    SysTick_wait_1ms(20);
    LCD_cmd(0x28);
    SysTick_wait_1ms(2);
    LCD_cmd(0x0C);
    SysTick_wait_1ms(2);
    LCD_cmd(0x06);
    SysTick_wait_1ms(2);
    LCD_cmd(0x01);
    SysTick_wait_1ms(2);
    LCD_cmd(0x80);
    SysTick_wait_1ms(2);
}

void LCD_cmd(unsigned char cmd)
{

    LCD_Write_Nibble(cmd & 0xF0, 0);
    LCD_Write_Nibble(cmd << 4, 0);
    if (cmd < 4)
        SysTick_wait_1ms(2);
    else
        SysTick_wait_1us(40);
}

void LCD_write_char(unsigned char data)
{

    LCD_Write_Nibble(data & 0xF0, RS);
    LCD_Write_Nibble(data << 4, RS);
    SysTick_wait_1ms(2);
}

void LCD_writeString(char *data)
{
    while (*(data) != 0)
    {
        LCD_write_char(*data);
        data++;
    }
}

void LCD_cursor_pos(unsigned char x, unsigned char y)
{

    unsigned char adress;
    if (y == 0)
        adress = 0x80;
    else
        adress = 0xC0;

    if (x < 16)
        adress += x;

    LCD_cmd(adress);
}

void LCD_Clearscreen(void)
{

    LCD_cmd(0x01);
    SysTick_wait_1ms(2);
}

void LCD_Write_Nibble(unsigned char data, unsigned char control)
{
    data &= 0xF0;    /* Extract upper nibble for data */
    control &= 0x0F; /* Extract lower nibble for control */
    LCD->DATA &= ~(1 << RS);
    LCD->DATA &= ~(1 << RW);
    LCD->DATA |= (1 << EN);
    SysTick_wait_1ms(2);
    LCD->DATA &= ~(1 << EN);
    SysTick_wait_1us(0);
    LCD->DATA = data;
    LCD->DATA = 0;
}