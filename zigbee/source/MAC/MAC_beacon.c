/*
 * MAC_beacon.c
 *
 *  Created on: Sep 26, 2010
 *      Author: mpoppe
 */

#include <frame.h>
#include "alarms_task.h"

#include "MAC/mac.h"
#include "MAC/MAC_beacon.h"
#include "MAC/MAC_command.h"
#include "MAC/MAC_mlme.h"
#include "MAC/mac_prototypes.h"

void NWK_beacon_handler(mac_pan_descriptor_t *desc, mpdu_t *mpdu, frame_t *fr);

LIST(panDescriptor);


mac_beaconHandler_t handle;

void MAC_beacon_setCB(void *cb)
{
	handle = (mac_beaconHandler_t *)cb;
}

void MAC_panDescriptor_init(void)
{
	list_init(panDescriptor);
}

list_t * MAC_panDescriptor_getList(void)
{
	return panDescriptor;
}

void MAC_beaconHandler(mpdu_t *mpdu, frame_t *fr)
{
/* 	TODO:	For now I am going to send the Beacon data to the PAN descriptor table I am not sure what I am going to do with that data yet
 * 			I know that the beacon request can send more data in the payload in the future the beacon indication in the mlme will send that on up
 */
    
    /*TODO: I need to setup a data request if I get a beacon with this address as the dest. addr */
   
   
   // TODO: I need to add a Mac status with scan mode so I capture all the desc. tables only durring scans
	uint8_t len;
	phy_pib_t *ppib = get_phyPIB();
	mac_pib_t *mpib = get_macPIB();
	
	mac_superframe_t sf;
	mac_gtsSpec_t gtsSpec;
	
	sf = *((mac_superframe_t *)fr->Rx_fr->ptr);
	fr->Rx_fr->ptr += sizeof(mac_superframe_t);
	
	gtsSpec = *((mac_gtsSpec_t *)fr->Rx_fr->ptr);
	fr->Rx_fr->ptr += sizeof(mac_gtsSpec_t);


	
	mac_pan_descriptor_t *desc = (mac_pan_descriptor_t *)malloc(sizeof(mac_pan_descriptor_t));
	desc->Coord = mpdu->source;

	desc->LogicalChannel = ppib->phyCurrentChannel;
	desc->ChannelPage = ppib->phyCurrentPage;

	desc->GTSPermit = false; //TODO: I need to fix this I am not sure on it.
	desc->LinkQuality = fr->LQI;
	desc->Timestamp = fr->timestamp;
	desc->SecurityFailure = 0x00;//TODO: Proper data needs to be inserted.
	desc->SecurityLevel = MAC_sec_none;// TODO: Proper data needs to be inserted.
	desc->KeyIdMode = 0x00;// TODO: Proper data needs to be inserted.
	desc->KeySource = 0x00;// TODO: Proper data needs to be inserted.
	desc->KeyIndex = 0x00;// TODO: Proper data needs to be inserted.
	

	if(mpib->macRuntimeStatus == MAC_SCAN_IN_PROGRESS)
	{
		list_add(panDescriptor, desc);
		alarm_new(9, "Count of Descriptor table is %i", list_length(panDescriptor));
	}	
		
	MAC_mlme_beaconInd(mpdu, fr);
	
	NWK_beacon_handler(desc, mpdu, fr);

	if(mpib->macRuntimeStatus != MAC_SCAN_IN_PROGRESS)
	{
		free(desc);
	}
//	TODO: 	I want to add a que for the different coordinator PAN_IDs that will allow me to select a different PANid
//			Or just to see what else is out there.

}//end incoming_beacon_handler

void MAC_beacon(void)
{
	uint8_t *ptr;
	uint8_t tempSuperframe;
	mac_superframe_t superframe;
	
	phy_pib_t *ppib = get_phyPIB();
	mac_pib_t *mpib = get_macPIB();

	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	frame_t *fr = frame_new();

	fr->payload = frame_hdr(payload);


	mpdu->fcf.MAC_fcf_Frame_Type = MAC_BEACON;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = NO_ADDRESS;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_PANid_Compression = NO;
	mpdu->fcf.MAC_fcf_Frame_Pending = NO;
	mpdu->fcf.MAC_fcf_Ack_Request = NO;
	mpdu->fcf.MAC_fcf_Sec_enabled = NO;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;

	mpdu->source = mpib->macShortAddress;


//	Add superframe

	//GTS spec
	SET_FRAME_DATA(fr->payload, 0x0000, 2);

	//SuperFrame spec
	superframe.assocPermit = ((mpib->macAssociationPermit) ? 1 : 0);
	superframe.panCoord = ((mpib->macAssociatedPANCoord) ? 1 : 0);	
	superframe.battLifeExt = ((mpib->macBattLifeExt) ? 1 : 0);
	superframe.beaconOrder = 0x0f;
	superframe.superframeOrder = 0x0f;

	SET_FRAME_DATA(fr->payload, *((uint16_t *)&superframe), 2);

//	Add NWK Beacon Data

	if(	ptr = mpib->macBeaconPayload)
	{

		for(uint8_t x=0; x < (mpib->macBeaconPayloadLength); x++)
		{
			*fr->payload->ptr++ = *ptr++;
		
		}//end for
		fr->payload->length += 16;
	}	
	MAC_createFrame(mpdu, fr);

    frame_sendWithFree(fr);
	
	free(mpdu);
}

void MAC_beaconReq_cb(mac_status_t status)
{
	switch(status)
	{
		case(MAC_SUCCESS):

			break;

		case(MAC_NO_ACK):
			break;

		case(MAC_TRANSACTION_EXPIRED):
			break;
	}
	MAC_beaconConfirm(status);
}

void MAC_beaconConfirm(mac_status_t status)
{
	(handle)(status);
}
