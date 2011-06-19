/*
 * MAC_RxQueue.h
 *
 * Created: 6/9/2011 10:22:33 AM
 *  Author: mpoppe
 */ 


#ifndef MAC_RXQUEUE_H_
#define MAC_RXQUEUE_H_


void MAC_RxQueue_init(void);
void MAC_RxQueue_add(void *fr);
void MAC_RxQueue_task(void);
void MAC_RxQueue_flush(void);


#endif /* MAC_RXQUEUE_H_ */