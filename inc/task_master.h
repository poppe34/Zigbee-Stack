/*
 * task_master.h
 *
 * Created: 3/12/2011 5:19:18 AM
 *  Author: matt
 */ 


#ifndef TASK_MASTER_H_
#define TASK_MASTER_H_

#include "compiler.h"

#define TASK_LIST_MAX_SIZE  10
#define BYTES_NEEDED_FOR_LENGTH 1

typedef enum data_direction
{
    to_device = 1,
	from_device = 2,
	from_usb = 3,
	to_usb = 4
}dir_t;

typedef enum{
	task_dummy 	= 0x00,
	task_LED 	= 0x01,
	task_alarm	= 0x02,
	task_zigbee	= 0x03,
}task_t;


typedef struct packet
{
	struct packet       *next;
	uint8_t             buf[64];
	uint8_t             *ptr;
	uint8_t               dir;
	uint8_t             len;
	uint8_t             task;
	uint8_t             subTask;
}packet_t;


void TM_task_init(void);
void TM_task(void);
void TM_addTask(packet_t *pkt);
packet_t *TM_newPacket(void);
void TM_freePacket(packet_t *pkt);
void TM_taskHandler(packet_t *pkt);
void TM_removeTask(packet_t *pkt);

#endif /* TASK_MASTER_H_ */