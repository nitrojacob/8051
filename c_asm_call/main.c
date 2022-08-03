/*
First assemble add_16.asm where the add_16 function is implemented
sdas8051 -ol add_16.asm 

Then compile main.c and link it's object code with the object code from previous assembly step
sdcc main.c add_16.rel

For functions marked as __reentrant, first argument is passed in registers (DPL, DPH, B, A), second argument at top of stack (below the program counter when seen by the callee), third argument below that etc..
 http://sdcc.sourceforge.net/doc/sdccman.pdf (Section 4.1.5 Interfacing with Assembler Code)
Return values have to be stored in the same manner. If there is less than or equal to 4 bytes store in (DPL, DPH, B, A)
*/
#include<8051.h>

typedef unsigned long U32;
typedef unsigned int U16;
typedef unsigned char U8;
//extern unsigned int add_16(unsigned int, unsigned int) __reentrant;
//extern unsigned int sub_16(unsigned int, unsigned int) __reentrant;
extern unsigned long mul_16(unsigned int, unsigned int) __reentrant;

/*RAMCLEAR in trampoline writes to P1, corrupting LCD state. Override that using this blank function*/
void _mcs51_genRAMCLEAR(void)
{

}

volatile unsigned  long i, j;

void main(void)
{ 
  for(i=0; i<=0xffff; i++)
    for(j=0; j<=0xffff; j++)
      if((U32)(i*j) != mul_16((U16)i, (U16)j))
        while(1);
  while(1);
}
