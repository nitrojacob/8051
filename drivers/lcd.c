#include <board_cfg.h>
#include "lcd.h"

//LCD Module
#ifndef LCD_CTRL_PORT
  #define LCD_CTRL_PORT       PORTB
  #define LCD_CTRL_DIR        DDRB
#endif /* LCD_CTRL_PORT */

#ifndef LCD_DATA_PORT
  #define LCD_DATA_PORT       PORTC
  #define LCD_DATA_PIN        PINC
  #define LCD_DATA_DIR        DDRC
  #define UC_TO_LCD           0xff
  #define LCD_TO_UC           0x00
#endif /* LCD_DATA_PORT */

//LCD Commands
#define LCD_CMD_CLEAR_DISPLAY   0x01
#define LCD_CMD_RETURN_HOME     0x02
#define LCD_CMD_ENTRY_MODE_SET  0x04
#define LCD_CMD_DISPLAY_CTRL    0x08
#define LCD_CMD_CURSOR_SHIFT    0x10
#define LCD_CMD_FUNCTION_SET    0x20
#define LCD_CMD_SET_CGRAM_ADDR  0x40
#define LCD_CMD_SET_DDRAM_ADDR  0x80

#ifndef LCD_REG_SEL
  #define LCD_REG_SEL         0x01
  #define LCD_RW              0x02
  #define LCD_ENABLE          0x04
#endif /* LCD_REG_SEL */

#ifdef LCD_BUSWIDTH_4BIT
  #define LCD_DATA_PORT_MASK 0xf0
#else
  #define LCD_DATA_PORT_MASK 0xff
#endif /* LCD_BUSWIDTH_4BIT */

typedef struct{
  unsigned char busWidth;  /* 4 or 8 bits */
}s_lcd;

static s_lcd lcd;

static void udelay(void);
static void BusyWait();
static inline void setCtrlBit(unsigned char x);
static inline void clrCtrlBit(unsigned char x);
static void LCDsendCommand(unsigned char command);

void LCD_init(void)
{
  LCD_CTRL_DIR=UC_TO_LCD;
  lcd.busWidth = 8;
#ifdef LCD_BUSWIDTH_4BIT
  LCDsendCommand(0x28);   //Function set
  lcd.busWidth = 4;
  LCDsendCommand(0x28);
#else
  LCDsendCommand(0x38);   //Function set
#endif /* LCD_BUSWIDTH_4BIT */
  LCDsendCommand(0x0c);   //Display ON/OFF :no cursor
  LCDsendCommand(LCD_CMD_CLEAR_DISPLAY);  //Clear Display
  LCDsendCommand(0x06);   //Entry Mode
}

void LCD_display(unsigned char msg[],unsigned char position)
{
  unsigned char i;
  LCDsendCommand(0x80|position);  /*Set DDRAM Address*/
  udelay();
  for(i=0;i<16 && msg[i] != '\0';i++){
    setCtrlBit(LCD_REG_SEL);   //DATA;
    setCtrlBit(LCD_ENABLE);
    LCD_DATA_PORT=(msg[i] & LCD_DATA_PORT_MASK) | (LCD_DATA_PORT & ~LCD_DATA_PORT_MASK);
    udelay();
    clrCtrlBit(LCD_ENABLE);
    if(lcd.busWidth == 4)
    {
      setCtrlBit(LCD_ENABLE);
      LCD_DATA_PORT = ((msg[i] << 4) & LCD_DATA_PORT_MASK) | (LCD_DATA_PORT & ~LCD_DATA_PORT_MASK);
      udelay();
      clrCtrlBit(LCD_ENABLE);
    }
  }
}
void LCD_clear(void)
{
  LCDsendCommand(LCD_CMD_CLEAR_DISPLAY);
}

static void udelay(void)    //AVR compliant
{
  unsigned char i;
  for(i=0;i<100;i++);
}

#ifdef LCD_UNIDIRECTIONAL
static void BusyWait()
{
  udelay();
}
#else
static void BusyWait()
{
  LCD_DATA_DIR=LCD_TO_UC;
  setCtrlBit(LCD_RW);
  while(LCD_DATA_PIN & 0x80);
  clrCtrlBit(LCD_RW);
  LCD_DATA_DIR=UC_TO_LCD;
}
#endif /* LCD_UNIDIRECTIONAL */

static inline void setCtrlBit(unsigned char x)
{
  LCD_CTRL_PORT|=x;
}

static inline void clrCtrlBit(unsigned char x)
{
  LCD_CTRL_PORT&=(~x);
}

static void LCDsendCommand(unsigned char command)  //All handshaking will be taken care of.
{
  clrCtrlBit(LCD_REG_SEL);    //COMMAND;
  setCtrlBit(LCD_ENABLE);     //Preparing for a 1->0 transition
  BusyWait();                 //Wait for any already issued commands to finish
  LCD_DATA_PORT=(command & LCD_DATA_PORT_MASK) | (LCD_DATA_PORT & ~LCD_DATA_PORT_MASK);      //Setting command
  clrCtrlBit(LCD_ENABLE);     //1->0 transition on E line.
  if(lcd.busWidth == 4)
  {
    setCtrlBit(LCD_ENABLE);
    udelay();
    LCD_DATA_PORT=((command << 4) & LCD_DATA_PORT_MASK) | (LCD_DATA_PORT & ~ LCD_DATA_PORT_MASK);
    clrCtrlBit(LCD_ENABLE);
  }
}

