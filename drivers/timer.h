#ifndef __TIMER_H__
#define __TiMER_H__

typedef enum{
  TIMER_0,
  TIMER_1,
  TIMER_2,
  TIMER_NOF
}eTIMER;

typedef enum{
  TIMER_MODE_13BIT = 0x00,
  TIMER_MODE_16BIT,
  TIMER_MODE_AUTORELOAD,
  TIMER_MODE_NOF,
  TIMER_MODE_COUNTER = 0x40, /*OR field*/
  TIMER_MODE_EXT_START = 0x80 /*OR field*/
}eTIMER_MODE;

typedef enum{
  TIMER_INTR_T0_OVF  = 0,
  TIMER_INTR_T0_COMP = 1,
  TIMER_INTR_T1_OVF  = 2,
  TIMER_INTR_T1_COMP_B   = 3,
  TIMER_INTR_T1_COMP_A   = 4,
  TIMER_INTR_T1_INPUT_CAPT   = 5,
  TIMER_INTR_T2_OVF  = 6,
  TIMER_INTR_T2_COMP = 7,
}eTIMER_INTR;

typedef enum{
  TIMER_PIN_T0_OC,
  TIMER_PIN_T1_OCA,
  TIMER_PIN_T1_OCB,
  TIMER_PIN_T2_OC
}eTIMER_PIN;

/**
 * Initialises timer with the parameters specified
 */
void timer_init(eTIMER timer, unsigned long frequency, unsigned long clkIO, eTIMER_MODE mode, unsigned int maxVal);

/**@brief Stops/Freezes the count of the timer specified, by gating the timer's input clock from pre-scaler.
 */
void timer_stop(eTIMER timer);

/**@brief Returns the current count of the timer.
 * Useful when the timer is used as a counter to measure the duration between two interrupts/events
 */
unsigned long timer_getCurrentCount(eTIMER timer);

/**@brief Configures the interrupt behaviour on the fly
 * @arg interrupt - the interrupt to be enabled/disabled
 *      mode      - 1 to enable; 0 to disable
 */
void timer_configureInterrupt(eTIMER_INTR interrupt, unsigned char mode);

#endif /*__TIMER_H__*/
