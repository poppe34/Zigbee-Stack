/*
 * NWK_beacon.c
 *
 *  Created on: Oct 26, 2010
 *      Author: mpoppe
 */
#include <frame.h>
#include <NWK/NWK_prototypes.h>

#include "list.h"

uint8_t filterExtPANidActive;
uint64_t filterPANid;



void NWK_beacon_handler(mac_pan_descriptor_t *desc, mpdu_t *mpdu, frame_t *fr){
	uint8_t x;
	
	phy_pib_t *ppib = get_phyPIB();

	nwk_neigh_t *tbl = (nwk_neigh_t *)malloc(sizeof(nwk_neigh_t));
	nwk_discript_t *disc = (nwk_discript_t *)malloc(sizeof(nwk_discript_t));
	nwk_beacon_t beacon;

//1st byte Protocol ID
	beacon.protocolID = *fr->Rx_fr->ptr++;

//2nd byte Stack profile and protocol version
	beacon.stackProf = (*fr->Rx_fr->ptr & 0x0f);
	beacon.protocolVer = ((*fr->Rx_fr->ptr >> 4) & 0x0f);
	fr->Rx_fr->ptr++;

//3rd byte router capacity avail, depth, and end device capacity avail
	beacon.routerCap = ((*fr->Rx_fr->ptr >> 2) & 0x01);
	beacon.devDepth = ((*fr->Rx_fr->ptr >> 3) & 0x0f);
	beacon.endDevCap = ((*fr->Rx_fr->ptr >> 7) & 0x01);
	fr->Rx_fr->ptr++;

//4th - 11th byte is the extended PANid
	beacon.extendedPANid = GET_FRAME_DATA(fr->Rx_fr, 8);

//12-15th byte is the TxOffset in zigbee this is always 0xffffff well should be
	beacon.txOffset = GET_FRAME_DATA(fr->Rx_fr, 8);

//16th byte is the NWK update ID
	beacon.nwkUpdateId = GET_FRAME_DATA(fr->Rx_fr, 1);


//****************************************************************************
//
//		Build Neighbor table
//
//****************************************************************************
	tbl->extendPANid = beacon.extendedPANid;
	if(!filterExtPANidActive || (filterExtPANidActive && (tbl->extendPANid == filterPANid))){
		tbl->LQI = fr->LQI;
//		tbl.RxOnWhenIdle = desc.
		tbl->age = 0;
//		tbl.beaconOffset; this optional.
		tbl->beaconTime = fr->timestamp;
//		tbl->cost; if nwkSymLink is true then this is neccessary but I am not there yet.
//		tbl->failure;

		if(desc->Coord.mode == SHORT_ADDRESS){
			tbl->shortAddr = desc->Coord;
		}
		else{
			tbl->extendAddr = desc->Coord;
		}

		tbl->potentialParent = YES;
		tbl->logicalChannel = desc->LogicalChannel;
		tbl->depth = beacon.devDepth;
		tbl->beaconOrder = 0; //desc->SuperframeSpec.beaconOrder;
		tbl->permitJoining = 0; //beacon. desc->SuperframeSpec.assocPermit;
		tbl->potentialParent = 0x01;
		tbl->type = ((desc->SuperframeSpec.panCoord == 1)? 0x00: 0x01);

		list_add((NWK_getNeighTable()), tbl);
	}

//****************************************************************************
//
//		Build Network discover table
//
//****************************************************************************
// TODO:	May need to limit when i build the network discover tbl
	disc->beaconOrder = desc->SuperframeSpec.beaconOrder;//TODO: I need to fix this the data should come from the superframe
	disc->endDeviceCapacity = beacon.endDevCap;
	disc->extendPANid = beacon.extendedPANid;
	disc->logicalChannel = desc->LogicalChannel;
	disc->permitJoining = desc->SuperframeSpec.assocPermit;//TODO: I need to fix this the data should come from the superframe
	disc->routerCapacity = beacon.routerCap;
	disc->stackProfile = beacon.stackProf;
	disc->superframeOrder = desc->SuperframeSpec.superframeOrder;//TODO: I need to fix this the data should come from the superframe
	disc->zigbeeVersion = beacon.protocolVer;

	nwk_addNetworkDiscription(disc);
}

void NWK_beaconFilterControl(uint64_t PANid){
	if(PANid != 0xffffffffffffffff){
		filterExtPANidActive = false;
	}
	else{
		filterExtPANidActive = true;
		filterPANid = PANid;
	}

}

void NWK_buildBeaconPayload(void){

	payload_t *nwkBeacon = NWK_getBeaconPayload();
	mac_pib_t *mpib = get_macPIB();
	nwk_nib_t *nnib = NWK_getNIB();
	
	nwkBeacon->ptr = &nwkBeacon->pl;
	nwkBeacon->length = 16;

	//Byte - 1: Byte Protocol ID
	*nwkBeacon->ptr++ = 0x00; //currently always 0x00 for zigbee protocols may change in the future
	
	//Byte - 2: Stack Profile and NWKcProtocolVersion
	*nwkBeacon->ptr = (nnib->nwkStackProfile<<4);
	*nwkBeacon->ptr++ |= nwkcProtocolVersion;

	//Byte - 3: Router Capacity, device depth, end device capacity
	*nwkBeacon->ptr = (0x00<<2);//TODO: currently I am telling things I am not at Router Capacity but I will need to update this once I have a variable
	*nwkBeacon->ptr |= (0x01<<3);//TODO: currently I am telling thins I am at depth 1 but this needs to updated once I have a variable
	*nwkBeacon->ptr++ |= (0x00<<7);//TODO: currently I am telling things I am not at end device capacity but I will need to update this once I have a variable

	//Byte - 4 - 12: NWK extended PANid
	
	SET_FRAME_DATA(nwkBeacon, nnib->nwkExtendedPANid, 8);
	
	//Byte 13 - 15: TXOffset
	*nwkBeacon->ptr++ = 0xff; //TODO: TX offset... I might make a constant for this since it is always 0xffffff for a beaconless network
	*nwkBeacon->ptr++ = 0xff;
	*nwkBeacon->ptr++= 0xff;

	//Byte - 16: NWKUpdateId
	*nwkBeacon->ptr = nnib->nwkUpdateId;
	
	mpib->macBeaconPayloadLength = 16;//nwkBeacon->length;
	mpib->macBeaconPayload = nwkBeacon->pl;
}