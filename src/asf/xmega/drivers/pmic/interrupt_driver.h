/*
 * interrupt_driver.h
 *
 * Created: 3/2/2011 7:06:28 PM
 *  Author: matt
 */ 


#ifndef INTERRUPT_DRIVER_H_
#define INTERRUPT_DRIVER_H_
#include "compiler.h"


#define CONFIG_INTERRUPT_TCD0_CCA_vect

#define ASSIGN_INTERRUPT(vect) irq_cb_t irq_##vect##_cb = NULL; \
    INLINE void set_##vect##_cb(irq_cb_t irq) {irq_##vect##_cb = irq;} \
    INLINE void release_##vect##_cb(void) {irq_##vect##_cb = NULL;} \
    INLINE Bool isSet_##vect##_cb(void) {return((irq_##vect##_cb != NULL) ? YES : NO);} \
    INLINE irq_cb_t get_##vect##_cb(void) {return irq_##vect##_cb;}
		

#endif /* INTERRUPT_DRIVER_H_ */