/*
 * MAC_scan.c
 *
 *  Created on: Sep 22, 2010
 *      Author: mpoppe
 */
#include "misc/qsm.h"

#include <frame.h>

#include "MAC/mac_prototypes.h"
#include "MAC/MAC_mlme.h"
#include "MAC/MAC_command.h"
#include "MAC/MAC_mlme_scan.h"

#include "alarms_task.h"

void MAC_mlme_scanConfim(void);

mac_pan_descriptor_t PANs_table[20]; //TODO: make this a variable called panTableMAX or something like that. Also i might make this a linked list
uint8_t pointer = 0x00;
mac_scan_t *current_scan;
phy_pib_t *ppib;
mac_pib_t *mpib;
uint32_t wait = 0x00000000;
uint8_t page;
uint16_t time;
scan_type_t type;
uint8_t temp;
uint16_t old_PANid;
uint32_t *channels;
volatile mac_status_t status;

typedef void (*mac_scanHandler_t)(mac_scanResult_t *result);
mac_scanHandler_t scanHandler;

void MAC_mlme_scanReq(mac_scan_t *scan){
	
//	TODO:	I need to make the memory allocation dynamic not static in the future

// Get the current MAC_PIB and PHY PIB
	ppib = get_phyPIB();
	mpib = get_macPIB();
	type = scan->type;
	switch(type){

	case(ED_SCAN):
	break;

	case(ACTIVE_SCAN):


	// Change the mode of the receiver to only receive beacons
//	TODO:	I need to change add a function that changes the different modes for example: promisciuous, beacon only
		change_receive_mode(yes);

		// Get the current PAN id store and then set the PAN id to 0xffff
			old_PANid = mpib->macPANid;

			MAC_setPANid(0xffff);
			status = MAC_SCAN_IN_PROGRESS;
			MAC_activeScan(scan);

	break;

	case(PASSIVE_SCAN):
	break;

	case(ORPHAN_SCAN):
	break;
	}




}

void MAC_activeScan(mac_scan_t *scan){
//	TODO: 	This is a big one... the timeing on this is way off I need to figure out the wait then i need to add it to the que and create a function
//			to return to to continue my  scan
//
//	TODO:	THere is a flaw in my design I have to start on channel 11 (also I dont scan 11) for the scan to scan 11 - 26 also my wait time
//			is not calc. correctly

	channels = (uint32_t *)malloc(sizeof(uint32_t));

// Variables needed to complete the scans
//	wait = (((aBaseSuperframeDuration << (current_scan.ScanDuration)) + aBaseSuperframeDuration)<<aMicroSecPerSymbol);
	wait = 0x0009f600;
	page = scan->ChannelPage;
	*channels = scan->ScanChannels;
	MAC_nextBeacon_cb(channels);
}

void end_active_scan(void)
{
	// Restore back to normal receive mode
	change_receive_mode(NO);
	//	Restore the old PAN id
	MAC_setPANid(old_PANid);
	status = MAC_SUCCESS;
	free(channels);
	MAC_mlme_scanConfirm();
}
mac_pan_descriptor_t *get_PAN_Table(uint8_t pos){
	return &PANs_table[pos];
}

//	TODO:	Alot needs to be added this function right now i am not sure on what.
void add_to_PAN_Table(mac_pan_descriptor_t *desc){
	PANs_table[pointer] = *desc;
	pointer++;

#ifdef debug
	if (pointer > 20){
	alarm("PAN TABLE FULL");
	}
#endif

}//end add_to_PAN_table
uint8_t MAC_getPanTableCount(void){
	return pointer;
}
void new_PAN_Table(void){
	pointer = 0;
}

void MAC_nextBeacon_cb(uint32_t *channels)
{
	//TODO: keep a running tally if all beacons sent ok
	uint8_t x;
	uint32_t mask = 0x00000001;
	if(*channels == 0)
	{
		end_active_scan();
		return;
	}
	for(x=0; x<32;x++)
	{
//	TODO: 	Add code for unsupported channel

		if((*channels >> x) & mask)
		{

			*channels &= ~(mask << x);
			MAC_setCurrentChannel(x);
			MAC_beaconReqCommand();
			add_to_time_qsm(&MAC_nextBeacon_cb, channels, wait);
			return;
		}//end if
	}//end for x

}
void MAC_beaconStatus_cb(phy_trac_t trac)
{
	switch(trac)
	{
	case(TRAC_SUCCESS):
		status = MAC_SUCCESS;
	break;

	case(TRAC_NO_ACK):

	break;

	case(TRAC_CHANNEL_ACCESS_FAILURE):

	break;

	case(TRAC_INVALID):

	break;

	case(TRAC_SUCCESS_DATA_PENDING):
		break;
	}

}
void MAC_mlme_scanSetCb(voidPtr cb)
{
	scanHandler = (mac_scanHandler_t *)cb;
}

void MAC_mlme_scanSetDefaultCb(void)
{
	//TODO: I need to setup a default callback
}
void MAC_mlme_scanConfirm(void)
{
	mac_scanResult_t *result = (mac_scanResult_t *)malloc(sizeof(mac_scanResult_t));
	result->count 	= MAC_getPanTableCount();
	result->desc 	= get_PAN_Table(0);
	result->status 	= status;
	result->type	= type;
    if(scanHandler)
	    (scanHandler)(result);
	else
	    alarm("No Scan Handler was implemented");
}


