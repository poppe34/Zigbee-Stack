/*
 * MAC_mlme_orphan.c
 *
 *  Created on: Oct 25, 2010
 *      Author: mpoppe
 */
#include "frame.h"

#include "MAC/mac.h"
#include "MAC/MAC_mlme.h"
#include "MAC/MAC_command.h"

#include "MISC/security.h"

#include "alarms_task.h"

static addr_t *orphanedAddr;
static security_t *orphanedSec;

/*------------------------------------------------------------------------------------------
 * Function:    MAC_mlme_orphanInd
 *
 * Description: This function reports to the Next Higher Layer (NHL) of a coord that a device 
 *              has been orphaned
 *
 * arg: addr of the orphaned device
 *
 * arg: security of the orphaned device
 *
 * brief: 
 *------------------------------------------------------------------------------------------*/
void MAC_mlme_orphanInd(long_addr_t srcAddr, security_t sec)
{
	srcAddr = srcAddr;
	sec = sec;
	
	alarm("Recieved an orphan Indication");
}

void MAC_mlme_orphanResp(long_addr_t orphanLongAddr, short_addr_t OrphanShortAddr, Bool assocMember, security_t sec)
{
    if(assocMember)
        {
			orphanedAddr = (addr_t *)malloc(sizeof(addr_t));
			orphanedSec = (security_t *)malloc(sizeof(security_t));
			
			orphanedAddr->mode = MAC_SHORT_ADDRESS;
			orphanedAddr->shortAddr = OrphanShortAddr;
			
			*orphanedSec = sec;
			
	        MAC_commandCoordRealign(orphanedAddr, orphanedSec);
			
		}	
}	

void MAC_mlme_orphanTxCb(mac_status_t status)
{
	MAC_mlme_commStatusInd(orphanedAddr, NULL, status, orphanedSec);
	free(orphanedAddr);
	free(orphanedSec);
}