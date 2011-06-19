/*
 * NWK_nlde.h
 *
 * Created: 6/13/2011 4:39:42 PM
 *  Author: mpoppe
 */ 


#ifndef NWK_NLDE_H_
#define NWK_NLDE_H_

#include "NWK/nwk.h"

// Network Data
void NWK_nlde_dataReq(npdu_t *npdu, frame_t *fr);
void NWK_nlde_dataInd(npdu_t *npdu, frame_t *fr);
void NWK_nlde_dataConf(nwk_status_t status);



#endif /* NWK_NLDE_H_ */