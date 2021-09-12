#include<8051.h>

void _mcs51_genRAMCLEAR(void)
{

}

void main(void)
{
  int i, delay = 10;
  P1 = 0xfe;	/*turn on*/
  for(i=0; i<delay; i++)
  {
  }
  P1 = 0xff; /*turn off*/
  while(1);
}
