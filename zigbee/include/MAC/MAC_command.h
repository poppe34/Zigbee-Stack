/*
 * MAC_command.h
 *
 * Created: 5/26/2011 6:20:36 AM
 *  Author: matt
 */ 


#ifndef MAC_COMMAND_H_
#define MAC_COMMAND_H_

/*================================= INCLUDES         =========================*/
#include "frame.h"

#include "MISC/security.h"

#include "MAC/mac.h"


typedef enum COMMAND_TYPE{
	MAC_ASSOC_REQUEST = 0x01,
	MAC_ASSOC_RESPONCE = 0x02,
	MAC_DISASSOC_NOTIFY = 0x03,
	MAC_DATA_REQUEST = 0x04,
	MAC_PAN_CONFLICT_NOTIFY = 0x05,
	MAC_ORPHAN_NOTIFY = 0x06,
	MAC_BEACON_REQUEST = 0x07,
	MAC_COORD_REALIGN = 0x08,
	MAC_GTS_REQUEST = 0x09,
}mac_command_type_t;

/*================================= PROTOTYPES         =========================*/

uint8_t MAC_assocRequestCommand(addr_t *destAddr, uint8_t capibilities, security_t *sec);
uint8_t MAC_assocResponceCommand(mlme_assoc_t *assoc);
void MAC_disassocCommand(addr_t *destAddr, mac_disassoc_reason_t reason);
uint8_t MAC_dataRequestCommand(addr_t *dstAddr);
uint8_t MAC_panIDConflictCommand(void);
uint8_t MAC_orphanCommand(void);
void    MAC_beaconReqCommand(void);
void    MAC_commandCoordRealign(addr_t *destAddr, security_t *sec);
void	MAC_commandHandler(frame_t *fr, mpdu_t *mpdu);

#endif /* MAC_COMMAND_H_ */