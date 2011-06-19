/*
 * NWK_nlme_netForm.c
 *
 *  Created on: Oct 20, 2010
 *      Author: mpoppe
 */

#include <frame.h>
#include <NWK/NWK_prototypes.h>
#include <MAC/mac_prototypes.h>

#include "conf_zigbee.h"

nwk_status_t NWK_formNetwork(void){

	nwk_status_t status = NWK_SUCCESS;

	if(DEFAULT_COORD == 0){
		status = NWK_INVALID_REQUEST;
		return status;
	}//end if

	return status;
}
