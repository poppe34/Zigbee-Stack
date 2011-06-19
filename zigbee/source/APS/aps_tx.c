/*
 * aps_tx.c
 *
 *  Created on: Sep 1, 2010
 *      Author: mpoppe
 */
#include <frame.h>

#include <aps/aps.h>

void APS_frame_construct(frame_t *frm);

//shifts for the FCF frame setup
#define fcf_fr_type_shift		(0)
#define fcf_del_type_shift		(2)
#define fcf_ack_format_shift 	(4)
#define fcf_security_shift 		(5)
#define fcf_ack_request_shift	(6)
#define fcf_ext_header_shift 	(7)

/*TODO: I think i need to setup the PDU as a pointer t allow initicator to get the
* length of the data and the data itself.
*/

apdu_status_t APS_apsde_data(frame_t *frm) {
	uint8_t ex_len;
	apdu_status_t status = SUCCESS;
	apdu_t apdu;
	apsde_data_t apsde;
	
// Frame Control
	apdu.aps_fcf.fcf_fr_type = FRAME_TYPE_DATA;
	apdu.aps_fcf.fcf_ack_format = DATA_FRAME_ACK;
	apdu.aps_fcf.fcf_security = (apsde.TxOptions & 0x01);
	apdu.aps_fcf.fcf_ack_request = ((apsde.TxOptions >> 2) & 0x01);
	apdu.aps_fcf.fcf_ext_header = NO;

	apdu.dstEndpoint = apsde.dstEndpoint;
//	apdu.grpAddr = pdu.
	apdu.clusterID = apsde.clusterID;
	apdu.profileID = apsde.profileID;
	apdu.srcEndpoint = apsde.srcEndpoint;
	apdu.APScounter = APS_counter++;
//	apdu.extHeader = NULL;  need to add the frame extender header to allow fragmentation

	apdu.payload = apsde.asdu;

	switch(apsde.dstAddrMode){

	case(NO_DST_ADDR_OR_ENDPOINT):
		//TODO need to add logic for binding table
	break;

	case(GRP_ADDRESS):
		apdu.aps_fcf.fcf_del_type = DEL_MODE_GRP_ADDR;
		apdu.Addr = apsde.dstAddr;

	break;

	case(DST_ADDR_AND_ENDPOINT):
		apdu.aps_fcf.fcf_del_type = DEL_MODE_UNICAST;

		apdu.dstEndpoint = apsde.dstEndpoint;
		apdu.Addr = apsde.dstAddr;

	break;
	case(LONG_DST_ADDR_AND_ENDPOINT):
		//TODO use NIB nwkAddressMap but not developed
	break;

	}
	APS_frame_construct(frm);/* TODO: *fixed 09.03.10 For now I am going to pass the whole
	APDU but i am not happy about it I need to look into cleaning that up. Maybe use a pointer

	new TODO: It isn't working (9.07.10)
	*/

	//TODO setup send to NWK
/*
	zig->nlde.dstAddr.s_addr = zig->apsde.dstAddr;
	zig->nlde.NsduLength	= zig->apsde.ADSUlength;
	zig->nlde.nsdu			= zig->apsde.asdu;
	zig->nlde.NsduHandle  	= (00); //TODO don't know what this is yet... will do more research..
	zig->nlde.radius 		= zig->apsde.radius;
	zig->nlde.nonMemRadius	= nwkNonMemeberRadius;
	zig->nlde.DiscoverRoute = 0; // TODO I need to add the code to add this. Still not 100% when to initiate it
							 // look at section 3.6.3.5 in the Zigbee spec for clarification.
	zig->nlde.SecuityEnabled = (((zig->apsde.TxOptions)>>SEC_ENABLED) & 0x01);

	/*This is where I Left off... I need to finish setting up the NWK 9/3/10
	 *
	 * NOTE:  I am not really sure how I am going to handle waiting for ACKs
	 * My initial plan is to just got straight through and not worry about implementing
	 * AWKs and add that later.  My initial guess how I am going to do that is do some kind
	 * of callback that gets the past frame and resend it after some set time limit or clear it after
	 * it receives the ACK (9/3/10]	 */

	//status = (apdu_status_t)NWK_nlde_data(zig); //setup the status better.
	return status;

}


//This function will take in the apdu information construct the APDU Frame
void APS_frame_construct(frame_t *frm){
/*
	uint8_t count = 0;
	uint8_t temp_fcf = 0;

	//Add extended Sub_Frame header
			if(zig->apdu.aps_fcf.fcf_ext_header){
				//TODO Add Fragmenation Code
			}

	//Add APS Counter

	*(zig->apsde.asdu)++ = get_APS_Count();
	zig->apsde.ADSUlength++;

	// Add source Endpoint

	*(zig->apsde.asdu)++ = zig->apdu.srcEndpoint;
	zig->apsde.ADSUlength++;

	// Add Cluster ID and Profile ID if it is either a Data or an Acknowledge Frame

	if((zig->apdu.aps_fcf.fcf_fr_type == FRAME_TYPE_DATA) || (zig->apdu.aps_fcf.fcf_fr_type == FRAME_TYPE_ACK)) {

		*(zig->apsde.asdu)++ = ((zig->apdu.profileID >> 8) & 0xFF);
		*(zig->apsde.asdu)++ = (zig->apdu.profileID & 0xff);
		zig->apsde.ADSUlength+=2;


		*(zig->apsde.asdu)++ = ((zig->apdu.clusterID >> 8) & 0xFF);
		*(zig->apsde.asdu)++ = (zig->apdu.clusterID & 0xFF);
		zig->apsde.ADSUlength+=2;

	}

	// Add the Destination endpoint except in group mode since there is none
	if(zig->apdu.aps_fcf.fcf_del_type == DEL_MODE_GRP_ADDR) {
		*(zig->apsde.asdu)++ = zig->apdu.dstEndpoint;
		zig->apsde.ADSUlength++;
	}

	else {
		*(zig->apsde.asdu)++ = ((zig->apdu.Addr >> 8) & 0xFF);
		*(zig->apsde.asdu)++ = (zig->apdu.Addr & 0xFF);
		zig->apsde.ADSUlength+=2;

	}

	temp_fcf |= ((zig->apdu.aps_fcf.fcf_fr_type)<< fcf_fr_type_shift);
	temp_fcf |= ((zig->apdu.aps_fcf.fcf_del_type)<< fcf_del_type_shift);
	temp_fcf |= ((zig->apdu.aps_fcf.fcf_ack_format)<< fcf_ack_format_shift);
	temp_fcf |= ((zig->apdu.aps_fcf.fcf_security)<< fcf_security_shift);
	temp_fcf |= ((zig->apdu.aps_fcf.fcf_ack_request)<< fcf_ack_request_shift);
	temp_fcf |= ((zig->apdu.aps_fcf.fcf_ext_header)<< fcf_ext_header_shift);

	*(zig->apsde.asdu)++ = temp_fcf;
	zig->apsde.ADSUlength++;

*/



}
