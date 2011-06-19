/*
 * qsm.h
 *
 *  Created on: Sep 17, 2010
 *      Author: mpoppe
 */

#ifndef QSM_H_
#define QSM_H_

#include "compiler.h"
#include "parts.h"
#define qsmMAXSIZE		(20)
#define qsmTYPE			(2)
#define qsmFIRST		(0)
#ifdef XMEGA

#define START_TIMER1_COMPA()	TCD0.INTFLAGS = 0xff; 	\
									TCD0.INTCTRLA = TC_CCAINTLVL_LO_gc;


#define START_TIMER3_COMPA()	TCD1.INTFLAGS = 0xff; 	\
									TCD1.INTCTRLA = TC_CCAINTLVL_LO_gc;


#define STOP_TIMER3_COMPA()		TCD1.INTCTRLA = TC_CCAINTLVL_OFF_gc;
#define STOP_TIMER1_COMPA()		TCD0.INTCTRLA = TC_CCAINTLVL_OFF_gc;
#else
#define START_TIMER1_COMPA()	do{							\
									TIFR1  |= _BV(OCF1A); 	\
									TIMSK1 |= _BV(OCIE1A);	\
								}while(0)

#define START_TIMER3_COMPA()	do{							\
									TIFR3  |= _BV(OCF3A); 	\
									TIMSK3 |= _BV(OCIE3A);	\
								}while(0)

#define STOP_TIMER3_COMPA()		TIMSK3 &= ~_BV(OCIE3A)
#define STOP_TIMER1_COMPA()		TIMSK1 &= ~_BV(OCIE1A)
#endif

typedef enum QSM_TYPES{
	QSM_INSTANT,
	QSM_TIME,
}qsm_type_t;

typedef enum QSM_STATUS{
	QSM_SUCCESS,
	QSM_STACKFULL,
}qsm_status_t;


//	TODO: 	I think i need to add types of arguments or function pointers?????

typedef void (*func_point_t)(void *argu); //	TODO: I need to look at this more I am not really sure if this will work

typedef struct QSM_HANDLES{
	func_point_t 	fp;
	void			*arg;
	uint32_t		time;//number of microseconds need to be delayed.. after it is put in the stack this will become time when the delay is finished
}qsm_t;
/************************************************************************************************************************************
 * Prototypes
 ************************************************************************************************************************************/
//qsm.c
uint8_t qsm_init(void);
uint8_t qsm_roomAvail(qsm_type_t type);
uint32_t get_Time(void);
uint8_t qsm_deinit(void);
void clear_qsm(void);
void remove_qsm(qsm_type_t type, uint8_t point);
qsm_status_t add_to_time_qsm(void *func, void *argument, uint32_t time);
qsm_status_t add_to_instant_qsm(void *func, void *argument);
void qsm_shift_left(uint8_t front, qsm_type_t type);
void qsm_shift_right(uint8_t front, qsm_type_t type);
void qsm_dispatch(void);
void qsm_time_setup(qsm_t *qsm);
void qsm_time_interrupt_handler(void);
void qsm_longTime_interrupt_handler(void);

#endif /* QSM_H_ */
