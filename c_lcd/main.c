#include<drivers/lcd.h>
#include"board_cfg.h"

/*RAMCLEAR in trampoline writes to P1, corrupting LCD state. Override that using this blank function*/
void _mcs51_genRAMCLEAR(void)
{

}

void main(void)
{
  LCD_init();
  LCD_display("Hello", 0x00);
  while(1);
}
