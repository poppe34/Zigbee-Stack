/*
 * MAC_mlme_poll.c
 *
 *  Created on: Nov 4, 2010
 *      Author: mpoppe
 */

#include <frame.h>

#include <mac/mac_prototypes.h>
#include "MAC/MAC_mlme.h"
#include "MAC/MAC_command.h"

#include "alarms_task.h"



void MAC_mlme_pollReq(addr_t *dstAddr){ //TODO: I need to add security level and key info

	MAC_setTxCB(&MAC_mlme_pollReq_cb);
    MAC_dataRequestCommand(dstAddr);
    
    
}


void MAC_mlme_pollReq_cb(mac_status_t status){

	switch(status){
	case(TRAC_SUCCESS):
		MAC_mlme_pollConf(MAC_SUCCESS);
	break;

	case(TRAC_NO_ACK):
		MAC_mlme_pollConf(MAC_NO_ACK);
	break;

	case(TRAC_CHANNEL_ACCESS_FAILURE):
		MAC_mlme_pollConf(MAC_ACCESS_FAILURE);
	break;

	case(TRAC_INVALID):
		MAC_mlme_pollConf(MAC_INVALID_ADDRESS);
	break;

	case(TRAC_SUCCESS_DATA_PENDING):
		break;
	}

}

void MAC_mlme_pollConf(mac_status_t status){
    status = status;
	alarm_new(9, "Received a Poll confirmation with status:%x", status);
}
