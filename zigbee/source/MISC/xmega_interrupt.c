/*
 * xmega_interrupt.c
 *
 * Created: 6/2/2011 5:20:53 PM
 *  Author: matt
 */ 
#include "compiler.h"
#include "board.h"
#include "ioport.h"

#include "conf_board.h"

#include "interrupt.h"

#include "tc.h"
#include "ioport.h"

#include "led.h"

#ifdef XMEGA
#include "RF230/RF230_IRQ.h"

typedef void (*interrupt_cb_t)(void);
interrupt_cb_t cbHandler;

void xmega_interrupt_init(void)
{
	
	ZIGBEE_PORT.INTFLAGS |= PORT_INT0IF_bm;
	
	ZIGBEE_PORT.INT0MASK |= ioport_pin_to_mask(ZIGBEE_IRQ);
	ZIGBEE_PORT.INTCTRL |= PORT_INT0LVL_HI_gc;
	
/*	
	ZIGBEE_PORT.PIN0CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	ZIGBEE_PORT.PIN1CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	ZIGBEE_PORT.PIN2CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	ZIGBEE_PORT.PIN3CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	ZIGBEE_PORT.PIN4CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	ZIGBEE_PORT.PIN5CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	ZIGBEE_PORT.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	ZIGBEE_PORT.PIN7CTRL |= PORT_ISC_INPUT_DISABLE_gc;
*/	


	

	

	
	
}

void xmega_interrupt_setCB(void *cb)
{
	cbHandler = (interrupt_cb_t)cb;
}

ISR(PORTD_INT0_vect)
{
	LED_On(LED1_GPIO);
	cbHandler();
}
#endif