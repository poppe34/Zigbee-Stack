/*
 * MAC_mlme_start.h
 *
 * Created: 6/23/2011 1:05:23 PM
 *  Author: mpoppe
 */ 


#ifndef MAC_MLME_START_H_
#define MAC_MLME_START_H_

#include "MISC/security.h"

typedef struct 
{
	uint16_t	PANid;
	uint8_t		channel;
	uint32_t	channelPage;
	uint32_t	startTime;
	uint8_t		beaconOrder;
	uint8_t		superFrameOrder;
	Bool		PANcoord;
	Bool		batteryLifeExt;
	Bool		CoordRealignment;
	security_t	CoordRealSec;
	security_t	BeaconSec;	
}mac_mlme_start_t;

typedef void (*MAC_mlme_start_CB_t)(status);

void MAC_mlme_startReq(mac_mlme_start_t *start);
void MAC_mlme_startConf(mac_status_t status);



#endif /* MAC_MLME_START_H_ */