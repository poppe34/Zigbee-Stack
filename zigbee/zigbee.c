/*
 * zigbee.c
 *
 *  Created on: Oct 22, 2010
 *      Author: mpoppe
 */

#include <frame.h>
#include "zigbee.h"

#include "RF230/RF230.h"

#include "phy/phy.h"

#include "MAC/mac_prototypes.h"

#include "NWK/NWK_prototypes.h"


void zigbee_init(void){
	uint8_t status = 0;
    
    time_init();
    frame_init();
	rf230_init();
	phy_init();
	mac_init();
	nwk_init();
//	aps_init();
//	af_init();
//	zdo_init();
	status = 1;
	return status;
}
