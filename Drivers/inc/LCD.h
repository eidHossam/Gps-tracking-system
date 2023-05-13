#ifndef LCD_H
#define LCD_H

#include "TM4C123.h"
#include "SysTick.h"

#define LCD GPIOD         // LCD port with Tiva C
#define CONTROL_LCD GPIOE // RS , RW and EN
#define RS 0x02           // RS -> PE1 (0x02)
#define RW 0x04           // RW -> PE2 (0x04)
#define EN 0x08           // EN -> PE3 (0x08)

/*define useful symbolic names for LCD commands */
#define clear_display 0x01
#define returnHome 0x02
#define moveCursorRight 0x06
#define moveCursorLeft 0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft 0x18
#define cursorBlink 0x0F
#define cursorOff 0x0C
#define cursorOn 0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode 0x06
#define Function_8_bit 0x32
#define Set5x7FontSize 0x20
#define FirstRow 0x80

// Functions Declaration
void LCD_init(void);
void LCD_WriteNibble(unsigned char, unsigned char);
void LCD_writeString(char *);
void LCD_Cmd(unsigned char);
void LCD_cursor_pos(unsigned char col, unsigned char row);
void LCD_writeChar(unsigned char);
void LCD_Clearscreen(void);
void LCD_showDistance(char *text, char *data);

#endif
