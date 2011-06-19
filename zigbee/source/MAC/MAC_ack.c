/*
 * MAC_ack.c
 *
 *  Created on: Sep 24, 2010
 *      Author: mpoppe
 */

#include "compiler.h"

#include "misc/time.h"

#include "mac/mac.h"
#include "mac/mac_prototypes.h"



/*
 * 		This section may very well be a temporary section due to the way i need to handle this in the future...
 *
 *      TODO: 05/25/11 Get rid of most of the code and add a linked list and utilize list.h
 */
uint8_t acks[20];
uint8_t num_of_acks = 0x00;

Bool check_Ack(uint8_t dsn){
	if(num_of_acks > 0){
		for(uint8_t x = 0; x<num_of_acks; x++){
			if(acks[x] == dsn){
				shift_ack(x);
				return YES;
			}//end if
		}//end for
	}//end if

	return NO;
}

void add_ack(uint8_t dsn){
	acks[num_of_acks] = dsn;
	num_of_acks++;

//	qsm_t qsm;
//	qsm.fp = &remove_handler;
//	qsm.arg = dsn;
//	qsm.tc = 100;

}

void remove_handler(uint8_t dsn){
	for(uint8_t x = 0; x<num_of_acks; x++){
		if(acks[x] == dsn){
			acks[x] = 0;
			shift_ack(x);
		}//end if
	}//end for
}//end remove_handler

void shift_ack(uint8_t pos){

	for(uint8_t x=pos; x<num_of_acks;x++){
		acks[x] = acks[x+1];
	}
	num_of_acks--;
}

mac_status_t MAC_waitACK(uint8_t num){
	uint8_t 		waiting_for_ack = YES;
	mac_pib_t 		*mpib 			= get_macPIB();
	mac_status_t 	status;
	uint32_t 		time;

// Setup the ticks for the timeout if there is no ack
	time = get_Time();
	time += (mpib->macAckWaitDuration * aMicroSecPerSymbol);
	while(waiting_for_ack){
		if(get_Time() >= time){
			waiting_for_ack = NO;
			status = MAC_NO_ACK;

			if(check_Ack(num)){
				waiting_for_ack = NO;
				status = MAC_SUCCESS;
			}//end if
		}//end if
	}//end while
}//end MAC_waitACK
