#include <board_cfg.h>
#include "interrupt.h"


void interrupt_enable(unsigned char interrupt_vector)
{
  IE |= (0x80 | (1<<interrupt_vector));
}

void interrupt_disable(unsigned char interrupt_vector)
{
  IE &= ~(1<<interrupt_vector);
}
