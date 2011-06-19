/*
 * mac_command.c
 *
 *  Created on: Sep 12, 2010
 *      Author: mpoppe
 */
#include "frame.h"

#include <MAC/mac_prototypes.h>
#include "MAC/MAC_command.h"
#include "MAC/MAC_mlme.h"


#include "alarms_task.h"

uint8_t temp;
/*------------------------------------------------------------------------------------------
 * Function:    MAC_dataRequestCommand
 *
 * Description: This function sends out a request for data command frame 
 *
 * arg: mpdu *** I am not sure if this is the right type of arg for this situation I may change it
 *                but this is to know where to send the data request to
 *
 * brief: This is initiated in one of three ways.
 *           1. if a beacon frame is received with this devices address
 *           2. if initiated by next higher layer on reception of MLME-POll.request
 *           3. a device may send this command to the coordinator macResponseWaitTime symbols after the
 *               acknowledgment to an association request command.
 *------------------------------------------------------------------------------------------*/
uint8_t MAC_assocRequestCommand(addr_t *destAddr, uint8_t capibilities, security_t *sec)
{
	mac_pib_t *mpib = get_macPIB();
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);

	mpdu_t	*mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	uint8_t seq_num;

	if(!(MAC_isAssoc()))
	{
  
        mpdu->destination = *destAddr;
		mpdu->source = mpib->macLongAddress;
  		
	    mpdu->fcf.MAC_fcf_Frame_Type = MAC_COMMAND;
	    mpdu->fcf.MAC_fcf_DstAddr_Mode = destAddr->mode;
	    mpdu->fcf.MAC_fcf_SrcAddr_Mode = MAC_LONG_ADDRESS;
	    mpdu->fcf.MAC_fcf_PANid_Compression = no;
	    mpdu->fcf.MAC_fcf_Frame_Pending = no;
	    mpdu->fcf.MAC_fcf_Ack_Request = yes;
	    mpdu->fcf.MAC_fcf_Sec_enabled = no;
	    mpdu->fcf.MAC_fcf_Frame_Ver = 0x00;
		
        MAC_createFrame(mpdu, fr);
	
        SET_FRAME_DATA(fr->payload, MAC_ASSOC_REQUEST, 1);
	
	    SET_FRAME_DATA(fr->payload, capibilities, 1);
        
		frame_sendWithFree(fr);
		free(mpdu);
		
		return seq_num;
	}
}
/*------------------------------------------------------------------------------------------
 * Function:    MAC_dataRequestCommand
 *
 * Description: This function sends out a request for data command frame 
 *
 * arg: mpdu *** I am not sure if this is the right type of arg for this situation I may change it
 *                but this is to know where to send the data request to
 *
 * brief: This is initiated in one of three ways.
 *           1. if a beacon frame is received with this devices address
 *           2. if initiated by next higher layer on reception of MLME-POll.request
 *           3. a device may send this command to the coordinator macResponseWaitTime symbols after the
 *               acknowledgment to an association request command.
 *------------------------------------------------------------------------------------------*/
uint8_t MAC_assocResponceCommand(mlme_assoc_t *assoc)
{
//	Start a frame and get the PIB data needed to generate an assoc req.
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	
	mpdu_t	*mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));

	mac_pib_t *mpib = get_macPIB();

// Setup the channel
	MAC_setCurrentChannel(assoc->LogicalChannel);

// Setup Coord address
	mpdu->destination = assoc->Coord;

	mpdu->source = mpib->macLongAddress;

//	TODO:	I need to add a function that place our PAN id the coord's after the ack. not before like below
	MAC_setPANid(assoc->Coord.PANid);
	MAC_setCoordPANid(assoc->Coord.PANid);

	if(assoc->Coord.mode == SHORT_ADDRESS){
		MAC_setCoordShortAddr(assoc->Coord.shortAddr);
	}
	else{
		MAC_setCoordLongAddr(assoc->Coord.extAddr);
	}


	mpdu->fcf.MAC_fcf_Frame_Type = MAC_COMMAND;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = assoc->Coord.mode;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = MAC_LONG_ADDRESS;
	mpdu->fcf.MAC_fcf_PANid_Compression = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = yes;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Ver = 0x00;



//	TODO: 	this needs to point to my PAN Table choice (I think) It might be to early to have this as the PANid  we haven't joined yet
//			9.23.10 I made this an argument of the function to pass what the panID we are talking to is.



//1. get the MAC setup of the frame
	MAC_createFrame(mpdu, fr);

