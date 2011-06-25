/*
 * NWK_nlme_netForm.c
 *
 *  Created on: Oct 20, 2010
 *      Author: mpoppe
 */

#include <frame.h>

#include "MISC/qsm.h"

#include "PHY/rc.h"

#include "MAC/mac.h"
#include "MAC/MAC_mlme.h"
#include "MAC/MAC_mlme_scan.h"
#include "MAC/MAC_mlme_start.h"

#include "NWK/NWK.h"
#include "NWK/NWK_nlme.h"
#include "NWK/NWK_command.h"

#include "conf_zigbee.h"

nwk_status_t NWK_nlme_formNetworkReq(nwk_nlme_nf_t *nf)
{

	mac_scan_t *scan;
	
	nwk_status_t status = NWK_SUCCESS;

	if(DEFAULT_COORD == 0)
	{
		status = NWK_INVALID_REQUEST;
		return status;
	}//end if
	//alloc memory to perform a scan
	scan = (mac_scan_t *)malloc(sizeof(mac_scan_t));

	scan->requestor = nwk_networkFormation;
	scan->type = ACTIVE_SCAN;
	scan->ChannelPage = DEFAULT_CHANNELPAGE;
	scan->ScanChannels = nf->scanChannels;
	scan->ScanDuration = nf->scanDuration;
	
	MAC_mlme_scanSetCb(&NWK_nlme_formNetworkActive_cb);
	MAC_mlme_scanReq(scan);
	
	return status;
}

void NWK_nlme_formNetworkED_cb(mac_scanResult_t* result)
{
	result = result;
	
}

void NWK_nlme_formNetworkActive_cb(mac_scanResult_t  *result)
{
	uint8_t count;
	Bool PANid_confirmed = NO, rescan;
	mac_mlme_start_t *start = (mac_mlme_start_t *)malloc(sizeof(mac_mlme_start_t));
	uint16_t PANid = DEFAULT_PANID;
	uint64_t exPANid = DEFAULT_EXT_PANID;
	
	nwk_nib_t *nnib = NWK_getNIB();
	mac_pib_t *mpib = get_macPIB();
	
	mac_pan_descriptor_t *currentDesc = (mac_pan_descriptor_t *)list_head(result->descList);
	
	count = list_length(result->descList);
	do
	{
		rescan = NO;
		
		for (uint8_t x=0; x<count; x++)
		{
			if(PANid == currentDesc->Coord.PANid)
			{
				PANid++;
				rescan = YES;
			}
			currentDesc = (mac_pan_descriptor_t *)currentDesc->next;
		}
	
	}while(rescan);	
	
	if(exPANid == 0x00)
	{
		exPANid = mpib->macLongAddress.extAddr;
	}
	
	start->beaconOrder = 0x0f;
	start->superFrameOrder = 0x0f;
	start->channel = DEFAULT_CHANNEL;
	start->channelPage = DEFAULT_CHANNELPAGE;
	start->PANcoord = YES;
	start->PANid = PANid;

	nnib->nwkExtendedPANid = exPANid;
	
	MAC_setShortAddr(0x0000);
    
    //Build the nwk Beacon Payload and add it to the MAC pib
    NWK_buildBeaconPayload();
	
    MAC_mlme_startReq(start);

	add_to_time_qsm(&NWK_nlme_linkStatus,NULL, ((nnib->nwkLinkStatusPeriod)*0x001E8480));
}

