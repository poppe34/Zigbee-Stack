/*
 * NWK_nlme_join.h
 *
 * Created: 6/23/2011 1:56:13 PM
 *  Author: mpoppe
 */ 


#ifndef NWK_NLME_JOIN_H_
#define NWK_NLME_JOIN_H_

typedef struct 
{
	short_addr_t		nwkAddr;
	long_addr_t			extAddr;
	mac_capibilities_t	capib;
	uint8_t				rejoin;
	Bool				secureRejoin;
}nwk_nlme_joinInd_t;


void NWK_nlme_joinInd(nwk_nlme_joinInd_t *join);
void NWK_nlme_joinReq(nwk_join_t *jn);

#endif /* NWK_NLME_JOIN_H_ */