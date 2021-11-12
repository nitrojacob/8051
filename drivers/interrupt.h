#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

/*Refer to corresponding device header for the interrupt_vector #defines. Eg. TF0_VECTOR*/
void interrupt_enable(unsigned char interrupt_vector);
void interrupt_disable(unsigned char interrupt_vector);

#endif /*__INTERRUPT_H__*/
