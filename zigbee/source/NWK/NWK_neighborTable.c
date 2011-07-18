/*
 * NWK_neighborTable.c
 *
 *  Created on: Oct 20, 2010
 *      Author: mpoppe
 */

#include <frame.h>

#include "alarms_task.h"

#include "list.h"
#include "MISC/qsm.h"

#include "PHY/rc_rf230.h"

#include "NWK/NWK.h"
#include "NWK/NWK_neighborTable.h"
#include "NWK/NWK_command.h"




LIST(neighbor_table);

static uint8_t neighbor_count;

void NWK_neighborTableInit(void)
{
	list_init(neighbor_table);
	neighbor_count = 0;
}


nwk_neigh_t *NWK_getBestAddrForNetwork(uint64_t extendPANid)
{
	uint8_t x, lqi= 0x00;
	nwk_neigh_t *current, *best;
	current = (nwk_neigh_t *)(list_head(neighbor_table));

	for(x=0; x<(list_length(neighbor_table)); x++)
	{
		if(extendPANid == current->extendPANid)
		{
				best = current;
		}//end if
		current = current->next;
	}//end for
	return best;
}

list_t NWK_getNeighTable(void)
{
	return neighbor_table;
}
/*
nwk_neigh_t *NWK_getNeighTable(void){
	return table->first;
}

uint8_t NWK_getNeighTableCount(void){
	return table->count;
}
*/

nwk_neigh_t *NWK_nlme_neighborTableSearchShortAddr(uint16_t addr)
{
	nwk_neigh_t *currentNeighbor;
	
	currentNeighbor = list_head(neighbor_table);
	
	while(currentNeighbor)
	{
		if(currentNeighbor->shortAddr.shortAddr == addr)
		{
			return currentNeighbor;
		}
		else
		{
			currentNeighbor = currentNeighbor->next;
		}
	}
	return NULL;									
}

nwk_neigh_t *NWK_nlme_addNeighbor(void)
{
	nwk_neigh_t *newNeigh = (nwk_neigh_t *)malloc(sizeof(nwk_neigh_t));
	
	if(newNeigh)
	{
		list_add(neighbor_table, newNeigh);
		neighbor_count++;
	}
		
	return newNeigh;
}


void NWK_nlme_linkStatus(void)
{
	if(is_Coord())
	{
		nwk_linkStatusCmd_t link, link2;
		uint8_t count = 0, count2 = 0;
		nwk_neigh_t *currentTbl;
		payload_t *pl = frame_hdr(payload);
		
		//Get the first neighbor in the table loaded
		currentTbl = list_head(neighbor_table);
		
		// point the payload pointer to the location in the payload for the children addrs
		pl->ptr = &pl->pl[2];
		
		// run through the list of neighbors and add the addr and capabilities of the children
		// then add them to the the payload of the link status.
		for(uint8_t x=0; x<(list_length(neighbor_table)); x++)
		{
			if(currentTbl->relation == child) 
			{
				SET_FRAME_DATA(pl, currentTbl->shortAddr.shortAddr, 2);
				
				SET_FRAME_DATA(pl, currentTbl->cost, 1); //Need to have a better defined path cost
				count++;
				
				currentTbl =(nwk_neigh_t *)currentTbl->next;
				
				//TODO: add a if statement for a condition that we had enough children that we would need two payloads
				
			}
		}
		
		link.count = count;
		link.first = YES;
		link.last = YES;
		link.reserved = NO;
		
		link2.count = count2;
		link2.first = YES;
		link2.last = YES;
		link2.reserved = NO;
		
		pl->ptr = &pl->pl[1];
		SET_FRAME_DATA(pl, *((uint8_t *)&link), 1);
		
		NWK_cmd_linkStatus(pl);
			
		nwk_nib_t *nnib = NWK_getNIB();
		
		add_to_time_qsm(&NWK_nlme_linkStatus, NULL, ((nnib->nwkLinkStatusPeriod)*0x001E8480));
	}	
	alarm_new(12, "NWK Layer sent Link Status");
}

void NWK_linkStatusHandler(void){


}	