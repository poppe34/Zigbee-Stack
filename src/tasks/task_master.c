/*
 * task_master.c
 *
 * Created: 3/12/2011 5:14:02 AM
 *  Author: matt
 */ 
#include "list.h"
#include "task_master.h"
#include "led.h"
#include "led_task.h"
#include "xplain.h"
#include "ioport.h"
#include "alarms_task.h"
#include "zigbee_task.h"

LIST(packets);
static uint16_t led_count;

void TM_task_init(void)
{
	list_init(packets);
}

void TM_task(void)
{
	uint8_t length;
	
	packet_t *pkt;
	
	length = list_length(packets);
    if(length)
	{
        pkt = list_pop(packets);
		TM_taskHandler(pkt);
	}	
	
	led_count++;
	if((led_count & 0x4000)) LED_On(LED7_GPIO);
	else LED_Off(LED7_GPIO);
}

void TM_addTask(packet_t *pkt)
{
	list_add(packets, pkt);
}

void TM_removeTask(packet_t *pkt)
{
	list_remove(packets, pkt);
}
packet_t *TM_newPacket(void)

{
	if(list_length(packets) >= 30)
	{
        return NULL;
		alarm("(task_manager.c)TM_newPacket:Overflow of packets");
	}	
	packet_t *newPacket = (packet_t *)malloc(sizeof(packet_t));
	
	newPacket->ptr = newPacket->buf;
	
	list_add(packets, newPacket);
	
	return newPacket;
}

void TM_freePacket(packet_t *pkt)
{
	list_remove(packets, pkt);
	free(pkt);
}

void TM_taskHandler(packet_t *pkt)
{
	switch(pkt->task)
	{
		case task_dummy:
			
		break;
			
		case task_LED:
			led_task(pkt);
		break;
			
		case task_alarm:
			alarm_subTaskHandler(pkt);
		break;
		
		case task_zigbee:
			zigbee_SubtaskHandler(pkt);
		break;
		default:
		    alarm("TASK MASTER REACHED AN UNKNOWN TASK");
		break;
			    	
	}
	
	TM_freePacket(pkt);
}