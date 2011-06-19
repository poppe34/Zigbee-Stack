// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief  This is the Radio Control for an Atmel AT86RF230B.
 *
 * \par Application note:
 *
 *
 * \par Documentation
 *
 *
 *
 * \author
 *
 *
 *
 * $Id:
 *
 * Copyright (c) 2010 ,
 *
 *
 *****************************************************************************/

#include "misc/time.h"
#include "alarms_task.h"

#include "frame.h"

#include "PHY/rc_rf230.h"
#include "PHY/phy.h"

#include "RF230/RF230.h"
#include "RF230/at86rf230_registermap.h"
#include "RF230/RF230_IRQ.h"

#include "MAC/mac_prototypes.h"
#include "MAC/MAC_RxQueue.h"

bool wait_for_ack = false;

bool PLL_LOCK_ON = false;




void radio_RF230_init(void) {
	bool status;
	uint8_t dummy_IRQ_read;
    trx_state state;

// Setup the interrupt
	RF230_irq_init();

	set_padIOPwrLevel(0x03);
	   set_rc_CLKM(CLKM_no_clock);
// Allow time for the radio to startup
    delay_us(TIME_TO_ENTER_P_ON);

// Set reset the radio
	RF230_RESET_START;
	RF230_SLP_TR_LOW;
	
	delay_us(TIME_RESET);

	RF230_RESET_END;
	
	RF230registerBitWrite(SR_IRQ_MASK, (0xCf));
	
	delay_us(TIME_SLEEP_TO_TRX_OFF);

	RF230registerBitWrite(SR_TRX_CMD, CMD_FORCE_TRX_OFF);
	
	delay_us(TIME_P_ON_TO_TRX_OFF);

	state = RF230_STATE();
	
// Make sure we are in TRX_OFF state we will putting the transceiver to RX_ON State
	if(TRX_OFF == state) {

	    /* reading IRQ clears any IRQ requests */
		dummy_IRQ_read = RF230registerRead(RG_IRQ_STATUS);
		
		/* put transceiver in CCA mode 3 */
		RF230registerBitWrite(SR_CCA_MODE, 0x03);
		/* Set the state to RX_ON */


	}
		status = set_trx_state(RX_AACK_ON, false);
		state = RF230_STATE();
		alarm_new(5, "The state of the RF230 during INIT is now %x", state);
}

void rc_reset(void){

	RF230_RESET_START;
	RF230_SLP_TR_LOW;
	delay_us(TIME_RESET);

	RF230_RESET_END;
}

void rc_reset_stateMachine(void){

// This section assumes that the transceiver is not in SLEEP or P_ON state.

	RF230_SLP_TR_LOW; //insure transceiver is not in any noCLK state
	delay_us(TIME_RESET);

	RF230registerBitWrite(SR_TRX_CMD, CMD_FORCE_TRX_OFF); // Force into TRX_OFF state
	delay_us(TIME_RESET);
}

void rc_goto_sleep(void){

	if(set_trx_state(TRX_OFF, false)) {

		RF230_SLP_TR_LOW;
		delay_us(TIME_TRX_OFF_TO_SLEEP);
	}
}


void rc_wakeup(void) {

	RF230_SLP_TR_LOW;
	delay_us(TIME_SLEEP_TO_TRX_OFF);

}

cca_mode_t get_CCAmode(void) {
				
		return((cca_mode_t)(RF230BitRead(SR_CCA_MODE)));

}

void set_CCAmode(cca_mode_t mode) {
		
	RF230registerBitWrite(SR_CCA_MODE, (cca_mode_t)mode);

}


uint8_t get_currentChannel(void){
// This section assumes that the transceiver is not in SLEEP or P_ON state.

	return (RF230BitRead(SR_CHANNEL)); //reads what channel the transciever is on.

}

bool set_auto_CRC_on(void) {
	bool status = false;
	
	RF230registerBitWrite(SR_TX_AUTO_CRC_ON, 0x01);

	if(get_auto_CRC() == 0x01){

		status = true;
	}

	return status;
}

