#ifndef LCD_H
#define LCD_H

#include "TM4C123.h"
#include "SysTick.h"

#define RS 0x02
#define RW 0x04
#define EN 0x08
#define LCD GPIOB

void LCD_setup(void);
void LCD_write_char(unsigned char data);
void LCD_cmd(unsigned char cmd);
void LCD_writeString(char *data);
void LCD_cursor_pos(unsigned char x, unsigned char y);
void LCD_Clearscreen(void);
void LCD_Write_Nibble(unsigned char data, unsigned char control);

#endif
