/*
 * NWK_nlme_netForm.c
 *
 *  Created on: Oct 20, 2010
 *      Author: mpoppe
 */

#include <frame.h>

#include "MAC/mac.h"
#include "MAC_mlme.h"
#include "MAC/MAC_mlme_scan.h"



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
	scan->type = ED_SCAN;
	scan->ChannelPage = DEFAULT_CHANNELPAGE;
	scan->ScanChannels = nf->scanChannels
	scan->ScanDuration = nf->scanDuration
	
	MAC_mlme_scanSetCb(&NWK_nlme_formNetworkActive_cb);
	MAC_mlme_scanReq(scan);
	
	return status;
}

void NWK_nlme_formNetworkED_cb(mac_scanResult_t* result)
{
	
	
}

void NWK_nlme_formNetworkActive_cb(mac_scanResult_t  *result)
{
	
}