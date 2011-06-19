/*
 * _1_wire.h
 *
 * Created: 6/10/2011 9:44:22 AM
 *  Author: mpoppe
 */ 


#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

#define oneWire_port			ZIGBEE_COORD_GPIO

#define oneWireResetPulse		(485)
#define oneWireReadDelay		(66)



typedef enum {
	oneWire_input = 0x01,
	oneWire_output_high = 0x02,
	oneWire_output_low = 0x03,
	oneWire_high = 0x04,
	oneWire_low = 0x05
}oneWire_ctrl_t;

Bool oneWire_portControl(oneWire_ctrl_t dir);

#endif /* 1-WIRE_H_ */