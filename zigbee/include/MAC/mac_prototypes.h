/*
 * mac_prototypes.h
 *
 *  Created on: Oct 12, 2010
 *      Author: mpoppe
 */

#ifndef MAC_PROTOTYPES_H_
#define MAC_PROTOTYPES_H_

#include "phy/phy.h"
#include "nwk/NWK.h"
#include "mac/mac.h"
#include "frame.h"



//MAC_beacon.c
void MAC_beaconHandler(mpdu_t *mpdu, frame_t *fr);
void MAC_beaconReq_cb(mac_status_t status);
void MAC_beacon(void);
void MAC_beaconConfirm(mac_status_t status);


//MAC_data_service.c
void MAC_dataIndication(frame_t *fr);
void change_receive_mode(uint8_t temp);
void MAC_incomingFrame(frame_t *fr);

//MAC_trx.c
mac_status_t MAC_createFrame(mpdu_t *mpdu, frame_t *fr);
mac_filter_t MAC_breakdownFrame(mpdu_t *mpdu, frame_t *fr);
mac_filter_t MAC_secondLevelFilter(mpdu_t *mpdu);
void MAC_issueACK(uint8_t seq_num);
void MAC_setTxCB(voidPtr tb);
void MAC_txStatus(phy_trac_t trac);


//MAC_ack.c
Bool check_Ack(uint8_t dsn);
void add_ack(uint8_t dsn);
void remove_handler(uint8_t dsn);
void shift_ack(uint8_t pos);
mac_status_t MAC_waitACK(uint8_t num);


//MAC.c


//temp
void assoced(nwk_status_t status);
void join_cb(mac_status_t status);
#endif /* MAC_PROTOTYPES_H_ */
