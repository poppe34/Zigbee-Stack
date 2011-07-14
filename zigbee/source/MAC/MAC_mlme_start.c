/*
 * MAC_mlme_start.c
 *
 *  Created on: Oct 14, 2010
 *      Author: mpoppe
 */
#include <frame.h>
#include "alarms_task.h"

#include "conf_zigbee.h"

#include "PHY/rc_rf230.h"

#include "MAC/mac.h"
#include "MAC/MAC_mlme_start.h"
#include "MAC/MAC_mlme_assoc.h"


MAC_mlme_start_CB_t startCBhandler;

void MAC_mlme_startReq(mac_mlme_start_t *start)
{
	mac_pib_t *mpib = get_macPIB();
	phy_pib_t *ppib = get_phyPIB();

	if(mpib->macShortAddress.shortAddr == 0xffff)
	{
		MAC_mlme_startConf(MAC_NO_SHORT_ADDRESS);
	}
	mpib->macBeaconOrder = start->beaconOrder;
	mpib->macSupeframeOrder = start->superFrameOrder;
	
	// Don't have the Channel Page in the pib.
	//mpib->macChannelPage = start->channelPage;

	//Set the PANid
	MAC_setPANid(start->PANid);

	if(start->beaconOrder < 0x0f)
	{
		mpib->macBattLifeExt = start->batteryLifeExt;
		mpib->macBeaconTxTime = start->startTime;
	}		
	//tell transceiver that we are the coord.
	I_AM_COORD(start->PANcoord);

	//Set the current Channel
	MAC_setCurrentChannel(start->channel);
	
	if(start->PANcoord)
	{
		MAC_mlme_assoc_init();
	}	
	MAC_mlme_startConf(MAC_SUCCESS);
}


void MAC_mlme_startConf(mac_status_t status)
{
	if(startCBhandler)
	{	
		(startCBhandler)(status);
	}
	else
	{
//		alarm("Recieved MAC start Confirm without setting the CB");
	}		
	
}

void MAC_mlme_start_setCB(voidPtr cb)
{
	startCBhandler = (MAC_mlme_start_CB_t *)cb;
}

void MAC_mlme_start_setDefaultCB(void)
{
	startCBhandler = NULL;
}