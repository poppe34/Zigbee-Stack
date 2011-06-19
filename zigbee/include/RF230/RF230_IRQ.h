/*
 * RF230_IRQ.h
 *
 * Created: 6/3/2011 3:55:07 PM
 *  Author: matt
 */ 


#ifndef RF230_IRQ_H_
#define RF230_IRQ_H_

void irq_handler(void);
void set_irq_callBack(void *cb);
void set_default_irq_callBack(void);
void receive_irq_CB(uint8_t irq_status);
void default_irq_CB(uint8_t irq_status);
void RF230_irq_init(void);


#endif /* RF230_IRQ_H_ */