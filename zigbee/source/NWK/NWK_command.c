/*
 * NWK_command.c
 *
 *  Created on: Oct 15, 2010
 *      Author: mpoppe
 */
#include <frame.h>

#include <NWK/NWK_prototypes.h>
#include "nwk/NWK_nlde.h"
#include "NWK/NWK_command.h"

#include "MAC/mac_prototypes.h"
#include "mac/MAC_mcps.h"

void NWK_cmd_routeReq(short_addr_t destAddr, short_addr_t grpID)
{
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	
	nwk_reqCmdOptionField_t options;
	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = YES;

	npdu->destination.mode = SHORT_ADDRESS;
	npdu->destination.shortAddr = nwk_broadcast_Rx_when_idle;
	npdu->destination.PANid	= mpib->macPANid;
	
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = 0x0000;// mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = no;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = 0xffff;
	mpdu->destination.PANid = mpib->macPANid;
/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/

	options.rsrv2 = 0x00;
	options.rsvr1 = 0x00;
	options.manyToOne = 1;//TODO: THis should be done it a system Config File somewhere
	options.dstIEEEAddr = 0;//TODO: this has more to it.  It should always be added if know
	
	if(grpID)
	{ 
		options.multicast = 1;
	} 
	else
	{
		options.multicast = 0;
	}		
	
	
	//Setup Payload

// Add the Options to the payload	
	//SET_FRAME_DATA(fr->payload, (*((uint8_t *)&options)), 1);
SET_FRAME_DATA(fr->payload, NWK_ROUTE_REQUEST, 1);
SET_FRAME_DATA(fr->payload, 0x10, 1);
// ADD route reuest Identifier
	//SET_FRAME_DATA(fr->payload, (*((uint8_t *)&options)), 1);
	//SET_FRAME_DATA(fr->payload, NWK_ROUTE_REQUEST, 1);
	SET_FRAME_DATA(fr->payload, NWK_STARTING_ROUTE_COST, 1);
//SET_FRAME_DATA(fr->payload, (*((uint8_t *)&options)), 1);
//Add Destination Address to the Payload
	SET_FRAME_DATA(fr->payload, destAddr, 2);
//Add Path Cost
	SET_FRAME_DATA(fr->payload, NWK_STARTING_ROUTE_COST, 1);
	
	if(options.dstIEEEAddr)
	{
		
	}
	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
	
}//

void NWK_cmd_routeReply(short_addr_t orginator, uint8_t path_cost)
{
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	
	nwk_respondCmdOptionField_t options;
	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = NO;

	npdu->destination.mode = SHORT_ADDRESS;
	npdu->destination.shortAddr = nwk_broadcast_Rx_when_idle;
	npdu->destination.PANid	= mpib->macPANid;
	
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = 0x0000;// mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = no;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = 0xffff;
	mpdu->destination.PANid = mpib->macPANid;
	
/***************************************
*
*	Setup Payload
*
****************************************/
// setup Command Options field
	options.rsrv1= 0x00;
	options.rsvr2 = 0x00;
	options.multicast = 1;//TODO: THis should be done it a system Config File somewhere
	options.originatorIEEE = 0;//TODO: this has more to it.  It should always be added if know
	options.responderIEEE = 0;
	
	

	SET_FRAME_DATA(fr->payload, NWK_ROUTE_REPLY, 1);
// Add the Options to the payload
	SET_FRAME_DATA(fr->payload, (*((uint8_t *)&options)), 1);
	
	SET_FRAME_DATA(fr->payload, 0x00, 1);
	
	SET_FRAME_DATA(fr->payload, orginator, 2);
	
	SET_FRAME_DATA(fr->payload, mpib->macShortAddress.shortAddr, 2);
	
	SET_FRAME_DATA(fr->payload, path_cost, 1);
	

	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
	
}//


void NWK_cmd_NetStatus(nwk_statusCode_t statusCode, short_addr_t addr)
{
	
/***************************************
*
*	TODO: I need to make the dest addr the same as the source addr
*			if this is done with a routing error
*
*			Also I need to fix the dest IEEE if this is not a broadcast
*
****************************************/
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	
	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = YES;

	npdu->destination.mode = SHORT_ADDRESS;
	npdu->destination.shortAddr = nwk_broadcast_all_Pan_devices;
	npdu->destination.PANid	= mpib->macPANid;
	
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = no;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = 0xffff;
	mpdu->destination.PANid = mpib->macPANid;
	
/***************************************
*
*	Setup Payload
*
****************************************/


	SET_FRAME_DATA(fr->payload, NWK_NETWORK_STATUS, 1);
// Add the Options to the payload
	SET_FRAME_DATA(fr->payload, statusCode, 1);
	
	SET_FRAME_DATA(fr->payload, addr, 2);
	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
}

