#include <board_cfg.h>
#include "timer.h"

void timer_init(eTIMER timer, unsigned long frequency, unsigned long clkIO, eTIMER_MODE mode, unsigned int maxVal)
{
  unsigned long divider;
  volatile unsigned char *pTH, *pTL;
  unsigned char modeReg = 0x00;/*GATE = 0; Doesn't depend on external signals for start*/

  switch(timer)
  {
    case TIMER_1:
      pTH = &TH1;
      pTL = &TL1;
      break;
    case TIMER_0:
    default:
      pTH = &TH0;
      pTL = &TL0;
      break;
  }

  switch(mode & ~(TIMER_MODE_COUNTER | TIMER_MODE_EXT_START))
  {
    case TIMER_MODE_13BIT: /*Fixed divide by 2^13*/
      *pTH = 0;
      *pTL = 0;
      modeReg |= 0x00;
      break;
    case TIMER_MODE_16BIT: /*Fixed divide by 2^16*/
      *pTL = 0;
      *pTH = 0;
      modeReg |= 0x01;
      break;
    case TIMER_MODE_AUTORELOAD: /*Programmable divide by 1 to 256*/
    default:
      divider = clkIO/(12 * frequency);
      *pTH = 0xff - (unsigned char)(divider & 0xff);
      *pTL = *pTH;
      modeReg |= 0x02;
      break;
  }
  if(mode & TIMER_MODE_COUNTER)
    modeReg |= 0x04;
  if(mode & TIMER_MODE_EXT_START)
    modeReg |= 0x08;
  switch(timer)
  {
    case TIMER_0:
      TMOD = (TMOD & 0xf0) | modeReg;
      TCON |= 0x10;
      break;
    case TIMER_1:
    default:
      TMOD = (TMOD & 0x0f) | (modeReg << 4);
      TCON |= 0x40;
      break;
  }
}


unsigned long timer_getCurrentCount(eTIMER timer)
{
  unsigned long result;
  unsigned char mode;
  volatile unsigned char *pTH, *pTL;
  switch(timer)
  {
    case TIMER_1:
      pTH = &TH1;
      pTL = &TL1;
      mode = (TMOD >> 4) & 0x07;
      break;
    case TIMER_0:
    default:
      pTH = &TH0;
      pTL = &TL0;
      mode = (TMOD) & 0x07;
      break;
  }
  switch(mode)
  {
    case 0x00:
    case 0x04:  /*13 bit*/
      result = *pTL & 0x1f;
      result = (result << 8) | *pTH;
      break;
    case 0x01:
    case 0x05:  /*16 bit*/
      result = *pTH;
      result = (result << 8) | *pTL;
      break;
    case 0x02:
    case 0x06:  /*Auto-reload*/
    default:
      result = *pTH;
      break;
  }
  return result;
}
