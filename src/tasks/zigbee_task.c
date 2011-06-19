/*
 * zigbee_task.c
 *
 * Created: 4/29/2011 3:08:32 PM
 *  Author: mpoppe
 */ 
#include "zigbee_task.h"



void zigbee_SubtaskHandler(packet_t *pkt)
{
	switch (pkt->subTask)
	{
		case zigbeePacketQty:
		    switch(pkt->dir)
			{
				case to_usb:
				break;
				case from_device:
				break;
			}
		break;
		
		case zigbeePacketFirst:
		    switch(pkt->dir)
			{
				case from_device:
				
				break;
				case from_usb:
				
				break;
				case to_usb:
				spi_sendToDev(pkt);
				break;
			}
		break;
	}
}

void zigbee_newPacket(uint8_t *buf, uint8_t zlen)
{
	packet_t *pkt = TM_newPacket();
	
	pkt->len = zlen;
	pkt->ptr = (pkt->buf);
	
	while(zlen)
	{
		*pkt->ptr++ = *buf++;
		zlen--;
	}

	pkt->dir = to_usb;
	pkt->task = task_zigbee;
	pkt->subTask = zigbeePacketFirst;
	

}
