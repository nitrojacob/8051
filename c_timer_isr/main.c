#include <drivers/timer.h>
#include <drivers/interrupt.h>
#include <board_cfg.h>

/*RAMCLEAR in trampoline writes to SP, corrupting it. Override that using this blank function*/
void _mcs51_genRAMCLEAR(void)
{

}

void main(void)
{
  interrupt_enable(TF0_VECTOR);
  timer_init(TIMER_0, 8000, 12000000, TIMER_MODE_AUTORELOAD, 0x00);
  while(1);
}

void timer0_isr(void) __interrupt (TF0_VECTOR)
{
  P1 ^= 0xff;
}