bool set_auto_CRC_off(void) {
	bool status = false;
	
	RF230registerBitWrite(SR_TX_AUTO_CRC_ON, 0);

	if(get_auto_CRC() == 0){

		status = true;
	}

	return status;
}

uint8_t get_auto_CRC(void) {

	return(RF230BitRead(SR_TX_AUTO_CRC_ON));

}
bool set_currentChannel(uint8_t channel) {

	uint8_t status = false;
	trx_state_t state = (RF230BitRead(SR_TRX_STATUS));

	if((TRX_SLEEP == state) || (P_ON == state)) {
		return status;
	}

	RF230registerBitWrite(SR_CHANNEL, channel);

	if (get_currentChannel() == channel){

		status = true;
		return status;
	}

	else {

		return status;

	}
}

uint8_t get_tx_pwr(void){
// This section assumes that the transceiver is not in SLEEP or P_ON state.

	return (RF230BitRead(SR_TX_PWR)); //reads what tx power level the transceiver is set to.

}


bool set_tx_pwr(uint8_t level) {

	uint8_t status = false;
	uint8_t state = (RF230BitRead(SR_TRX_STATUS));

	if((TRX_SLEEP == state) || (P_ON == state)) {
		return status;
	}

	RF230registerBitWrite(SR_TX_PWR, level);

	if (get_tx_pwr() == level){
		status = true;
		return status;
	}

	else {

		return status;

	}
}

bool set_trx_state(trx_state_t state, bool force) {
    uint8_t new_status;
	uint8_t status = RF230_STATE(); //Get the original status of the transceiver


	// check if new state is a valid to transition
	if((state != TRX_OFF) && (state != RX_ON) && (state != PLL_ON) && (state != RX_AACK_ON) && (state != TX_ARET_ON)) {

		return NO;
	}
	//
	//	transition to TRX_OFF
	//
	switch(state) {

		case TRX_OFF:

			; //make sure we are not in sleep

			// check if transceiver is in a state that will transfer to TRX_OFF
			if( (status == RX_ON) || (status == PLL_ON) || (status == RX_AACK_ON) || (status == TX_ARET_ON)) {

				RF230registerBitWrite(SR_TRX_CMD, CMD_TRX_OFF);
				delay_us(TIME_CMD_FORCE_TRX_OFF);
			}

			else if(force) { //if force is allowed force the transfer

				RF230registerBitWrite(SR_TRX_CMD, CMD_FORCE_TRX_OFF);
				delay_us(TIME_CMD_FORCE_TRX_OFF);
			}

		break;

		case RX_ON:
	//
	//	transition to RX_ON
	//

			if (status == TRX_OFF) {
				RF230registerBitWrite(SR_TRX_CMD, CMD_RX_ON);
				delay_us(TIME_TRX_OFF_TO_PLL_ACTIVE);
			}

			else if((status == RX_AACK_ON) || (status == RX_ON) || (status == PLL_ON) || (status == TX_ARET_ON)) {

				RF230registerBitWrite(SR_TRX_CMD, CMD_RX_ON);
				delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);
			}

		break;
	//
	//	transition to PLL_ON
	//
		case PLL_ON:

			if (status == TRX_OFF) {
				RF230registerBitWrite(SR_TRX_CMD, CMD_PLL_ON);
				delay_us(TIME_TRX_OFF_TO_PLL_ACTIVE);
			}

			else {

				RF230registerBitWrite(SR_TRX_CMD, CMD_PLL_ON);
				delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);

			}
		break;

		case RX_AACK_ON:

			if (status == TRX_OFF) {

				RF230registerBitWrite(SR_TRX_CMD, CMD_RX_ON);
				delay_us(TIME_TRX_OFF_TO_PLL_ACTIVE);
				status = RF230_STATE();
			}
			

			if ((status == RX_ON) || (status == PLL_ON)) {

				RF230registerBitWrite(SR_TRX_CMD, CMD_RX_AACK_ON);
				delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);
			}
			else if (status == TX_ARET_ON) {

				RF230registerBitWrite(SR_TRX_CMD, CMD_RX_ON);
				delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);

				RF230registerBitWrite(SR_TRX_CMD, CMD_RX_AACK_ON);
				delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);
			}
		break;

		case TX_ARET_ON:

			if (status == TRX_OFF) {

				RF230registerBitWrite(SR_TRX_CMD, CMD_RX_ON);
				delay_us(TIME_TRX_OFF_TO_PLL_ACTIVE);
				status = RF230_STATE();
			}
			

			if ((status == RX_ON) || (status == PLL_ON)) {

				RF230registerBitWrite(SR_TRX_CMD, CMD_TX_ARET_ON);
				delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);
			}
			else if (status == RX_AACK_ON) {

				RF230registerBitWrite(SR_TRX_CMD, CMD_RX_ON);
				delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);

				RF230registerBitWrite(SR_TRX_CMD, CMD_TX_ARET_ON);
				delay_us(TIME_STATE_TRANSITION_PLL_ACTIVE);
			}
		break;

		case TRX_SLEEP:

				RF230registerBitWrite(SR_TRX_CMD, CMD_FORCE_TRX_OFF);
				delay_us(TIME_CMD_FORCE_TRX_OFF);

				RF230_SLP_TR_HIGH;
		break;

		default:

			return false;

	}
  	new_status = RF230_STATE();
	// Did the transition work correctly?



	if(new_status == state) {

		return true;
	}

	else {
		return false;
	}
}

