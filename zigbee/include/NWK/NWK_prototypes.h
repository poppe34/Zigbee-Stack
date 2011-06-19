/*
 * NWK_prototypes.h
 *
 *  Created on: Oct 14, 2010
 *      Author: mpoppe
 */

#ifndef NWK_PROTOTYPES_H_
#define NWK_PROTOTYPES_H_

#include "compiler.h"
#include "MAC/mac.h"
#include "NWK/NWK.h"

#include "MAC/MAC_mlme_scan.h"
#include "NWK/NWK_neighborTable.h"

#include "list.h"
//NWK.c
void NWK_buildBeaconPayload(void);
//frame_data_t *NWK_getBeaconPayload(void);
void NWK_setExtendedPANid(uint64_t addr);
void NWK_setShortAddr(uint16_t addr);
void NWK_setPANid(uint16_t pan);
nwk_nib_t *NWK_getNIB(void);
void nwk_init(void);

//NWK_trx.c
void NWK_createFrame(npdu_t *npdu, frame_t *fr);
npdu_t * NWK_trx_frameBreakdown(frame_t *fr);
nwk_status_t NWK_nlde_data(frame_t *fr);
uint8_t get_NWK_Sequence_num(void);
void NWK_setTxCB(trx_cb_t *tb);
void NWK_txStatus(phy_trac_t trac);
void MAC_setCoordShortAddr(uint16_t addr);
//NWK_beacon.c
void NWK_beaconInd(mac_pan_descriptor_t *desc, mpdu_t *mpdu, frame_t *fr);

//NWK_nlme_networkDiscover.c
void NWK_nlme_networkDiscoveryReq(uint32_t channel, uint8_t duration, void *cb);
void NWK_nlme_networkDiscoverConfirm_cb(mac_scanResult_t *result);
void nwk_addNetworkDiscription(nwk_discript_t *disc);

//NWK_nlme_join
void NWK_nlme_joinNetDiscov_cb(nwk_netDisc_t *netDisc);
void NWK_nlme_joinReq(nwk_join_t *join, void *cb);
void NWK_nlme_joinMacAssoc_cb(mac_status_t status);
void NWK_nlme_joinTx_cb(uint8_t num);
void NWK_nlme_joinConfirm(nwk_status_t status);
void NWK_nlme_rejoinScan_cb(mac_scanResult_t *result);

//NWK_neighborTable.c
void NWK_neighborTableInit(void);
list_t NWK_getNeighTable(void);
nwk_neigh_t *NWK_getBestAddrForNetwork(uint64_t extendPANid);

//NWK_command.c
nwk_status_t NWK_routeRequest(uint8_t addr[]);
nwk_status_t NWK_status_cmd(nwk_status_code_t code, uint16_t addr);
mac_status_t NWKtoMAC_bridge(mac_fcf_t *fcf, npdu_t *npdu, frame_t *fr);

//NWK_beacon.c
void NWK_beaconFilterControl(uint64_t PANid);
void NWK_beaconInd(mac_pan_descriptor_t *desc, mpdu_t *mpdu, frame_t *fr);

//NWK_NLME_netForm
nwk_status_t NWK_formNetwork(void);
#endif /* NWK_PROTOTYPES_H_ */

//