//2. device's capabilities
	//command type
	SET_FRAME_DATA(fr->payload, MAC_ASSOC_RESPONCE, 1);
   
    //capabilities info the command type 
	SET_FRAME_DATA(fr->payload, assoc->CapabilityInfo, 1);
    
	

	frame_sendWithFree(fr);
    free(mpdu);
	
}	
/*------------------------------------------------------------------------------------------
 * Function:    MAC_dataRequestCommand
 *
 * Description: This function sends out a request for data command frame 
 *
 * arg: mpdu *** I am not sure if this is the right type of arg for this situation I may change it
 *                but this is to know where to send the data request to
 *
 * brief: This is initiated in one of three ways.
 *           1. if a beacon frame is received with this devices address
 *           2. if initiated by next higher layer on reception of MLME-POll.request
 *           3. a device may send this command to the coordinator macResponseWaitTime symbols after the
 *               acknowledgment to an association request command.
 *------------------------------------------------------------------------------------------*/
void MAC_disassocCommand(addr_t *destAddr, mac_disassoc_reason_t reason)
{
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	uint8_t seq_num;
	mac_status_t status;
 
	
//Setup Command Frame
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_COMMAND;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = destAddr->mode;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = MAC_LONG_ADDRESS;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = yes;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;

	mpdu->destination = *destAddr;//TODO: This needs to point somewhere else maybe??? 9.23.10 I think this might be right

	mpdu->source = mpib->macLongAddress;
    
    //Form mac frame
    MAC_createFrame(mpdu, fr);
    
    //Command Frame Type
	SET_FRAME_DATA(fr->payload, MAC_DISASSOC_NOTIFY, 1);

    //Reason for the Disassociation
	SET_FRAME_DATA(fr->payload, reason, 1);

// Free the memory
    frame_sendWithFree(fr);
	free(mpdu);
}

/*------------------------------------------------------------------------------------------
 * Function:    MAC_dataRequestCommand
 *
 * Description: This function sends out a request for data command frame 
 *
 * arg: mpdu *** I am not sure if this is the right type of arg for this situation I may change it
 *                but this is to know where to send the data request to
 *
 * brief: This is initiated in one of three ways.
 *           1. if a beacon frame is received with this devices address
 *           2. if initiated by next higher layer on reception of MLME-POll.request
 *           3. a device may send this command to the coordinator macResponseWaitTime symbols after the
 *               acknowledgment to an association request command.
 *------------------------------------------------------------------------------------------*/
uint8_t MAC_dataRequestCommand(addr_t *dstAddr)
{
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	
    mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
   
	phy_pib_t *ppib = get_phyPIB();
	mac_pib_t *mpib = get_macPIB();

//1. Setup FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_COMMAND;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = dstAddr->mode;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = LONG_ADDRESS;
	if(dstAddr->mode == 0)
	{
			mpdu->fcf.MAC_fcf_PANid_Compression = no;
	}

	else
	{
			mpdu->fcf.MAC_fcf_PANid_Compression = YES;
	}
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = yes;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;

//2. setup source & destination
    mpdu->destination = *dstAddr;
	mpdu->source = mpib->macLongAddress;//TODO: I don't know which to use short or long address?

//3. get a sequence number
   mpdu->seq_num = get_MAC_seqNum();

//Form Mac frame	
    MAC_createFrame(mpdu, fr);

    SET_FRAME_DATA(fr->payload, MAC_DATA_REQUEST, 1);
    
	frame_sendWithFree(fr);
	free(mpdu);

    //TODO: Add code here to added waiting for ack shouldn't have to return seq_num unless 
    //      I see need for it in the future.
	return mpdu->seq_num;

}
uint8_t MAC_panIDConflictCommand(void)
{
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	
    mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
    uint8_t seq_num;
	
	mac_pib_t *mpib = get_macPIB();

//1. Setup FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_COMMAND;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = LONG_ADDRESS;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = LONG_ADDRESS;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = yes;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;

//2. Setup Address
    mpdu->source = mpib->macLongAddress;
	mpdu->destination = mpib->macCoordExtendedAddress;
	
//3. Setup Sequence Number

//4. Form Mac Frame
    MAC_createFrame(mpdu, fr);

//5. Add command Type
	SET_FRAME_DATA(fr->payload, MAC_PAN_CONFLICT_NOTIFY, 1);
	
	frame_sendWithFree(fr);
	free(mpdu);
	
	return seq_num;
}
uint8_t MAC_orphanCommand(void)
{
    mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	
	mac_pib_t *mpib = get_macPIB();

//1. Setup FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_COMMAND;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = MAC_SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = LONG_ADDRESS;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = yes;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
//2. Setup Addresses
	mpdu->destination.PANid = 0xffff;
	mpdu->destination.extAddr = 0xffff;
	mpdu->destination.mode = MAC_SHORT_ADDRESS;
    mpdu->source = mpib->macLongAddress;
	

//4. Form MAC Frame
    MAC_createFrame(mpdu, fr);

//5. Add command Type
	SET_FRAME_DATA(fr->payload, MAC_ORPHAN_NOTIFY, 1);
	
	frame_sendWithFree(fr);
	free(mpdu);
	
	return 1;
}


