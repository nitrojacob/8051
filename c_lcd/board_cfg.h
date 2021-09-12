#ifndef __BOARD_CFG_H__
#define __BOARD_CFG_H__

#include <8051.h>
#define LCD_CTRL_PORT P1
#define LCD_CTRL_DIR  P1

#define LCD_DATA_PORT P1
#define LCD_DATA_PIN  P1
#define LCD_DATA_DIR  P1
#define UC_TO_LCD           LCD_DATA_PIN
#define LCD_TO_UC           0xff

#define LCD_REG_SEL         0x08
#define LCD_RW              0x01
#define LCD_ENABLE          0x04

#endif /*__BOARD_CFG_H__*/
