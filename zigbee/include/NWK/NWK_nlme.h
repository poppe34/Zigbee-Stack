/*
 * NWK_nlme.h
 *
 * Created: 6/21/2011 2:37:14 PM
 *  Author: mpoppe
 */ 


#ifndef NWK_NLME_H_
#define NWK_NLME_H_


typedef struct
{
	uint32_t	scanChannels;
	uint8_t		scanDuration;
	uint8_t		beaconOrder;
	uint8_t		superframeOrder;
	uint8_t		BatteryLifeExt;
}nwk_nlme_nf_t;



//Network Form
nwk_status_t NWK_nlme_formNetworkReq(nwk_nlme_nf_t *nf);
void NWK_nlme_formNetworkED_cb(mac_scanResult_t* result);
void NWK_nlme_formNetworkActive_cb(mac_scanResult_t  *result);
void NWK_nlme_linkStatus(void);
#endif /* NWK_NLME_H_ */