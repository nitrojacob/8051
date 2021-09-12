/**
 * HD 44780 LCD controller header file
 *
 * Target    :AVR (ATMega32) @ 1MHz
 *
 * Data bus of LCD to be connected to LCD_DATA_PORT
 * Control lines of LCD (E,RW and RS) to be connected to LCD_CTRL_PORT
 */
#ifndef __LCD_H__
#define __LCD_H__

/* Define the following globally, if the settings needs to be changed. If not defined globally the following settings are assumed.
//LCD Module
#define LCD_CTRL_DIR        DDRB
#define LCD_CTRL_PORT       PORTB
//0 - LCD_REG_SEL
//1 - LCD_RW
//2 - LCD_ENABLE
#define LCD_DATA_PORT       PORTC
#define LCD_DATA_PIN        PINC
#define LCD_DATA_DIR        DDRC
*/

/* Upper and lower line of the two line display */
#define LCD_UPPER_LINE		0x80
#define LCD_LOWER_LINE		0xc0

void LCD_display(unsigned char a[],unsigned char position);
void LCD_init(void);
void LCD_clear(void);

#endif //__LCD_H__