bool set_rc_CLKM(uint8_t speed)
{
	bool status = false;
	RF230registerBitWrite(SR_CLKM_CTRL, speed);
	
	if((get_rc_CLKM()) == speed)
	{
		status = true;
	}
	return status;
}

uint8_t get_rc_CLKM(void)
{
	return(RF230BitRead(SR_CLKM_CTRL));
}


void rc_rx_frame(void) {

// setup the location for the frame
	frame_t *fr = frame_new();
	fr->Rx_fr = frame_hdr(rx_data);
	
	fr->direction = INCOMING;

	uint8_t state = RF230_STATE();
	alarm_new(5, "The state of the RF230 before Rx is now %x", state);
	
#ifdef debug
//	TODO: Setup a debugging section
//		post_log(get_Time,"Frame Received")
#endif

	fr->Rx_fr->length = RF230frameRead(fr->Rx_fr->frame);
//	TODO:	I need to setup the RTC right now it defaults to a 16 bit number
	fr->Rx_fr->ptr++;
	fr->LQI = *fr->Rx_fr->ptr;
	fr->Rx_fr->ptr++;
	
	fr->timestamp = get_Time();


// Move to the MAC layer
	MAC_RxQueue_add(fr);

}
bool rc_send_frame(uint8_t len, uint8_t *frame_tx) {
//	TODO: I am not sure if I need to preform a CSMA-
	bool status = false;

	/* Make sure we are sending another frame */
	while(wait_for_ack == true) {;}
	set_irq_callBack(&PHY_TxIrqCB);

	while(!(set_trx_state(TX_ARET_ON, 0))) {;}
	/* toggle the SLP_TR to initiate the transfer */

	/*Send frame to RF230*/
		RF230frameWrite(frame_tx, len);
		RF230_SLP_TR_HIGH;
		RF230_SLP_TR_LOW;

	/*Report back a successful transmit*/
		status = true;


	return status;
}


void set_shortAddr(uint16_t addr) {

	RF230registerWrite(RG_SHORT_ADDR_0, addr);
	RF230registerWrite(RG_SHORT_ADDR_1, (uint8_t)(addr>>8));

}

