/*
 * MAC_mlme_scan.h
 *
 * Created: 6/17/2011 3:01:08 PM
 *  Author: mpoppe
 */ 


#ifndef MAC_MLME_SCAN_H_
#define MAC_MLME_SCAN_H_

#include "MISC/security.h"

#include "MAC/mac.h"

typedef enum
{
	nlme_ED_Scan = 0x04,
}scan_request_t;

typedef enum{
	ED_SCAN = 0x00,
	ACTIVE_SCAN = 0x01,
	PASSIVE_SCAN = 0x02,
	ORPHAN_SCAN = 0x03,
}scan_type_t;

typedef struct MAC_SCAN{
	scan_type_t		type;
	scan_request_t	requestor;
	uint32_t 		ScanChannels;
	uint8_t			ScanDuration;
	uint8_t			ChannelPage;
	security_t		sec;
}mac_scan_t;

typedef struct MAC_SCAN_CONFIRM{
	mac_pan_descriptor_t 	*desc;
	scan_type_t 			type;
	mac_status_t			status;
	uint8_t					count;
}mac_scanResult_t;

void MAC_mlme_scanSetCb(voidPtr cb);
void MAC_mlme_scanSetDefaultCb(void);
void MAC_activeScan(mac_scan_t *scan);
void MAC_mlme_scanReq(mac_scan_t *scan);
void new_PAN_Table(void);
uint8_t MAC_getPanTableCount(void);
void add_to_PAN_Table(mac_pan_descriptor_t *desc);
void MAC_beaconStatus_cb(phy_trac_t trac);
void MAC_nextBeacon_cb(uint32_t *channels);
void MAC_mlme_scanConfirm(void);

#endif /* MAC_MLME_SCAN_H_ */