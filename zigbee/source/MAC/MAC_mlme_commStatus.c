/*
 * MAC_mlme_commStatus.c
 *
 * Created: 5/27/2011 9:03:58 AM
 *  Author: matt
 */ 
#include "compiler.h"

#include "MAC/mac.h"
#include "MAC/MAC_mlme.h"

#include "misc/security.h"

#include "alarms_task.h"

typedef voidPtr commStatus_cb_t(voidPtr info);

static uint8_t currentHandler;

commStatus_cb_t status_cb;

void MAC_mlme_commStatusInd(addr_t *destAddr, addr_t *srcAddr, mac_status_t status, security_t *sec)
{
	alarm_new(9, "Rx a comm status Indication");
	destAddr = destAddr;
	srcAddr = srcAddr;
	status = status;
	sec = sec;

}

