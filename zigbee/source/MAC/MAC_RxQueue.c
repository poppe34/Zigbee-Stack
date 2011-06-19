
/*
 * MAC_RxQueue.c
 *
 * Created: 6/9/2011 9:52:07 AM
 *  Author: mpoppe
 */ 
#include "compiler.h"

#include "frame.h"
#include "list.h"

#include "MAC/mac_prototypes.h"
#include "tasks/zigbee_task.h"

/*********************************************************
              Variable Declarations
**********************************************************/
LIST(RxQueue);

/************************************************************************
	 Function:    MAC_RxQueue_init

Description: This function initiates the Received packets Queue
				
 Arguments:   none

 Return:      none                      
*************************************************************************/
void MAC_RxQueue_init(frame_t *fr)
{
	list_init(RxQueue);
}

/************************************************************************
Function:	MAC_RxQueueInit_task

Discript:	This function initiates the Received packets Queue
				
Arguments:  none

Return:     none                      
*************************************************************************/

void MAC_RxQueue_task(void)
{
	// Check if there are any packets in the queue and dispatch top packet
	if(list_length(RxQueue))
	{
		
		frame_t *fr = (frame_t *)(list_pop(RxQueue));
		report_packet(fr->Rx_fr->frame, fr->Rx_fr->length);
		
		MAC_incomingFrame(fr);
		free(fr);
	}
};

/************************************************************************
Function:	MAC_RxQueueInit_task

Discript:	This function clears out the receive queue
				
Arguments:  none

Return:     none                      
*************************************************************************/
void MAC_RxQueue_flush(void)
{
	frame_t *fr;
	uint8_t length = list_length(RxQueue);
		
	while(length)
	{
		fr = list_pop(RxQueue);
		frame_free(fr);	
		length--;
	}
}

/************************************************************************
Function:	MAC_RxQueueInit_add

Discript:	This function addes a frame to the queue
				
Arguments:  none

Return:     none                      
*************************************************************************/
void MAC_RxQueue_add(void *fr)
{
	list_add(RxQueue, fr);
}
