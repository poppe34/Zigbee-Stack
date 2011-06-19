// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief
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
 * Copyright (c) 2008 ,
 *
 *
 *****************************************************************************/

/*================================= INCLUDES         =========================*/

#include "frame.h"

#include "nwk/NWK.h"
#include "NWK/NWK_prototypes.h"

/*================================= MACROS           =========================*/

/*================================= VARIABLES        =========================*/
nwk_nib_t nnib;
payload_t nwkBeacon;
/*================================= SOURCE CODE      =========================*/
void nwk_init(void){

	NWK_neighborTableInit();
	nnib.nwkSequenceNumber = 0x23;//TODO: make this a random number
	nnib.nwkPassiveAckTimeout = 0x0500;//TODO: I need to define this in stack profile
	nnib.nwkMaxBroadcastRetries = 0x03;
	nnib.nwkMaxChildren = 0x10;//TODO: I need to define this in the stack profile
	nnib.nwkMaxDepth = 0x05;//TODO: I need to define this in the stack profile
	nnib.nwkMaxRouters = 0x05;//TODO: I need to define this in the stack profile

	nnib.nwkNetworkBroadcastDeliveryTime = 0x0ff0;//TODO: I need to solve for this??????
	nnib.nwkReportConstantCost = 0x01;
	nnib.nwkRouteDiscoveryRetriesPermitted = nwkcDiscoveryRetryLimit;

	nnib.nwkSymLink = NO;
	nnib.nwkCapabilityInfo = 0x0d;//TODO: see table 3.51 in zigbee spec
	nnib.nwkAddrAlloc = 0x02;
	nnib.nwkUseTreeRouting = true;

	nnib.nwkManagerAddr.shortAddr = 0x0000;
	nnib.nwkManagerAddr.mode = SHORT_ADDRESS;

	nnib.nwkMaxSourceRoute = 0x0c;
	nnib.nwkUpdateId = 0x00;
	nnib.nwkTransactionPersistenceTime = 0x01f4;//TODO: link it to mactransactionPersistenceTime

	nnib.nwkNetworkAddress.shortAddr = 0xffff;
	nnib.nwkNetworkAddress.mode = SHORT_ADDRESS;

	nnib.nwkStackProfile = 0x02;//TODO: I am not sure where to get this

	nnib.nwkExtendedPANid = 0xfffffffffffffffe;

	nnib.nwkUseMulticast = yes;

	nnib.nwkIsConcentrator = NO;
	nnib.nwkConcentratorRadius = 0x0000;
	nnib.nwkConcentratorDiscoveryTime = 0x0000;

	/*	nnib.nwkSecurityLevel = 0;
	nnib.nwksecurityMaterialSet;
	nnib.nwkActivekeySeqNumber;
	nnib.nwkAllFresh;
	nnib.nwkSecureAllFrames; TODO: I need to add security functionality */

	nnib.nwkLinkStatusPeriod = 0x0f;
	nnib.nwkRouterAgeLimit = 0x03;
	nnib.nwkUniqueAddr = yes;

	nnib.nwkTimeStamp = true;
	nnib.nwkPANid = 0xffff;

	nnib.nwkTxTotal = 0x0000;

	NWK_buildBeaconPayload();
}

nwk_nib_t *NWK_getNIB(void){
	return &nnib;
}

void NWK_setExtendedPANid(uint64_t addr){
		nnib.nwkExtendedPANid = addr;
}

void NWK_setShortAddr(uint16_t addr){
	nnib.nwkNetworkAddress.shortAddr= addr;

}

void NWK_setPANid(uint16_t pan){
	nnib.nwkPANid = pan;

	nnib.nwkNetworkAddress.PANid = pan;

}
void NWK_buildBeaconPayload(void){

	nwkBeacon.ptr = &nwkBeacon.pl;
	nwkBeacon.length = 16;

	*nwkBeacon.ptr++ = 0x00; //currently always 0x00 for zigbee protocols may change in the future

	*nwkBeacon.ptr = (nnib.nwkStackProfile<<4);
	*nwkBeacon.ptr++ |= nwkcProtocolVersion;

	*nwkBeacon.ptr = (0x00<<2);//TODO: currently I am telling things I am not at Router Capacity but I will need to update this once I have a variable
	*nwkBeacon.ptr |= (0x01<<3);//TODO: currently I am telling thins I am at depth 1 but this needs to updated once I have a variable
	*nwkBeacon.ptr++ |= (0x00<<7);//TODO: currently I am telling things I am not at end device capacity but I will need to update this once I have a variable

	for(uint8_t x = 8; x>0;x--){
		*nwkBeacon.ptr++ = (uint8_t)(nnib.nwkExtendedPANid>>(8*x));
	}//end for

	*nwkBeacon.ptr++ = 0x00;
	*nwkBeacon.ptr++ = 0xff; //TODO: TX offset... I might make a constant for this since it is always 0xffffff for a beaconless network
	*nwkBeacon.ptr++ = 0xff;
	*nwkBeacon.ptr++= 0xff;


	*nwkBeacon.ptr = nnib.nwkUpdateId;
}
payload_t *NWK_getBeaconPayload(void){
	nwkBeacon.ptr = &nwkBeacon.pl[0];
	return(&nwkBeacon);

}
