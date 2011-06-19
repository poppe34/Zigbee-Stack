/*
 * USBspi_task.h
 *
 *  Created on: Feb 28, 2011
 *      Author: mattpoppe
 */

#ifndef USBSPI_TASK_H_
#define USBSPI_TASK_H_




#include "task_master.h"


#define SHORT_DELAY _delay_us(40)


typedef struct spi_packet{
	uint8_t     len;
	uint8_t     task;
    uint8_t     data[64];
	uint8_t     *ptr;	
}__attribute__((packed));



typedef struct spi_packet spi_packet_t;

#define reset_spi_pointer(pkt)  pkt->ptr = pkt->buf


void spi_send_alarm(char *inx);
uint8_t char_stringLength(char *inx);
void spi_IRQ_CB(void);
void spi_polled(void);
void spi_sendToDev(packet_t *pkt);
void spi_task_init(void);


#endif /* USBSPI_TASK_H_ */
