/*
 * NWK_nlde_data.c
 *
 * Created: 6/14/2011 2:48:38 PM
 *  Author: mpoppe
 */ 


#include "compiler.h"

#include "alarms_task.h"

#include "frame.h"

#include "NWK\NWK_nlde.h"
#include "NWK\NWK_prototypes.h"


void NWK_nlde_dataReq(npdu_t *npdu, frame_t *fr)
{
	
	
}

void NWK_nlde_dataInd(npdu_t *npdu, frame_t *fr)
{
	alarm_new(9, "Rx NWK data Frame");
}

void NWK_nlde_dataConf(nwk_status_t status)
{
	
}