void NWK_cmd_leave(nwk_leaveCmdOptionField_t leave)
{
	
/***************************************
*
*	TODO: I need to make the dest addr the same as the source addr
*			if this is done with a routing error
*
*			Also I need to fix the dest IEEE if this is not a broadcast
*
****************************************/
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	
	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = YES;

	npdu->destination.mode = SHORT_ADDRESS;
	npdu->destination.shortAddr = nwk_broadcast_all_Pan_devices;
	npdu->destination.PANid	= mpib->macPANid;
	
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = no;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = 0xffff;
	mpdu->destination.PANid = mpib->macPANid;
	
/***************************************
*
*	Setup Payload
*
****************************************/


	SET_FRAME_DATA(fr->payload, NWK_LEAVE, 1);
// Add the Options to the payload
	SET_FRAME_DATA(fr->payload, *((uint8_t *)&leave), 1);
	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
}



void NWK_cmd_routeRec(short_addr_t addr)
{
	
/***************************************
*
*	TODO: I need to make the dest addr the same as the source addr
*			if this is done with a routing error
*
*			Also I need to fix the dest IEEE if this is not a broadcast
*
****************************************/
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	
	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = YES;

	npdu->destination.mode = SHORT_ADDRESS;
	npdu->destination.shortAddr = nwk_broadcast_all_Pan_devices;
	npdu->destination.PANid	= mpib->macPANid;
	
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = YES;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = addr;
	mpdu->destination.PANid = mpib->macPANid;
	
/***************************************
*
*	Setup Payload
*
****************************************/


	SET_FRAME_DATA(fr->payload, NWK_ROUTE_RECORD, 1);
// Add the Options to the payload
	SET_FRAME_DATA(fr->payload, 0x00, 1);
	
	SET_FRAME_DATA(fr->payload, 0x00,1);
	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
}

void NWK_cmd_rejoinReq(void)
{
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	nwk_nib_t *nnib = NWK_getNIB();
	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = YES;

	npdu->destination.mode = SHORT_ADDRESS;
	npdu->destination.shortAddr = nwk_broadcast_all_Pan_devices;
	npdu->destination.PANid	= mpib->macPANid;
	
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = no;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = 0xffff;
	mpdu->destination.PANid = mpib->macPANid;
	
/***************************************
*
*	Setup Payload
*
****************************************/


	SET_FRAME_DATA(fr->payload, NWK_REJOIN_REQUEST, 1);
// Add the Options to the payload
	SET_FRAME_DATA(fr->payload, nnib->nwkCapabilityInfo, 1);
	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
}



void NWK_cmd_rejoinResp(short_addr_t addr, uint8_t status)
{
	
/***************************************
*
*	TODO: I need to make the dest addr the same as the source addr
*			if this is done with a routing error
*
*			Also I need to fix the dest IEEE if this is not a broadcast
*
****************************************/
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	
	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = YES;

	
	npdu->destination = mpib->macCoordShortAddress;
	
	
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = YES;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = addr;
	mpdu->destination.PANid = mpib->macPANid;
	
/***************************************
*
*	Setup Payload
*
****************************************/


	SET_FRAME_DATA(fr->payload, NWK_REJOIN_RESPONSE, 1);
// Add the Options to the payload
	SET_FRAME_DATA(fr->payload, addr, 2);
	
	SET_FRAME_DATA(fr->payload, status, 1);
	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
}

