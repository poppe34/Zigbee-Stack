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

mac_status_t mac_init(void);
uint16_t get_short_ADDR(void);
void get_PAN_ID(uint8_t *id);
uint64_t get_IEEE_ADDR(void);
void set_PAN_ID(uint8_t *pan_id);
void set_short_ADDR(uint16_t addr);
void set_IEEE_ADDR(uint64_t addr);
uint8_t get_seqNum(void);
Bool MAC_isAssoc(void);
void MAC_setAssoc(Bool value);

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
mac_status_t mac_init(void);
uint8_t get_MAC_seqNum(void);
mac_pib_t *get_macPIB(void);
void MAC_setPANid(uint16_t pan);
void MAC_setShortAddr(uint16_t addr);
void MAC_setCurrentChannel(uint8_t chan);
void MAC_setLongAddr(uint64_t addr);
void MAC_setCoordPANid(uint16_t pan);
void MAC_setCoordShortAddr(uint16_t addr);
void MAC_setCoordLongAddr(uint64_t addr);

//temp
void assoced(nwk_status_t status);
void join_cb(mac_status_t status);
#endif /* MAC_PROTOTYPES_H_ */
