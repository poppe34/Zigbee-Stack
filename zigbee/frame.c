/*
 * zigbee.c
 *
 *  Created on: Sep 13, 2010
 *      Author: mpoppe
 */

#include "frame.h"
#include "list.h"

#include "alarms_task.h"

#include "PHY/rc.h"

#include "MAC/MAC_mlme.h"

//Track all the allocated frames
LIST(frames);

/*--------------------------------------------------------------------------------
 *   function:     frame_init
 *
 *   Description:  This function inits the frames list to track how many frames are 
 *                  currently allocated
 *
 *   Argument 1:   none
 *
 *   return:       none
 --------------------------------------------------------------------------------*/
void frame_init(void)
{
    list_init(frames);
}

/*--------------------------------------------------------------------------------
 *   function:     frame_newFrame
 *
 *   Description:  This function allocates memory for a frame and directs the pointer
 *                  to the beginning of the memory buffer
 *
 *   Argument 1:   none
 *
 *   return:        starting address for a newly allocated memory
 --------------------------------------------------------------------------------*/
frame_t *frame_new(void)
{
    frame_t *fr;
    
    if(list_length(frames)<kFRAME_POOL_SIZE)
    {
        fr = (frame_t *)malloc(sizeof(frame_t));
    }
    else
        alarm("Exceded the max number of frames");
    
	return fr;
}

voidPtr frame_hdr(hdr_type_t type)
{
	voidPtr hdr;
	
	switch(type)
	{
		case mac_hdr:
			hdr = malloc(sizeof(mac_hdr_t));
			((mac_hdr_t *)hdr)->ptr = ((mac_hdr_t *)hdr)->hdr;
			((mac_hdr_t *)hdr)->length = 0;
		break;
		case nwk_hdr:
			hdr = malloc(sizeof(nwk_hdr_t));
			((nwk_hdr_t *)hdr)->ptr = ((nwk_hdr_t *)hdr)->hdr;
			((nwk_hdr_t *)hdr)->length = 0;
		break;
		case aps_hdr:
			hdr = malloc(sizeof(aps_hdr_t));
			((aps_hdr_t *)hdr)->ptr = ((aps_hdr_t *)hdr)->hdr;
			((aps_hdr_t *)hdr)->length = 0;
		break;
		case payload:
			hdr = malloc(sizeof(payload_t));
			((payload_t *)hdr)->ptr = ((payload_t *)hdr)->pl;
			((payload_t *)hdr)->length = 0;
		break;
		case rx_data:
			hdr = malloc(sizeof(frameData_t));
			((frameData_t *)hdr)->ptr = ((frameData_t *)hdr)->frame;
			((frameData_t *)hdr)->length = 0;
		break;
	}
	return hdr;
}
/*--------------------------------------------------------------------------------
 *   function:     Mac_createFrame
 *
 *   Description:  This function populates the frame with MAC data
 *
 *   Argument 1:   MAC data
 *
 *   Argument 2:   Frame
 --------------------------------------------------------------------------------*/
void frame_free(frame_t *fr)
{
    list_remove(frames, fr);
    free(fr);
}

/*--------------------------------------------------------------------------------
 *   function:     frame_sendWithFree
 *
 *   Description:  This function sends the frame to the phy layer to be sent out 
 *                  then frees the allocated memory for that frame
 *
 *   Argument 1:   MAC data
 *
 *   Argument 2:   Frame
 --------------------------------------------------------------------------------*/
void frame_sendWithFree(frame_t *fr)
{	
//****************************
//  Add CRC 
//****************************
	uint8_t txFrame[128];
	uint8_t *ptr;
	uint8_t length = 0;
	
	ptr = txFrame;
    SET_FRAME_DATA(fr->payload, 0x0000, 2);
	if(fr->mac)
	{
		fr->mac->ptr = fr->mac->hdr;
		
		for(uint8_t x = 0;x<fr->mac->length; x++)
		{
			length++;
			*ptr++ = *fr->mac->ptr++;
		}
	}
		if(fr->nwk)
	{
		fr->nwk->ptr = fr->nwk->hdr;
		
		for(uint8_t x = 0;x<fr->nwk->length; x++)
		{
			length++;
			*ptr++ = *fr->nwk->ptr++;
		}
	}	
		if(fr->aps)
	{
		fr->aps->ptr = fr->aps->hdr;
		
		for(uint8_t x = 0;x<fr->aps->length; x++)
		{
			length++;
			*ptr++ = *fr->aps->ptr++;
		}
	}
		if(fr->payload)
	{
		fr->payload->ptr = fr->payload->pl;
		
		for(uint8_t x = 0;x<fr->payload->length; x++)
		{
			length++;
			*ptr++ = *fr->payload->ptr++;
		}
	}			
	rc_send_frame(length, txFrame);
	
	if(fr->mac){free(fr->mac);}
	if(fr->nwk){free(fr->nwk);}
	if(fr->aps){free(fr->aps);}	
	if(fr->payload){free(fr->payload);}
    frame_free(fr);
}
/*--------------------------------------------------------------------------------
 *   function:     Mac_clearAll
 *
 *   Description:  This function deallocates all the data frames
 *
 *   Argument 1:   none
 *
 *   Argument 2:   none
 --------------------------------------------------------------------------------*/
void frame_clearAll(void)
{
    //TODO: add a clear all data frames section
}
/* EOF */
