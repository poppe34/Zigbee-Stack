/*
 * MAC_mlme_reset.c
 *
 *  Created on: Oct 14, 2010
 *      Author: mpoppe
 */

#include <frame.h>

#include "MAC/mac.h"
#include "MAC/mac_prototypes.h"

mac_status_t MAC_mlme_resetReq(void){
	return(mac_init());
}
