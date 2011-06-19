/*
 * led.c
 *
 *  Created on: Feb 27, 2011
 *      Author: mattpoppe
 */
#include "compiler.h"
#include "led.h"
#include "led_task.h"
#include "ioport.h"
#include "xplain.h"
#include "alarms_task.h"

void led_task_init(void)
{
	
}

/**
* Function: led_task
* Arguments: pointer to the led frame
* Return: none
**/

void led_task(packet_t *pkt)
{
	switch(pkt->subTask)
	{
	case led_off:
		LED_Off(led_pinNum(pkt->buf[0]));
		alarm_new(20, "Device turned off LED %i", pkt->buf[0]);
		break;
	case led_on:
		LED_On(led_pinNum(pkt->buf[0]));
		alarm_new(20, "Device turned on LED %i", pkt->buf[0]);
		break;
	case led_toggle:
		LED_Toggle(led_pinNum(pkt->buf[0]));
		alarm_new(20, "Device toggled LED %i", pkt->buf[0]);
		break;
	case led_status:
		break;
	case led_report:
		break;
	}
}
/**
* Function:		led_pinNum
* Description:	This function adds the offset for Port E to make the LED address
*				IO_ID compatible.
* Arguments:	Pin number for LED port E
* Return:		IO_ID number for LED port + pin
**/
uint8_t led_pinNum(U8 num)
{
	uint8_t pin = PORT_PORTE + num;
	return(pin);
}

void led_cb(void)
{
	
	led_pinNum(4);
}