/*------------------------------------------------------------------------------------------
 * Function:    MAC_beaconCommand
 *
 * Description: This function sends out a beacon 
 *
 * arg: none
 *
 * brief: 
 *------------------------------------------------------------------------------------------*/
void MAC_beaconReqCommand(void)
{
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);

//Setup for the FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_COMMAND;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = MAC_SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = MAC_NO_ADDRESS;
	mpdu->fcf.MAC_fcf_PANid_Compression = NO;
	mpdu->fcf.MAC_fcf_Frame_Pending = NO;
	mpdu->fcf.MAC_fcf_Ack_Request = NO;
	mpdu->fcf.MAC_fcf_Sec_enabled = NO;

//Setup for destination
	mpdu->destination.mode = MAC_SHORT_ADDRESS;
	mpdu->destination.PANid = 0xffff;
	mpdu->destination.shortAddr = 0xffff;

	MAC_createFrame(mpdu, fr);
	
	SET_FRAME_DATA(fr->payload, MAC_BEACON_REQUEST, 1);
	
	frame_sendWithFree(fr);
	free(mpdu);
}	

void MAC_commandCoordRealign(addr_t *destAddr, security_t *sec)
{
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	
	mac_pib_t *mpib = get_macPIB();
	
    mpdu->source = mpib->macLongAddress;
	
//Setup for the FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_COMMAND;
    mpdu->fcf.MAC_fcf_DstAddr_Mode = destAddr->mode;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = mpdu->source.mode;
	mpdu->fcf.MAC_fcf_PANid_Compression = NO;
	mpdu->fcf.MAC_fcf_Frame_Pending = NO;
	
	if(destAddr->mode == MAC_LONG_ADDRESS)
	    mpdu->fcf.MAC_fcf_Ack_Request = YES;
	else
	    mpdu->fcf.MAC_fcf_Ack_Request = NO;
	
	mpdu->fcf.MAC_fcf_Sec_enabled = NO;
	mpdu->fcf.MAC_fcf_Frame_Ver = 0x01;
	
	mpdu->destination = *destAddr;
	
	MAC_createFrame(mpdu, fr);
	
	SET_FRAME_DATA(fr->payload, MAC_COORD_REALIGN, 1);
	
	SET_FRAME_DATA(fr->payload, destAddr->PANid, 2);
	
	SET_FRAME_DATA(fr->payload, destAddr->shortAddr, 2);
	
	SET_FRAME_DATA(fr->payload, (get_currentChannel()), 1);
	
	SET_FRAME_DATA(fr->payload, (get_short_ADDR()), 2);
	
	frame_sendWithFree(fr);
	free(mpdu);
	
	
}

void MAC_commandHandler(frame_t *fr, mpdu_t *mpdu)
{
	/*
 * 		This section will have the proper location for each mac commands that it receives
 */
	
		uint8_t command = GET_FRAME_DATA(fr->Rx_fr, 1);

		switch(command) 
		{
		case(MAC_ASSOC_REQUEST):
            MAC_mlme_assocReqHandler(mpdu, fr);
		break;
		case(MAC_ASSOC_RESPONCE):
			MAC_mlme_assocRespHandler(mpdu, fr);
		break;
				
		case MAC_DISASSOC_NOTIFY:
			MAC_mlme_disAssocHandler(mpdu, fr);
		break;
		
		case MAC_DATA_REQUEST:
			alarm("Rx a Data command");
		break;
		
		case MAC_PAN_CONFLICT_NOTIFY:
			alarm("Rx a Pan Conflix command");
		break; 
		case MAC_ORPHAN_NOTIFY:
			alarm ("Rx a Orphan Command");
		break;
		case MAC_BEACON_REQUEST:
			alarm("Rx a Beacon Req");
			MAC_mlme_beaconInd(mpdu, fr);
		break;
		case MAC_COORD_REALIGN:
		
		break;
		case MAC_GTS_REQUEST:
		
		break;
		default:
		alarm_new(7, "Unknown MAC Command Frame Rx");
		break;
//	TODO:	I need to add the other types of command frames that i could receive....
		}//end switch command
}