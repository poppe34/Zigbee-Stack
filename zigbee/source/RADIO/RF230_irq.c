/*
 * RF230_irq.c
 *
 *  Created on: Sep 28, 2010
 *      Author: mpoppe
 */

#include <frame.h>
#include <phy/phy.h>
#include <conf_zigbee.h>
#include <rf230/at86rf230_registermap.h>
#include <avr/interrupt.h>
#include <RF230/RF230.h>
#include "phy/rc_rf230.h"
#include "alarms_task.h"
#include "led.h"
#include "board.h"
#include "tc.h"

#include "misc/xmega_misc.h"

#include "RF230/RF230_IRQ.h"

#include "MAC/mac_prototypes.h"

typedef void (*rf230_irq_cb_t)(uint8_t irq_status);

rf230_irq_cb_t rf230_irq_cb = &default_irq_CB;

bool Rx_incoming = 0x00;
uint8_t counter = 0x00;
bool new_rx = 0x00;

void RF230_irq_init(void)
{
	uint8_t status = RF230registerRead(RG_IRQ_STATUS);
	xmega_interrupt_setCB(&irq_handler);
	xmega_interrupt_init();
	
}

void set_irq_callBack(void *cb) {

	cli();
	rf230_irq_cb = (rf230_irq_cb_t)cb;
	sei();
}

void set_default_irq_callBack(void){

	cli();
	rf230_irq_cb= &default_irq_CB;
	sei();
}

void default_irq_CB(uint8_t irq_status){
	if(((irq_status >> RX_START) & 0x01)) 
	{
		set_irq_callBack(&receive_irq_CB);
		//alarm_new(9, "Started to receive a new Packet");
	}//end if
	if(((irq_status>> TRX_END) & 0x01))
		{
		alarm_new(9, "Received a new Packet: default CB");
		rc_rx_frame();
		}	
}//end default_irq_cb

void receive_irq_CB(uint8_t irq_status){

	if(((irq_status>> TRX_END) & 0x01)){
		
		alarm_new(9, "Received a new Packet: receive CB");
		rc_rx_frame();
		
		//set_default_irq_callBack();
	}//end if
	
}//end receive_irq_CB

void PHY_TxIrqCB(uint8_t irq_status){

	phy_trac_t trac;
	mac_status_t status;
	if(((irq_status>> TRX_END) & 0x01)){
		trac =(phy_trac_t)RF230BitRead(SR_TRAC_STATUS);
		
		alarm_new(5, "TRAC STATUS is:%x", trac);
		switch(trac){
		case(TRAC_SUCCESS):
			status = MAC_SUCCESS;
			set_default_irq_callBack();
		break;

		case(TRAC_SUCCESS_DATA_PENDING):
			status = MAC_SUCCESS;
			set_default_irq_callBack();
		break;

		case(TRAC_CHANNEL_ACCESS_FAILURE):
			status = MAC_TRANSACTION_EXPIRED;
			set_default_irq_callBack();
		break;

		case(TRAC_NO_ACK):
			status = MAC_NO_ACK;
			set_default_irq_callBack();
		break;

		case(TRAC_INVALID):
			set_default_irq_callBack();
		break;

		}//end switch
		set_trx_state(RX_AACK_ON, 0);
		MAC_txStatus(trac);
					
	}//end if
}//end PH_TxIrqCB


void irq_handler(void)
{
		uint8_t irq_status = RF230registerRead(RG_IRQ_STATUS);
		(rf230_irq_cb)(irq_status);
}
