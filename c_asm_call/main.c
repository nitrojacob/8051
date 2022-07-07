/*
First assemble add_16.asm where the add_16 function is implemented
sdas8051 -ol add_16.asm 

Then compile main.c and link it's object code with the object code from previous assembly step
sdcc main.c add_16.rel

For functions marked as __reentrant, first argument is passed in registers (DPL, DPH, B, A), second argument at top of stack (below the program counter when seen by the callee), third argument below that etc..
 http://sdcc.sourceforge.net/doc/sdccman.pdf (Section 4.1.5 Interfacing with Assembler Code)
Return values have to be stored in the same manner. If there is less than or equal to 4 bytes store in (DPL, DPH, B, A)
*/


extern unsigned int add_16(unsigned int, unsigned int) __reentrant;

/*RAMCLEAR in trampoline writes to P1, corrupting LCD state. Override that using this blank function*/
void _mcs51_genRAMCLEAR(void)
{

}


void main(void)
{
  unsigned  int res;
  unsigned char LSB, MSB;
  res = add_16(511,512);
  LSB = (unsigned char)res;
  MSB = (unsigned char)(res >> 8);
  while(1);
}
