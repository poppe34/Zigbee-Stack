/*
 * MAC_mlme_assoc.h
 *
 * Created: 6/25/2011 5:34:17 PM
 *  Author: matt
 */ 


#ifndef MAC_MLME_ASSOC_H_
#define MAC_MLME_ASSOC_H_

#include "MISC/security.h"

typedef enum
{
	MAC_ASSOC_SUCCESS = 0x00,
	MAC_ASSOC_CAPACITY = 0x01,
	MAC_ASSOC_DENIED = 0x02,
	
}mac_assoc_status_t;


typedef struct {
	uint64_t				extAddr;
	uint16_t				shortAddr;
	mac_assoc_status_t		status;
	security_t				sec;
}mac_assoc_resp_t; 

typedef struct ASSOC_DATA
{
	struct ASSOC_DATA		*next;
	mac_assoc_resp_t		*resp;
}mac_assoc_data_t;

void MAC_mlme_assoc_init(void);
Bool MAC_mlme_assocSendResp(uint64_t *addr);

#endif /* MAC_MLME_ASSOC_H_ */