void NWK_cmd_linkStatus(void)
{
	
/***************************************
*
*	TODO: I need to make the dest addr the same as the source addr
*			if this is done with a routing error
*
*			Also I need to fix the dest IEEE if this is not a broadcast
*
****************************************/
	nwk_linkStatusCmd_t link;
	
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	
	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = NO;

	npdu->destination.mode = SHORT_ADDRESS;
	npdu->destination.shortAddr = nwk_broadcast_router_and_Cord;
	
	npdu->source = mpib->macShortAddress;
	
	npdu->radius = 1;

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = NO;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = 0xffff;
	mpdu->destination.PANid = mpib->macPANid;
	
/***************************************
*
*	Setup Payload
*
****************************************/

	link.count = 1;
	link.first = 1;
	link.last = 0;
	link.reserved = 0;
	
	SET_FRAME_DATA(fr->payload, NWK_LINK_STATUS, 1);

	SET_FRAME_DATA(fr->payload, *((uint8_t *)&link), 1);

// Add the Options to the payload
	SET_FRAME_DATA(fr->payload, 0x2342, 2); //TODO I need to get info from the neighbor table
	
	SET_FRAME_DATA(fr->payload, 0x00, 1);
//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
}
void NWK_cmd_netReport(void)
{
	
/***************************************
*
*	TODO: I need to make the dest addr the same as the source addr
*			if this is done with a routing error
*
*			Also I need to fix the dest IEEE if this is not a broadcast
*
****************************************/
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
	
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	nwk_nib_t *nnib = NWK_getNIB();
	
	nwk_reportCmdOpt_t cmd;	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = YES;

	
	npdu->destination = nnib->nwkManagerAddr;
		
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = YES;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination= nnib->nwkManagerAddr;
		
/***************************************
*
*	Setup Payload
*
****************************************/


	SET_FRAME_DATA(fr->payload, NWK_NETWORK_REPORT, 1);
// Add the Options to the payload
	SET_FRAME_DATA(fr->payload,*((uint8_t *)&cmd), 1);
	
	SET_FRAME_DATA(fr->payload, nnib->nwkExtendedPANid, 8);
	
	//SET_FRAME_DATA(fr->payload, status, 1);
	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
}

void NWK_cmd_netUpdate(void)
{
	
/***************************************
*
*	TODO: I need to make the dest addr the same as the source addr
*			if this is done with a routing error
*
*			Also I need to fix the dest IEEE if this is not a broadcast
*
****************************************/
	nwk_linkStatusCmd_t link;
	
	frame_t *fr = frame_new();
	fr->payload = frame_hdr(payload);
	fr->payload->ptr = fr->payload->pl;
		
	npdu_t *npdu =(npdu_t *)malloc(sizeof(npdu_t));
	mpdu_t *mpdu = (mpdu_t *)malloc(sizeof(mpdu_t));
	
	mac_pib_t *mpib = get_macPIB();
	nwk_nib_t *nnib = NWK_getNIB();
	
	nwk_reportCmdOpt_t cmd;	
/***************************************
*
*	Setup to produce NWK hdr
*
****************************************/
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_discover_rt = SUPPRESS_DISCOVER;
	npdu->fcf.NWK_frame_type = NWK_COMMAND;
	npdu->fcf.NWK_multicast = NO;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_security = no;
	npdu->fcf.NWK_source_rt = no;
	npdu->fcf.NWK_source_IEEE = YES;

	
	npdu->destination = mpib->macCoordShortAddress;
	
	
	npdu->source.mode = LONG_ADDRESS;
	npdu->source = mpib->macLongAddress;
	npdu->source.shortAddr = mpib->macShortAddress.shortAddr;
	

/***************************************
*
*	Setup to produce MAC hdr
*
****************************************/
	//setup MAC FCF
	mpdu->fcf.MAC_fcf_Frame_Type = MAC_DATA;
	mpdu->fcf.MAC_fcf_Sec_enabled = no;
	mpdu->fcf.MAC_fcf_Frame_Pending = no;
	mpdu->fcf.MAC_fcf_Ack_Request = YES;
	mpdu->fcf.MAC_fcf_PANid_Compression = yes;
	mpdu->fcf.MAC_fcf_DstAddr_Mode = SHORT_ADDRESS;
	mpdu->fcf.MAC_fcf_Frame_Ver = MAC_COMPATIBLE_WITH_802_15_4_2003;
	mpdu->fcf.MAC_fcf_SrcAddr_Mode = SHORT_ADDRESS;

	//Source Addr
	mpdu->source = mpib->macShortAddress;
	
	//Destination Addr - broadcast
	mpdu->destination.shortAddr = 0xffff;
	mpdu->destination.PANid = mpib->macPANid;
	
/***************************************
*
*	Setup Payload
*
****************************************/

	SET_FRAME_DATA(fr->payload, NWK_NETWORK_UPDATE, 1);
// Add the Options to the payload
	SET_FRAME_DATA(fr->payload,*((uint8_t *)&cmd), 1);
	
	SET_FRAME_DATA(fr->payload, nnib->nwkExtendedPANid, 8);
	
	//SET_FRAME_DATA(fr->payload, status, 1);
// Add the Options to the payload

	
	//Create the NWK frame header
	NWK_createFrame(npdu, fr);
	//send off to the MAC data req
	MAC_mcps_dataReq(mpdu, fr);
	 
	free(npdu);
	free(mpdu);
}

