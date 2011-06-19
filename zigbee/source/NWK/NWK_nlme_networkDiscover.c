/*
 * NWK_nlme_networkDiscover.c
 *
 *  Created on: Oct 20, 2010
 *      Author: mpoppe
 */

#include <frame.h>
#include <NWK/NWK_prototypes.h>
#include <MAC/mac_prototypes.h>
#include "MAC/MAC_mlme.h"
static nwk_netDisc_t *netDisc;

typedef (*nwk_discHandler_t)(nwk_discript_t *NWKdisc);
nwk_discHandler_t discovHandler;

void NWK_nlme_networkDiscoveryReq(uint32_t channel, uint8_t duration, void *cb){
	discovHandler = (nwk_discHandler_t *)cb;

	netDisc = (nwk_netDisc_t *)malloc(sizeof(nwk_netDisc_t));
	netDisc->count = 0;

	nwk_netDisc_t net;
	mac_scan_t *scan = (mac_scan_t *)malloc(sizeof(mac_scan_t));

	scan->ChannelPage = 0x00;
	scan->ScanChannels = channel;
	scan->type = ACTIVE_SCAN;
	scan->ScanDuration = duration;
	MAC_mlme_scanReq(scan);

	free(scan);

}

void nwk_addNetworkDiscription(nwk_discript_t *disc){
	nwk_discript_t *temp = netDisc->first;

	if(netDisc->count == 0){
		netDisc->first = disc;
		netDisc->count = 1;
		return;
	}
	for(uint8_t x=1; x<netDisc->count; x++){
		temp = temp->next;
	}
	temp->next = disc;
	disc->prev = temp;

	netDisc->count++;

}

void NWK_clearNetworkDiscription(void){
	nwk_discript_t *temp = netDisc->first;
	uint8_t x;

	for(x=1; x<netDisc->count; x++){
		temp = temp->next;
	}

	for(x=netDisc->count; x>0; x--){
		temp = temp->prev;
		free(temp->next);
	}
	netDisc->count =0;
}

void NWK_nlme_networkDiscoverConfirm_cb(mac_scanResult_t *result){
	netDisc->status = result->status;
	//(discovHandler)(netDisc);
}

uint8_t NWK_nlme_getNetworkCount(void){
	return netDisc->count;
}

nwk_discript_t *NWK_nlme_getNetworkTable(void){
	return netDisc->first;
}//
