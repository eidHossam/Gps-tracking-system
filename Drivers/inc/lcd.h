#include "TM4C123.h"
#define rs PB5
#define rw PB6
#define en PB7
#define LCD GBIOB
  
void LCD_setup(void);
void LCD_data(unsigned char data);
void LCD_cmd(unsigned char cmd);
void LCD_write(char[16] data);
void LCD_cursor_pos(unsigned char x,unsigned char y);
void LCD_Clearscreen(void);
void LCD_Write_Nibble(unsigned char data, unsigned char control);
