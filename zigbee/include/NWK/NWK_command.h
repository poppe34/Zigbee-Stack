#include "frame.h"
/*
 * NWK_command.h
 *
 * Created: 6/15/2011 3:48:12 PM
 *  Author: mpoppe
 */ 


#ifndef NWK_COMMAND_H_
#define NWK_COMMAND_H_

typedef enum 
{
	no_route_avail_NWK = 0x00,
	treeLink_failure_NWK = 0x01,
	nonTreeLink_failure_NWK = 0x02,
	low_batteryLevel_NWK = 0x03,
	no_routing_capacity_NWK = 0x04,
	no_indirect_capacity_NWK = 0x05,
	indirect_transaction_expiry_NWK = 0x06,
	target_device_unavailable_NWK = 0x07,
	target_address_unallocated_NWK = 0x08,
	parent_link_failure_NWK = 0x09,
	validate_route_NWK = 0x0a,
	source_route_failure_NWK = 0x0b,
	manyToOne_failure_NWK = 0x0c,
	address_conflict_NWK = 0x0d,
	verify_addresses_NWK = 0x0e,
	panId_update_NWK = 0x0f,
	network_addr_update_NWK = 0x10,
	bad_frame_counter_NWK = 0x11,
	bad_key_seq_num_NWK = 0x12,
}nwk_statusCode_t;

typedef enum
{
	NWK_ROUTE_REQUEST = 0x01,
	NWK_ROUTE_REPLY = 0x02,
	NWK_NETWORK_STATUS = 0x03,
	NWK_LEAVE = 0x04,
	NWK_ROUTE_RECORD = 0x05,
	NWK_REJOIN_REQUEST = 0x06,
	NWK_REJOIN_RESPONSE = 0x07,
	NWK_LINK_STATUS = 0x08,
	NWK_NETWORK_REPORT = 0x09,
	NWK_NETWORK_UPDATE = 0xa,
}nwk_cmd_id;

START_PACK
typedef struct PACK 
{
	COMBINE(5, (
	uint8_t		rsrv2: 1,
	uint8_t		multicast: 1,
	uint8_t		dstIEEEAddr: 1,
	uint8_t		manyToOne: 2,
	uint8_t		rsvr1: 3))
}nwk_reqCmdOptionField_t;
END_PACK

START_PACK
typedef struct PACK
{
	COMBINE(5, (
	uint8_t		rsrv1: 1,
	uint8_t		multicast: 1,
	uint8_t		responderIEEE: 1,
	uint8_t		originatorIEEE: 1,
	uint8_t		rsvr2: 4))
}nwk_respondCmdOptionField_t;
END_PACK

START_PACK
typedef struct PACK
{
	COMBINE(4, (
	uint8_t		rsvr1: 5,
	uint8_t		rejoin: 1,
	uint8_t		request: 1,
	uint8_t		removeChild: 1))
}nwk_leaveCmdOptionField_t;
END_PACK

START_PACK
typedef struct PACK
{
	COMBINE(4, (
	uint8_t		count: 4,
	uint8_t		first: 1,
	uint8_t		last: 1,
	uint8_t		reserved: 1))
}nwk_linkStatusCmd_t;
END_PACK

START_PACK
typedef struct PACK
{
	COMBINE(2, (
	uint8_t		reportInfo_count: 5,
	uint8_t		reportCmd_ID: 3))
}nwk_reportCmdOpt_t;
END_PACK

void NWK_cmd_routeReq(short_addr_t destAddr, short_addr_t grpID);
void NWK_cmd_routeReply(short_addr_t orginator, uint8_t path_cost);
void NWK_cmd_NetStatus(nwk_statusCode_t statusCode, short_addr_t addr);
void NWK_cmd_leave(nwk_leaveCmdOptionField_t leave);
void NWK_cmd_routeRec(short_addr_t addr);
void NWK_cmd_rejoinReq(void);
void NWK_cmd_rejoinResp(short_addr_t addr, uint8_t status);
void NWK_cmd_linkStatus(void);

#endif /* NWK_COMMAND_H_ */