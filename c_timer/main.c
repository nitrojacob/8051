#include <drivers/timer.h>
#include <board_cfg.h>

/*RAMCLEAR in trampoline writes to SP, corrupting it. Override that using this blank function*/
void _mcs51_genRAMCLEAR(void)
{

}

void main(void)
{
  timer_init(TIMER_0, 4000, 12000000, TIMER_MODE_AUTORELOAD, 0x00);
  while(1);
}
