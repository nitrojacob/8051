#include <8051.h>

void _mcs51_genRAMCLEAR(void)
{

}

void main(void)
{
  unsigned char i, j, delay = 10;
  while(1)
  {
    for(i=0; i<8; i++)
    {
      P1=~(0x01 << i);
      for(j=0; j<delay; j++);
    }
  }
}
