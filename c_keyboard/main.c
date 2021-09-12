#include<8051.h>

typedef struct{
  unsigned char scan;
  unsigned char ascii;
  unsigned char disp;
}s_keymap;

s_keymap keymap[] = {
  /*scan ascii disp*/
  { 0xb7, '1', 0x06 }, /*0 1 1*/
  { 0xd7, '2', 0x5B }, /*1 0 1*/
  { 0xe7, '3', 0x4F }, /*1 1 0*/
  { 0xbb, '4', 0x66 },
  { 0xdb, '5', 0x6D },
  { 0xeb, '6', 0x7D },
  { 0xbd, '7', 0x07 },
  { 0xdd, '8', 0x7F },
  { 0xed, '9', 0x6F },
  { 0xbe, '*', 0x77 },
  { 0xde, '0', 0x3F },
  { 0xee, '#', 0x7C },
};

void main(void)
{
  unsigned char i;
  while(1)
  {
    P0 = 0xf0;
    while(P0 == 0xf0);
    for(i=0; i<sizeof(keymap)/sizeof(s_keymap); i++)
    {
      P0 = keymap[i].scan | 0xf0;
      if(P0 == keymap[i].scan)
        P1 = ~(keymap[i].disp);
    }
  }
}

