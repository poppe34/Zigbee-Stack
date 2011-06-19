/*
 * USBspi_task.c
 *
 *  Created on: Feb 28, 2011
 *      Author: mattpoppe
 */

#include "compiler.h"
#include "avr/io.h"
#include "conf_spi_master.h"
#include "spi_master.h"
#include "spi_task.h"
#include "led.h"
#include "list.h"
#include "alarms_task.h"
#include "util/delay.h"
#include "zigbee_task.h"




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
	//cli();
	uint8_t len;
	uint8_t flag = 0xAA;
	if(pkt)
	{
        spi_select_device(SPI_USB, &SPI_DEVICE_USB);
		SPIC.DATA = flag;
		while(!spi_is_rx_full(SPI_USB));

	    spi_write_packet(SPI_USB, &(pkt->len), 1);

	    spi_write_packet(SPI_USB, &(pkt->task), 1);

	    spi_write_packet(SPI_USB, &(pkt->subTask), 1);

	    spi_write_packet(SPI_USB, pkt->buf, pkt->len);
	    spi_deselect_device(SPI_USB, &SPI_DEVICE_USB);
	}
	else
	{
		LED_On(LED6_GPIO);
	}		
	sei();
}


void spi_polled(void)
{
	cli();
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
//		alarm_new(5, "Received a SPI Packet with no Length");
		LED_Toggle(LED4_GPIO);
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

}

void spi_IRQ_CB(void)
{
   if(gpio_pin_is_low(USB_IRQ)) 
		spi_polled();
}


ISR(PORTC_INT0_vect)
{
	spi_IRQ_CB();
}



