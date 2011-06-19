/*
 * NWK_trx.c
 *
 *  Created on: Oct 14, 2010
 *      Author: mpoppe
 */
#include "compiler.h"

#include <frame.h>

#include "alarms_task.h"

#include <NWK/NWK_prototypes.h>
#include "NWK/NWK_nlde.h"

#include "MAC/MAC_prototypes.h"



uint8_t NWK_sequence_num = 0x11;
trx_cb_t trx_cb;
void NWK_trx_incomingFrame(frame_t *fr)
{
	npdu_t *npdu = NWK_trx_frameBreakdown(fr);
	
	
	switch(npdu->fcf.NWK_frame_type)
	{
		case NWK_DATA:
			NWK_nlde_dataInd(npdu, fr);
		break;
		
		case NWK_COMMAND:
		
		break;
		
		default:
		
		alarm("NWK: Unknown NWK Frame Type");
		
		break;
		
	}
}

npdu_t * NWK_trx_frameBreakdown(frame_t *fr)
{
	npdu_t *npdu = (npdu_t *)malloc(sizeof(npdu_t));
	
	//Get the Frame Control Field
	npdu->fcf = *((nwk_fcf_t *)fr->Rx_fr->ptr);
	fr->Rx_fr->ptr += 2;
		
	//Get the destination Address
	npdu->destination.shortAddr = GET_FRAME_DATA(fr->Rx_fr, 2);
	
	//Get the Source Addr
	npdu->source.shortAddr = GET_FRAME_DATA(fr->Rx_fr, 2);
	
	//Get the packet Radius
	npdu->radius = GET_FRAME_DATA(fr->Rx_fr, 1);
	
	//Get sequence num
	npdu->sequence_num = GET_FRAME_DATA(fr->Rx_fr, 1);
	
	//Check if there is a ext destination addr if so get it
	if(npdu->fcf.NWK_dest_IEEE)
	{
		npdu->destination.extAddr = GET_FRAME_DATA(fr->Rx_fr, 8);
	}
	//Check if there is a ext source addr if so get it
	if(npdu->fcf.NWK_source_IEEE)
	{
		npdu->source.extAddr = GET_FRAME_DATA(fr->Rx_fr, 8);
	}
	
	//Check if multicast was used if so get it
	
	if(npdu->fcf.NWK_multicast)
	{
		npdu->multicast_control = *((nwk_multicastControl_t *)fr->Rx_fr->ptr);
		fr->Rx_fr->ptr++;
	}
	
	//check if there is a source route if there is set the pointer to the front of the
	//source route.
	
	if(npdu->fcf.NWK_source_rt == 1)
	{
		npdu->src_route.relay_cnt = GET_FRAME_DATA(fr->Rx_fr, 1);
		npdu->src_route.relay_index = GET_FRAME_DATA(fr->Rx_fr,1);
		
		for(uint8_t x = 0; x < npdu->src_route.relay_cnt; x++)
		{
			npdu->src_route.relayList[x] = GET_FRAME_DATA(fr->Rx_fr, 2);
		}
	}
	
}

void NWK_trx_sourceRouteBreakdown(frame_t *fr)
{
	
}
nwk_status_t NWK_nlde_data(frame_t *fr){

	//TODO: need to setup the status
	nwk_status_t status = NWK_SUCCESS;
	npdu_t *npdu = (npdu_t *)malloc(sizeof(npdu_t));

	npdu->fcf.NWK_frame_type = NWK_data;
	npdu->fcf.NWK_protocol_ver = nwkcProtocolVersion;
	npdu->fcf.NWK_discover_rt = no;
	npdu->fcf.NWK_multicast = 0x01;
	npdu->fcf.NWK_security = no;
	//npdu->src_route = zig->nlde.DiscoverRoute; //TODO add logic to add route discovery
	npdu->fcf.NWK_dest_IEEE = no;
	npdu->fcf.NWK_source_IEEE = no;

	//npdu->multicast_control.multicastMode = MMF_mem;

	//npdu->dest = zig->nlde.dstAddr.s_addr;
	//npdu->srcAddr = SHORT_ADDR;//TODO this needs to be changed to the macShortAddress from MAC PIB
	npdu->radius = 0x06;//TODO: if the radius is not given a default value of 2x nwkMaxDepth needs to be given(using temp value)
	npdu->sequence_num = (get_NWK_Sequence_num());
	if(npdu->fcf.NWK_dest_IEEE){
		//TODO add IEEE address and compare it from the nwkAddressMap and neighbor table
	}
	if(npdu->fcf.NWK_source_IEEE){
		//TODO add this field initially I will never need it
	}

	if(!(npdu->fcf.NWK_multicast = 0x01)) {
		/*TODO add code here for multicast frame not ready yet making sure everything
		else works first */
	}


	NWK_createFrame(npdu, fr);
	free(npdu);
	//MAC_mcps_data(zig);

	return status;
}

void NWK_createFrame(npdu_t *npdu, frame_t *fr){


	mac_pib_t *mpib = get_macPIB();
	nwk_nib_t *nnib = NWK_getNIB();

	fr->nwk = frame_hdr(nwk_hdr);
	
	npdu->source = nnib->nwkNetworkAddress;

// Add NWK fcf
	SET_FRAME_DATA(fr->nwk, *((uint16_t *)&npdu->fcf), 2);
	
// Add Dest Addr
	SET_FRAME_DATA(fr->nwk, npdu->destination.shortAddr, 2);	
	
// Add Source Addr
	SET_FRAME_DATA(fr->nwk, 0x0000, 2);//npdu->source.shortAddr, 2);
	
// Add Radius
	SET_FRAME_DATA(fr->nwk, npdu->radius, 1);//TODO: this value should be temp I need a variable in its place

//Add sequence Num
	SET_FRAME_DATA(fr->nwk, get_NWK_Sequence_num(), 1);

//Add Desination IEEE addr if needed
	if(npdu->fcf.NWK_dest_IEEE){
		SET_FRAME_DATA(fr->nwk, npdu->destExtAddr, 8);
	}	
	
//Add Source IEEE addr if needed
	if(npdu->fcf.NWK_source_IEEE){
		SET_FRAME_DATA(fr->nwk, mpib->macLongAddress.extAddr, 8);
	}

//Add Multicast control frame if needed
	if(npdu->fcf.NWK_multicast){
		uint8_t *temp_mc = &npdu->multicast_control;
		SET_FRAME_DATA(fr->nwk, *temp_mc, 1);
	}

	//TODO: lookup (in the spec 3.6.1.6)and figure out the routeing address and how to implement it.

	/*TODO a bunch more to add to the frame but I am not ready to do that yet...
	 * Troubleshooting needs to be done before I get to far ahead of myself.  Validate
	 * everything in section 3.6.2 of the zigbee spec.
	 */
//	RF230frameWrite((nlde->nsdu)-(nlde->NsduLength), nlde->NsduLength);
	//TODO: I need to create the pdu for the MAC sublayer.
	/*TODO: Security subclause is 4.2.2, I need to look at it and implement it.
	 * 		Add a section called security service provider (SSP)	 */
}


uint8_t get_NWK_Sequence_num(void){
	return(NWK_sequence_num++);
}

void NWK_setTxCB(trx_cb_t *tb){
	trx_cb = tb;
}

void NWK_txStatus(phy_trac_t trac){
	(trx_cb)(trac);
}
/*EOF*/
