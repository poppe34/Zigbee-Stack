/*
 * NWK_neighborTable.c
 *
 *  Created on: Oct 20, 2010
 *      Author: mpoppe
 */

#include <frame.h>
#include <NWK/NWK_prototypes.h>

#include "list.h"
LIST(neighbor_table);

void NWK_neighborTableInit(void){
list_init(neighbor_table);
}


nwk_neigh_t *NWK_getBestAddrForNetwork(uint64_t extendPANid){
	uint8_t x, lqi= 0x00;
	nwk_neigh_t *current, *best;
	current = (nwk_neigh_t *)(list_head(neighbor_table));

	for(x=0; x<(list_length(neighbor_table)); x++){

		if(extendPANid == current->extendPANid){

				best = current;

		}//end if
		current = current->next;
	}//end for
	return best;
}

list_t NWK_getNeighTable(void){
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
