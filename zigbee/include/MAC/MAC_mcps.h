#include "phy\phy.h"
#include "mac.h"
/*
 * MAC_mcps.h
 *
 * Created: 6/13/2011 3:02:01 PM
 *  Author: mpoppe
 */ 


#ifndef MAC_MCPS_H_
#define MAC_MCPS_H_

#include "compiler.h"

#include "MAC/mac.h"

#include "PHY/phy.h"


/*****************************   PROTOTYPES   *****************************/

// MAC_MCPS_data.c
void MAC_mcps_dataInd(mpdu_t *mpdu, frame_t *fr);
void MAC_mcps_dataReq(mpdu_t *mpdu, frame_t *fr);
void MAC_mcps_dataReq_cb(phy_trac_t status);
void MAC_mcps_dataConf(mac_status_t status);

#endif /* MAC_MCPS_H_ */void MAC_mcps_dataConf(uint8_t msduHandle, mac_status_t status, uint32_t timestamp);