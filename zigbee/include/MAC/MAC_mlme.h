/*
 * MAC_mlme.h
 *
 *  Created on: Oct 14, 2010
 *      Author: mpoppe
 */

#ifndef MAC_MLME_H_
#define MAC_MLME_H_
#include "frame.h"

#include "MISC/security.h"

#include "MAC/mac.h"

#include "PHY/phy.h"

//MLME associate 
void MAC_mlme_assocReq(addr_t *destAddr, uint32_t page, uint8_t channel, uint8_t capabilites, security_t *sec);
void MAC_mlme_assocInd(long_addr_t *addr, mac_capibilities_t capib, security_t *sec);
void MAC_mlme_assocConf(mac_status_t status, short_addr_t *addr, security_t *sec);
void MAC_mlme_assocReq_cb(phy_trac_t trac);
void MAC_mlme_assocReqHandler(mpdu_t *mpdu, frame_t *fr);
void MAC_mlme_assocRespHandler(mpdu_t *mpdu, frame_t *fr);

//MLME DisAssoc 
void mac_mlme_disassocReq(mac_disassoc_reason_t reason);
void MAC_disassoc_cb(phy_trac_t trac);
void MAC_mlme_disassocConf(mac_status_t status);
void MAC_mlme_disAssocHandler(mpdu_t *mpdu, frame_t *fr);

//MLME Communications Status
void MAC_mlme_commStatusInd(addr_t *destAddr, addr_t *srcAddr, mac_status_t status, security_t *sec);
void MAC_mlme_commStatus_setHandlerNum(uint8_t num);

//MLME Scan



//MLME Beacon Notify
void MAC_mlme_beaconInd(mpdu_t *mpdu, frame_t *fr);

//MLME Reset
mac_status_t MAC_mlme_resetReq(void);

//MLME Poll
void MAC_mlme_pollReq(addr_t *dstAddr);
void MAC_mlme_pollReq_cb(mac_status_t status);
void MAC_mlme_pollConf(mac_status_t status);

//MLME Start
mac_status_t MAC_mlme_startReq(void);

#endif /* MAC_MLME_H_ */
