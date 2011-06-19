/*
 * MAC_ack.c
 *
 *  Created on: Sep 23, 2010
 *      Author: mpoppe
 */
#include "conf_zigbee.h"
#include <frame.h>

#include "MAC/MAC_mlme.h"
#include "MAC/mac_prototypes.h"
#include "MAC/MAC_command.h"
#include "MAC/MAC.h"

#include "MISC/qsm.h"
#include "MISC/time.h"
#include "alarms_task.h"

typedef void (*mac_assocHandler_t)(mac_status_t status);
mac_assocHandler_t assocHandler;

// This Is so I know what state we are in while performing the assoc Request
static uint8_t waiting_for_AssocResponce = 0, waiting_for_info = 0;
// This keeps what the pan Coord address is that we are attempting to Join
static addr_t coordAddr;

void MAC_mlme_assocReq(addr_t *destAddr, uint32_t page, uint8_t channel, uint8_t capabilites, security_t *sec)
{
    alarm_new(9, "MLME associate Request initiated");
	//
    MAC_setCurrentChannel(channel);
	coordAddr = *destAddr;
// TODO: I need to add the security values...
// TODO: I need to set up the page methods....

	MAC_setTxCB(&MAC_mlme_assocReq_cb);
	MAC_assocRequestCommand(destAddr, capabilites, sec);	
	waiting_for_AssocResponce = 1;
	MAC_setPANid(coordAddr.PANid);
}

void MAC_mlme_assocReq_cb(phy_trac_t trac){
	short_addr_t badAddr;
	security_t sec;
	badAddr = 0xffff;
	mac_pib_t *mpib = get_macPIB();
	
	switch(trac){
	case(TRAC_SUCCESS):
	
		if(waiting_for_info)
		{
			alarm_new(9, "Successful Tx of DataReq for assocReq");
			waiting_for_info = 0;
			mpib->macAssociatedPANCoord = YES;
			if(coordAddr.mode == MAC_SHORT_ADDRESS)
			{
				mpib->macCoordShortAddress = coordAddr;
			}
			else if(coordAddr.mode == MAC_LONG_ADDRESS)
			{
				mpib->macCoordExtendedAddress = coordAddr;
			}
			
		}
    
		if(waiting_for_AssocResponce)
		{
		   alarm_new(9,"Successful Tx of AssocReq");
		   add_to_time_qsm(&MAC_dataRequestCommand, &coordAddr, (Symbols_to_Time(macResponseWaitTime)));
		   waiting_for_AssocResponce = 0;
		   waiting_for_info = 1;
		 
		   
		}
	break;

	case(TRAC_NO_ACK):
		MAC_mlme_assocConf(MAC_NO_ACK, badAddr, &sec);
	break;

	case(TRAC_CHANNEL_ACCESS_FAILURE):
		MAC_mlme_assocConf(MAC_ACCESS_FAILURE,  badAddr, &sec);
	break;

	case(TRAC_INVALID):
		MAC_mlme_assocConf(MAC_INVALID_ADDRESS, badAddr, &sec);
	break;

	case(TRAC_SUCCESS_DATA_PENDING):
		break;
	}
	
}

void MAC_mlme_assocReqHandler(mpdu_t *mpdu, frame_t *fr)
{
	if(MAC_isPanCoord())
	{
		mac_capibilities_t capib = *((mac_capibilities_t *)(fr->Rx_fr->ptr));
		fr->Rx_fr->ptr += sizeof(mac_capibilities_t);
	
		alarm_new(9, "MAC Request Command Received with cap: %.2x ", (capib));
	
		if(mpdu->source.mode != MAC_LONG_ADDRESS)
		{
			alarm_new(9, "Invalid source mode in an Assoc Request");
		}
	
		MAC_mlme_assocInd(&mpdu->source.extAddr, capib, &mpdu->sec);
	}		
}

void MAC_mlme_assocRespHandler(mpdu_t *mpdu, frame_t *fr)
{
	alarm_new(9, "Received an Assoc Request");
	
	mac_pib_t *mpib = get_macPIB();
	
    short_addr_t addr = GET_FRAME_DATA(fr->Rx_fr, 2);
	uint8_t	command_status = GET_FRAME_DATA(fr->Rx_fr, 1);
	
	/*   Indicate that we are attached to a network and update the device of our new 
		short addr. */
			
	MAC_setAssoc(YES);

	if(mpdu->source.mode == MAC_SHORT_ADDRESS)
		{
			mpib->macCoordShortAddress = coordAddr;
		}
	else if(mpdu->source.mode == MAC_LONG_ADDRESS)
		{
			mpib->macCoordExtendedAddress = coordAddr;
		}
		
	MAC_setShortAddr(addr);
	
	
	MAC_mlme_assocConf(MAC_SUCCESS, addr, null);
    
}

void MAC_mlme_assocConf(mac_status_t status, short_addr_t *addr, security_t *sec)
{
	alarm_new(9, "Received an Associate Confirm with the status: %x", status);

	status = status;
	addr = addr;
	sec = sec;
	
}

void MAC_mlme_assocInd(long_addr_t *addr, mac_capibilities_t capib, security_t *sec)
{
    alarm_new( 9, "I received an MAC Assoc Request");
	addr = addr;
	capib = capib;
	sec = sec;
}