
#include "lcd.h"


void LCD_setup(void)
{
	_delay_ms(20);
	LCD_cmd(0x28);
	_delay_ms(2);
	LCD_cmd(0x0C);
	_delay_ms(2);
	LCD_cmd(0x06);
	_delay_ms(2);
	LCD_cmd(0x01);
	_delay_ms(2);
	LCD_cmd(0x80);
	_delay_ms(2);
}

void LCD_cmd(unsigned char cmd){
	
	LCD_Write_Nibble(cmd & 0xF0 , 0);
	LCD_Write_Nibble(cmd << 4 , 0);
	if (cmd < 4)
		delay_ms(2);
	else
		delay_us(40);
	
}

void LCD_data(unsigned char data ){
        
    LCD_Write_Nibble(data & 0xF0 , rs);
	LCD_Write_Nibble(data << 4 , rs);
	delay_ms(2);
}

void LCD_write(char[16] data){
	while (*(data) != 0)
	{
		LCD_data(*data);
		data++;
	}
	
}

void LCD_cursor_pos(unsigned char x,unsigned char y){
	
	unsigned char adress;
	if(y==0)
	 adress=0x80;
	else 
	 adress=0xC0;
	 
	 if(x<16)
	 adress+=x;
	 
	 LCD_cmd(adress);
}

void LCD_Clearscreen(void){
	
	LCD_cmd(0x01);
	_delay_ms(2);
}

void LCD_Write_Nibble(unsigned char data, unsigned char control)
{
	data &= 0xF0;       /* Extract upper nibble for data */
	control &= 0x0F;    /* Extract lower nibble for control */
		PORTB &= ~(1<<rs);
		PORTB &= ~(1<<rw);
		PORTB |= (1<<en);
		_delay_ms(2);
		PORTB &= ~(1<<en);
	delay_us(0);
	LCD->DATA = data; 
	LCD->DATA = 0; 
}