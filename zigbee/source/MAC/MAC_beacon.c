/*
 * MAC_beacon.c
 *
 *  Created on: Sep 26, 2010
 *      Author: mpoppe
 */

#include <frame.h>
#include "MAC/mac.h"
#include "MAC/mac_prototypes.h"
#include "NWK/NWK_prototypes.h"
#include "MAC/MAC_command.h"
#include "MAC/MAC_mlme.h"

typedef void(*mac_beaconHandler_t)(mac_status_t status);
mac_beaconHandler_t handle;

void MAC_beaconReq(void *cb)
{
	handle = (mac_beaconHandler_t *)cb;
    
	
    
}

void MAC_beaconHandler(mpdu_t *mpdu, frame_t *fr)
{
/* 	TODO:	For now I am going to send the Beacon data to the PAN descriptor table I am not sure what I am going to do with that data yet
 * 			I know that the beacon request can send more data in the payload in the future the beacon indication in the mlme will send that on up
 */
    
    /*TODO: I need to setup a data request if I get a beacon with this address as the dest. addr */
    /*
	uint8_t len;
	phy_pib_t *ppib = get_phyPIB();
	uint16_t tempsuperframe, tempgtsSpec;

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
	//add_to_PAN_Table(desc);

	tempgtsSpec = (uint16_t)*fr->ptr++;
	tempgtsSpec |= ((uint16_t)(*fr->ptr >> 8));
	fr->ptr++;

	tempsuperframe = (uint16_t)*fr->ptr++;
	tempsuperframe |= ((uint16_t)(*fr->ptr >> 8));
	fr->ptr++;

	desc->SuperframeSpec.assocPermit = ((uint8_t)(tempsuperframe>>MAC_SUPERFRAME_ASSOC_PERMIT_SHIFT & 0x01));
	desc->SuperframeSpec.battLifeExt =  ((uint8_t)(tempsuperframe>>MAC_SUPERFRAME_BATT_EX_SHIFT & 0x01));
	desc->SuperframeSpec.beaconOrder = ((uint8_t)(tempsuperframe>> MAC_SUPERFRAME_BEACON_ORDER_SHIFT & 0x0f));
	desc->SuperframeSpec.capSlot = ((uint8_t)(tempsuperframe>>MAC_SUPERFRAME_CAP_SLOT_SHIFT & 0x0f));
	desc->SuperframeSpec.panCoord = ((uint8_t)(tempsuperframe>>MAC_SUPERFRAME_PAN_COORD_SHIFT & 0x01));
	desc->SuperframeSpec.superframeOrder = ((uint8_t)(tempsuperframe>>MAC_SUPERFRAME_FRAME_ORDER_SHIFT & 0x0f));

	MAC_mlme_beaconInd(mpdu, fr);
	
	NWK_beaconInd(desc, mpdu, fr);


//	TODO: 	I want to add a que for the different coordinator PAN_IDs that will allow me to select a different PANid
//			Or just to see what else is out there.
*/
}//end incoming_beacon_handler

void MAC_beacon(void)
{
	/*
	uint8_t tempSuperframe;

	phy_pib_t *ppib = get_phyPIB();
	mac_pib_t *mpib = get_macPIB();

	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	frame_t *fr = (frame_t *)malloc(sizeof(frame_t));


	mpdu->fcf.MAC_fcf_Frame_Type = MAC_BEACON;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = NO_ADDRESS;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_PANid_Compression = NO;
	mpdu->fcf.MAC_fcf_Frame_Pending = NO;
	mpdu->fcf.MAC_fcf_Ack_Request = NO;
	mpdu->fcf.MAC_fcf_Sec_enabled = NO;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;

	mpdu->source = mpib->macShortAddress;

//	Add room for CRC
	*fr->ptr++ = 0x00;
	*fr->ptr++ = 0x00;

	fr->dataLength = 2;

//	Add NWK Beacon Data

	frame_data_t nwkBeacon;
	nwkBeacon.ptr = mpib->macBeaconPayload;
	nwkBeacon.length = mpib->macBeaconPayloadLength;

	for(uint8_t x=0; x<nwkBeacon.length; x++)
	{
		*fr->ptr++ = *nwkBeacon.ptr++;
		fr->dataLength++;
	}//end for

//	Add superframe

	//GTS spec
	*fr->ptr++ = 0x00;
	*fr->ptr++ = 0x00;

	fr->dataLength +=2;

	//SuperFrame spec
	tempSuperframe = ((mpib->macAssociationPermit) ? 0x80 : 0); //TODO: do a shift variable for the 0x80 like _bv(assoc_permit)
	tempSuperframe |= ((mpib->macAssociatedPANCoord) ? 0x40 :0);
	tempSuperframe |= ((mpib->macBattLifeExt) ? 0x10 : 0);
	tempSuperframe |= 0x0f;// final CAP slot is not enabled in zigbee

	*fr->ptr++ = tempSuperframe;

	tempSuperframe = 0xff; // Superframe Order and Beacon order are both 0xf since zigbee uses a beaconless network

	*fr->ptr++ = tempSuperframe;

	fr->dataLength += 2;

	MAC_createFrame(mpdu, fr);

    frame_sendWithFree(fr);
	free(mpdu);

	*/
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
