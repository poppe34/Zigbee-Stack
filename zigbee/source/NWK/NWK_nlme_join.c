/*
 * NWK_nlme_rejoin.c
 *
 *  Created on: Oct 27, 2010
 *      Author: mpoppe
 */
#include <frame.h>
#include <NWK/NWK_prototypes.h>

#include "MAC/mac_prototypes.h"
#include "MAC/MAC_mlme.h"
#include "MAC/MAC_mcps.h"

#include "NWK/NWK_command.h"
#include "NWK/NWK_nlme_join.h"

nwk_join_t *join;
typedef void (*nwk_joinHandler_t)(nwk_status_t status);
nwk_joinHandler_t joinHandler;

static Bool join_resp_waiting = NO;

void NWK_beaconFilterControl(uint64_t PANid);

uint64_t joinExtPANid;

void NWK_nlme_joinReq(nwk_join_t *jn){

	mlme_assoc_t *assoc = (mlme_assoc_t *)malloc(sizeof(mlme_assoc_t));
	nwk_neigh_t *neighbor;
	mac_scan_t *scan = (mac_scan_t *)malloc(sizeof(mac_scan_t));

	switch(jn->rejoinNetwork){
	case(JOINED_THRU_ASSOC):
	break;
	case(JOINED_DIRECTLY):
	break;
	case(JOINED_NWK_REJOIN):
	break;
	}//end switch
//TODO:	add the logic if the network is already joined to issue an indication saying INVALID_REQUEST
	free(assoc);
	free(scan);
}//end NWK_nlme_joinReq

void NWK_nlme_rejoinScan_cb(mac_scanResult_t *result){

	nwk_neigh_t *parent = NWK_getBestAddrForNetwork(joinExtPANid);
	nwk_nib_t *nnib = NWK_getNIB();
	npdu_t *npdu = (npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = no;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = yes;

	if(nnib->nwkNetworkAddress.shortAddr == 0xffff){
		if(nnib->nwkAddrAlloc == 0x02){
			 NWK_setShortAddr((uint16_t)rand());
		}
	}

	npdu->source = nnib->nwkNetworkAddress;

	npdu->destination = parent->shortAddr;
	npdu->destExtAddr = parent->extendAddr.extAddr;
	npdu->sequence_num = nnib->nwkSequenceNumber++;
//	TODO:	fix the delay time below I don't have aresponsewaittime declared
//	add_to_time_qsm(&NWK_nlme_rejoinUnsuccess_cb, null, aResponseWaitTime);

	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = yes;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Ver = 0x00;

	nwk_capInfo_t capInfo;
	capInfo.allocAddr = yes;//0x01 means that it will issue and addr
	capInfo.altPanCoord = no;
	capInfo.devType = 0x00;
	capInfo.powerSource = 0x01;//power is from mains
	capInfo.recWhenIdle = yes;
	capInfo.secEnabled = no;
	uint8_t *tempCapInfo = &capInfo;


//Add room for CRC
	SET_FRAME_DATA(fr->payload, 0x0000, 2);

//Add Capability info
	SET_FRAME_DATA(fr->payload, *tempCapInfo, 1);

	SET_FRAME_DATA(fr->payload, NWK_REJOIN_REQUEST, 1);

	NWK_createFrame(npdu, fr);

	MAC_mcps_dataReq(mpdu, fr);
	
	frame_sendWithFree(fr);
	
	free(npdu);
	free(mpdu);
}

void NWK_nlme_rejoinUnsuccess_cb(void){

}

void NWK_nlme_joinNetDiscov_cb(nwk_netDisc_t *netDisc){

	nwk_neigh_t *parent;


}

void NWK_nlme_joinInd(nwk_nlme_joinInd_t *join)
{
	nwk_neigh_t *newNeigh = NWK_nlme_addNeighbor();
	
	if(newNeigh)
	{
		newNeigh->
}

Bool MAC_mlme_joinResp_waiting(void)
{
    
}
void NWK_nlme_joinTx_cb(uint8_t num){

}
void NWK_nlme_joinMacAssoc_cb(mac_status_t status){
	(joinHandler)(status);
}

void NWK_nlme_joinConfirm(nwk_status_t status){
	(joinHandler)(status);
}
