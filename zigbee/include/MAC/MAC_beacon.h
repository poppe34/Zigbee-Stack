/*
 * MAC_beacon.h
 *
 * Created: 6/21/2011 5:09:02 PM
 *  Author: mpoppe
 */ 


#ifndef MAC_BEACON_H_
#define MAC_BEACON_H_

#include "list.h"

typedef void(*mac_beaconHandler_t)(mac_status_t status);

void MAC_beaconConfirm(mac_status_t status);
void MAC_beaconReq_cb(mac_status_t status);
void MAC_beacon(void);
void MAC_beaconHandler(mpdu_t *mpdu, frame_t *fr);
list_t * MAC_panDescriptor_getList(void);
void MAC_panDescriptor_init(void);
void MAC_beacon_setCB(void *cb);

#endif /* MAC_BEACON_H_ */