uint16_t get_short_ADDR(void) {
 	uint16_t temp_value;
 	temp_value = RF230registerRead(RG_SHORT_ADDR_1);
 	temp_value << 8;
 	temp_value |= RF230registerRead(RG_SHORT_ADDR_0);

 	return temp_value;
}
void set_PANid(uint16_t pan) {
	RF230registerWrite(RG_PAN_ID_0, (uint8_t)pan);
	RF230registerWrite(RG_PAN_ID_1, (uint8_t)(pan>>8));
}

uint16_t get_PANid(void) {
 	uint16_t temp_value;
 	temp_value = RF230registerRead(RG_PAN_ID_1);
 	temp_value = temp_value << 8;
 	temp_value |= RF230registerRead(RG_PAN_ID_0);
 	return temp_value;
}
void set_IEEE_ADDR(uint64_t addr) {

	uint8_t reg = RG_IEEE_ADDR_0, x;

	for(x=0; (x<8); x++) {
		RF230registerWrite(reg, addr>>(8*x));
		reg++;
	}
}
uint64_t get_IEEE_ADDR(void) {

	uint64_t ieee;
	uint8_t reg = RG_IEEE_ADDR_0;

	for (uint8_t i=0;i<8;i++){

		ieee |= (((uint64_t)RF230registerRead(reg))<< (8*i));
		reg++;
	}

	return ieee;
}

void turn_ON_CRC(void){

	RF230registerBitWrite(SR_TX_AUTO_CRC_ON, on);

}
void I_AM_COORD(uint8_t coord) {

	if(coord){
		RF230registerBitWrite(SR_I_AM_COORD, 0x01);
	}

	else{
		RF230registerBitWrite(SR_I_AM_COORD, 0x00);
	}
}

Bool is_Coord(void)
{
	return (RF230BitRead(SR_I_AM_COORD));
}

uint16_t get_CSMA_seed(void) {

	uint16_t CSMA;
	uint8_t dummy;

	CSMA = (uint16_t)RF230registerRead(RG_CSMA_SEED_0);
	dummy = RF230BitRead(SR_CSMA_SEED_0);
	CSMA |= (uint16_t)(dummy << 8);

	return CSMA;

}

bool set_CSMA(uint16_t csma){

	uint8_t octet;

	octet = (uint8_t)csma;

	RF230registerWrite(RG_CSMA_SEED_0, octet);

	octet = (csma >> 8) & 0xff;
	RF230registerBitWrite(SR_CSMA_SEED_0, octet);

	return(csma == get_CSMA_seed());

}

uint8_t get_MIN_BE(void){

	return(RF230BitRead(SR_MIN_BE));

}

bool set_MIN_BE(uint8_t be){

	
	RF230registerBitWrite(SR_MIN_BE, be);

	return(be == get_MIN_BE());

}

uint8_t get_frame_retries (void){

	return RF230BitRead(SR_MAX_FRAME_RETRIES);
}

bool set_frame_retries(uint8_t fr){


	RF230registerBitWrite(SR_MAX_FRAME_RETRIES, fr);

	return(fr == get_frame_retries());

}

uint8_t get_CSMA_retries (void){

	return RF230BitRead(SR_MAX_CSMA_RETRIES);
}

bool set_CSMA_retries(uint8_t Cr){

	RF230registerBitWrite(SR_MAX_CSMA_RETRIES, Cr);

	return(Cr == get_CSMA_retries());

}

uint8_t get_aack_set_pd (void){

	return RF230BitRead(SR_MAX_CSMA_RETRIES);
}

bool set_aack_set_pd(uint8_t aack){

	RF230registerBitWrite(SR_MAX_CSMA_RETRIES, aack);

	return(aack == get_aack_set_pd());

}

bool set_padIOPwrLevel(uint8_t level)
{
	bool status = NO;
	
	RF230registerBitWrite(SR_PAD_IO, level);

	if(get_padIOPwrLevel() == level)
		{
			status = YES;
		}

	return status;
}

uint8_t get_padIOPwrLevel(void)
{
	return RF230BitRead(SR_PAD_IO);
}
