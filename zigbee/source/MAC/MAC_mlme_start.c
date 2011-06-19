/*
 * MAC_mlme_start.c
 *
 *  Created on: Oct 14, 2010
 *      Author: mpoppe
 */
#include <frame.h>

#include "conf_zigbee.h"

#include <MAC/mac_prototypes.h>
#include "PHY/rc_rf230.h"

mac_status_t MAC_mlme_startReq(void){
	mac_pib_t *mpib = get_macPIB();
	phy_pib_t *ppib = get_phyPIB();

	uint16_t pan = DEFAULT_PANID;
	uint16_t addr =0x0000;
//Set the PANid

	MAC_setPANid(pan);


//Set the short address to the default Coor addr
	MAC_setShortAddr(addr);

//tell transeiver that we are the coord.

	I_AM_COORD(YES);
//Set the current Channel
	MAC_setCurrentChannel(DEFAULT_CHANNEL);

	return MAC_SUCCESS;
}
