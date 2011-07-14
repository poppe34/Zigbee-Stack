/*
 * USBspi_task.c
 *
 *  Created on: Feb 28, 2011
 *      Author: mattpoppe
 */

#include "compiler.h"
#include "avr/io.h"
#include "frame.h"
#include "conf_spi_master.h"
#include "spi_master.h"
#include "spi_task.h"
#include "led.h"
#include "list.h"
#include "alarms_task.h"
#include "util/delay.h"
#include "zigbee_task.h"

static direction_t currentSPIpacketDir;
static packet_t *currentSPIpacket;
static spiReady;
static volatile uint8_t packetLength;

struct spi_device SPI_DEVICE_USB = {
	//! Board specific select id
	.id = SPI_USB_DEVICE_ID
};
/************************************************************************/
/* FUNCTION: spi_task_init
/* argument: no
/* return: whether or not the init was successful                       */
/************************************************************************/
void spi_task_init(void)
{
	//enable the SPI interface in the Power Reduction register
	spi_master_init(SPI_USB);

	spi_master_setup_device(SPI_USB, &SPI_DEVICE_USB, SPI_MODE_0,
			SPI_USB_DEFAULT_BAUDRATE, 0);

	spi_enable(SPI_USB);
	
	/* THIS IS JUST FOR TESTING-DEBUGGING */

	((SPI_t *)SPI_USB)->INTCTRL |= SPI_INTLVL0_bm;
	spiReady = YES;
//	return YES;
}

void spi_task(void)
{	


}



uint8_t char_stringLength(char *inx)
{
	U8 len = 0;

	while(*inx)
	{
		len++;
	}

	return len;
}

void spi_sendToDev(packet_t *pkt)
{
	if(pkt && spiReady && (pkt->len != 0))
	{
		cli();
		//set the spi interface as busy
		spiReady = NO;
		
		TM_removeTask(pkt);
		
		//set the spi direction as outgoing
		currentSPIpacketDir = OUTGOING;
		
		/*
		set the pointers to the beginning of the frame. 
		Order of the Frame:
			1. length
			2. task
			3. subTask
			4. Data to be sent
			*/		
		currentSPIpacket = pkt;
		
		//Set the packet length
		packetLength = currentSPIpacket->len;
		
		//reset the pointer to the front of the Packet
		currentSPIpacket->ptr = &currentSPIpacket->len;
		sei();
		
		// Select the USB Device
		spi_select_device(SPI_USB, &SPI_DEVICE_USB);
	//Tell the other device to setup to receive a packet by sending it a 0xAA
		SPIC.DATA = 0xAA;
	}
	else
	{
		while(1);
		
	}	
}


void spi_polled(void)
{
	/*
	cli();
	SPIC.INTCTRL = 0;
	uint8_t display = 0x88;
	packet_t *packet = TM_newPacket();
	if(!(packet)) 
	{
        LED_Toggle(LED5_GPIO);
		sei();
		return;
	}
		
	spi_select_device(SPI_USB, &SPI_DEVICE_USB);

    uint8_t len = 0;

    spi_write_packet(SPI_USB, &display, 1);
	_delay_us(10);
    spi_read_packet(SPI_USB, &(packet->len), 1);
	_delay_us(10);
	len= packet->len;
	
	if(len == 0 || len >= 0x88) 
	{	
        spi_deselect_device(SPI_USB, &SPI_DEVICE_USB);
		sei();
		TM_freePacket(packet);
		return;

	}		
	spi_read_packet(SPI_USB, &(packet->task), 1);
	_delay_us(10);
    spi_read_packet(SPI_USB, &(packet->subTask), 1);
	packet->ptr = packet->buf;
	_delay_us(10);
	spi_read_packet(SPI_USB, packet->ptr, len);

	sei();

	packet->dir = from_device;
	spi_deselect_device(SPI_USB, &SPI_DEVICE_USB);
	((SPI_t *)SPI_USB)->INTCTRL |= SPI_INTLVL0_bm;
	*/
}

void spi_IRQ_CB(void)
{
   if(gpio_pin_is_low(USB_IRQ)) 
		spi_polled();
}

Bool spi_ready(void)
{
	
	return spiReady;
	
}

ISR(PORTC_INT0_vect)
{
	
}

ISR(SPIC_INT_vect)
{
	if(currentSPIpacket)
	{
		if(packetLength)
		{
			((SPI_t *)SPI_USB)->DATA = *currentSPIpacket->ptr++;
			packetLength--;
		}
	
		else 
		{
			spi_deselect_device(SPI_USB, &SPI_DEVICE_USB);
			free(currentSPIpacket);
			currentSPIpacket = NULL;
			spiReady = YES;
		}	
	}		
}

