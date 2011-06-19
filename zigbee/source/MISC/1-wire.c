/*
 * _1_wire.c
 *
 * Created: 6/10/2011 9:42:26 AM
 *  Author: mpoppe
 */ 
#include "compiler.h"
#include "alarms_task.h"

#include "misc/1-wire.h"

#include "ioport.h"
#include "board.h"
#include <util/delay.h>

void oneWire_reset(void)
{
	// init low to Tx reset Pulse
	oneWire_portControl(oneWire_output_low);
	_delay_us(oneWireResetPulse);
	// Make the one wire port an input
	oneWire_portControl(oneWire_input);
	_delay_us(oneWireReadDelay);
	
	// read the port and see if the slave has driven the port low
	if(~(ioport_get_value(oneWire_port)))
	{
		
	}

	
	
	
}




Bool oneWire_portControl(oneWire_ctrl_t dir)
{
	switch(dir)
	{
		case oneWire_input:
			ioport_configure_pin(oneWire_port, IOPORT_DIR_INPUT);
		break;
		case oneWire_output_high:
			ioport_configure_pin(oneWire_port, IOPORT_DIR_OUTPUT);
			ioport_set_pin_high(oneWire_port);
		break;
		case oneWire_output_low:
			ioport_configure_pin(oneWire_port, IOPORT_DIR_OUTPUT);
			ioport_set_pin_low(oneWire_port);
		break;
		
		case oneWire_high:
			ioport_set_pin_high(oneWire_port);
		break;
		
		case oneWire_low:
			ioport_set_pin_low(oneWire_port);	
		break;
		
		default:
			alarm_new(15, "Reached an unknown 1 wire port control ");
		break;
	}
}
