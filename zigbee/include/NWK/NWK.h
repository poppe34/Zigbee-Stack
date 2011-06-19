/*
 * nwk.h
 *
 *  Created on: Sep 3, 2010
 *      Author: mpoppe
 */

#ifndef NWK_H_
#define NWK_H_

#include "frame.h"

#define NWK_UNICAST		(0)
#define	NWK_INDIRECT	(1)
#define	NWK_BROADCAST	(2)
#define	NWK_GRP_ADDR	(3)

#define NWK_data		(0)
#define NWK_command		(1)

#define NWK_STARTING_ROUTE_COST		(0)

#define NWK_frame_type_shift		(0)
#define	NWK_protocol_ver_shift		(2)
#define NWK_discover_rt_shift		(6)
#define NWK_multicast_shift			(8)
#define NWK_security_shift			(9)
#define NWK_source_rt_shift			(10)
#define NWK_dest_IEEE_shift			(11)
#define NWK_src_IEEE_shift			(12)

#define nwkcDefaultSecurityLevel
#define nwkcDiscoveryRetryLimit		0x03
#define nwkcMinHeaderOverhead		0x08
#define nwkcProtocolVersion			0x02
#define nwkcWaitBeforValidation		0x0500
#define nwkcRouteDiscoverTime		0x2710
#define nwkcMaxBroadcastJitter		0x40
#define nwkcInitialRREQRetries		0x03
#define nwkcRREQRetries				0x02
#define nwkcRREQRetryInterval		0xfe
#define nwkcMinRREQJitter			0x01
#define nwkcMaxRREQJitter			0x40
#define nwkcMACFrameOverhead		0x0b

#define nwkNonMemeberRadius	(6) //7 is treated as infinite

#define NWK_CAP_INFO_ALT_COORD_SHIFT		(0)
#define NWK_CAP_INFO_DEV_TYPE_SHIFT			(1)
#define NWK_CAP_INFO_POWER_SOURCE_SHIFT		(2)
#define NWK_CAP_INFO_REC_IDLE_SHIFT			(3)
#define NWK_CAP_INFO_SEC_CAP_SHIFT			(6)
#define NWK_CAP_INFO_ALLOC_ADDR_SHIFT		(7)
/*================================= TYEPDEFS         =========================*/

enum NWK_BROADCAST_ADDR{
	nwk_broadcast_all_Pan_devices	= 0xffff,
	nwk_broadcast_Rx_when_idle		= 0xfffd,
	nwk_broadcast_router_and_Cord	= 0xfffc,
	nwk_broadcast_low_pwr_router	= 0xfffb,
};	

typedef enum NWK_DEST_ADDR_MODE {
	NWK_Group_ADDR,
	NWK_network_ADDR,
}NWK_DstAddrMode;

typedef enum NWK_STATUS {
    NWK_SUCCESS                     = 0x00, ///< A request has been executed successfully
    NWK_INVALID_PARAMETER           = 0xC1, ///< Invalid argument passed to function
    NWK_INVALID_REQUEST             = 0xC2, ///< Upper layer requested service that cannot be performed
    NWK_NOT_PERMITTED               = 0xC3, ///< Join request not allowed
    NWK_STARTUP_FAILURE             = 0xC4, ///< Network formation request failed
    NWK_ALREADY_PRESENT             = 0xC5, ///< Device requesting direct join is already in nbor tbl
    NWK_SYNC_FAILURE                = 0xC6, ///< Sync request has failed
    NWK_TABLE_FULL                  = 0xC7, ///< Join request failed because nbor table full
    NWK_UNKNOWN_DEVICE              = 0xC8, ///< Leave request failed because device not in nbor tbl
    NWK_UNSUPPORTED_ATTRIBUTE       = 0xC9, ///< NIB request failed get/set
    NWK_NO_NETWORKS                 = 0xCA, ///< Join request issued where no networks available
    NWK_MAX_FRM_CNTR                = 0xCC, ///< Security failed because frame counter hit max val
    NWK_NO_KEY                      = 0xCD, ///< Security failed because no key available
    NWK_BAD_CCM_OUTPUT              = 0xCE, ///< Security failed because security engine error
    NWK_NO_ROUTING_CAPACITY         = 0xCF, ///< Discover route failed due to lack of routing or disc tbl entries
    NWK_ROUTE_DISC_FAILED           = 0xD0, ///< Discover route failed due to any other reason
    NWK_ROUTE_ERROR                 = 0xD1, ///< Data transmit request failed due to routing failure on other device
    NWK_BT_TBL_FULL                 = 0xD2, ///< Broadcast failed due to no room in broadcast table
    NWK_FRAME_NOT_BUFFERED          = 0xD3  ///< Data transmit request failed due to lack of pending entries
}nwk_status_t;

typedef enum NWK_ADDR_MODE {
	NWK_NO_ADDRESS = 0x00,
	NWK_none = 0x01,
	NWK_SHORT_ADDRESS = 0x02,
	NWK_LONG_ADDRESS = 0x03,
}nwk_addrMode_t;

typedef enum NWK_STATUS_CODE{
	NWK_NO_ROUTE_AVAILABLE 			= 0x00,
	NWK_TREE_LINK_FAILURE 			= 0x01,
	NWK_NON_TREE_LINK_FAILURE 		= 0x02,
	NWK_LOW_BATTERY_LEVEL 			= 0x03,
	NWK_NO_ROUTING_CAP 				= 0x04,
	NWK_NO_INDIRECT_CAPACITY 		= 0x05,
	NWK_INDIRECT_TRANSACTION_EXPIRY = 0x06,
	NWK_TARGET_DEVICE_UNAVAIL 		= 0x07,
	NWK_TARGET_ADDREESS_UNALLOCATED = 0x08,
	NWK_PARENT_LINK_FAILURE 		= 0x09,
	NWK_VALIDATE_ROUTE 				= 0x0a,
	NWK_SOURCE_ROUTE_FAILURE 		= 0x0b,
	NWK_MANY_TO_ONE_ROUTE_FAILURE 	= 0x0c,
	NWK_ADDRESS_CONFLICT 			= 0x0d,
	NWK_VERIFY_ADDRESSES 			= 0x0e,
	NWK_PANid_UPDATE 				= 0x0f,
	NWK_NETWORK_ADDR_UPDATE 		= 0x10,
	NWK_BAD_FRAME_COUNTER 			= 0x11,
	NWK_BAD_KEY_SEQ_NUM 			= 0x12,
}nwk_status_code_t;



typedef struct NWK_ADDR_MAP{
//	nwk_addr_map_t	*next;
	uint64_t		LongAddr;
	uint16_t 		ShortAddr;
}nwk_addr_map_t;

typedef struct NWK_PATH{
	uint16_t		addr;
	//nwk_path_t *next;
}nwk_path_t;

typedef struct NWK_ROUTE_ENTRY{
	uint16_t 	addr;
	uint16_t	count;
	nwk_path_t	path;
}nwk_route_t;

typedef enum FRAME_TYPE{
	NWK_DATA 	= 0x00,
	NWK_COMMAND = 0x01,
}nwk_frame_type_t;

typedef enum NWK_DISCOVER_ROUTE {
	SUPPRESS_DISCOVER,
	ENABLE_DISCOVER,
//	reserved1,
//	reserved2,
}NWK_discover_rt_t;

typedef enum MMF_VALUE{
	MMF_non_mem,
	MMF_mem,
//	reserved1,
//	reserved2,
}mmf_value_t;

typedef enum REJOIN_NETWORK{
	JOINED_THRU_ASSOC = 0x00,
	JOINED_DIRECTLY = 0x01,
	JOINED_NWK_REJOIN = 0x02,
}nwk_rejoinNet_t;

typedef struct NWK_NIB{
	uint8_t		nwkSequenceNumber;
	uint16_t	nwkPassiveAckTimeout;
	uint8_t 	nwkMaxBroadcastRetries;
	uint8_t		nwkMaxChildren;
	uint8_t		nwkMaxDepth;
	uint8_t		nwkMaxRouters;
	uint8_t		*nwkNeighborTable;
	uint8_t		nwkNetworkBroadcastDeliveryTime;
	bool		nwkReportConstantCost;
	uint8_t		nwkRouteDiscoveryRetriesPermitted;
	uint8_t		*nwkRouteTable;
	bool		nwkSymLink;
	uint8_t		nwkCapabilityInfo;
	uint8_t		nwkAddrAlloc;
	uint8_t		nwkUseTreeRouting;
	addr_t		nwkManagerAddr;
	uint8_t		nwkMaxSourceRoute;
	uint8_t		nwkUpdateId;
	uint16_t	nwkTransactionPersistenceTime;
	addr_t		nwkNetworkAddress;
	uint8_t		nwkStackProfile;
	uint8_t		*nwkBroadcastTransactionTable;
	uint64_t	nwkExtendedPANid;
	uint8_t		nwkUseMulticast;
	uint8_t		*nwkRouteRecordTable;
	uint8_t		nwkIsConcentrator;
	uint8_t		nwkConcentratorRadius;
	uint8_t		nwkConcentratorDiscoveryTime;
	uint8_t		nwkSecurityLevel;
	uint8_t		nwksecurityMaterialSet;
	uint8_t		nwkActivekeySeqNumber;
	uint8_t		nwkAllFresh;
	uint8_t		nwkSecureAllFrames;
	uint8_t		nwkLinkStatusPeriod;
	uint8_t		nwkRouterAgeLimit;
	uint8_t		nwkUniqueAddr;
	addr_t		*nwkAddressMap;
	uint8_t		nwkTimeStamp;
	uint16_t	nwkPANid;
	uint16_t	nwkTxTotal;


}nwk_nib_t;

START_PACK
typedef struct PACK NWK_FCF{
	COMBINE(3, (
	uint8_t 	NWK_frame_type: 2,
	uint8_t 	NWK_protocol_ver: 4,
	uint8_t 	NWK_discover_rt: 2))
	COMBINE(6, (
	uint8_t	NWK_multicast: 1,
	uint8_t	NWK_security: 1,
	uint8_t	NWK_source_rt: 1,
	uint8_t	NWK_dest_IEEE: 1,
	uint8_t	NWK_source_IEEE: 1,
	uint8_t	NWK_RESERVE: 3))
}nwk_fcf_t;
END_PACK

START_PACK
typedef struct PACK NWK_MULTICAST_CONTROL{
	COMBINE(3, (
	uint8_t		multicastMode: 2,
	uint8_t		nonmemberRadius: 3,
	uint8_t		maxNonmemberRadius: 3))
}nwk_multicastControl_t;
END_PACK

typedef struct nlde_data_t{
	addr_mode_t		 	dstAddrMode;
	addr_t				dstAddr;
	uint8_t				NsduLength;
	uint8_t				*nsdu;
	uint8_t				NsduHandle;
	uint8_t				radius;
	uint8_t				nonMemRadius;
	uint8_t				DiscoverRoute; //TODO change to dhte union for discover route
	uint8_t				SecuityEnabled; //TODO it is called out to be boolean
}nlde_data_t;

typedef struct NWK_DISCRIPTOR{
	uint64_t 	extendPANid;
	uint8_t 	logicalChannel;
	uint8_t		stackProfile;
	uint8_t		zigbeeVersion;
	uint8_t 	beaconOrder;
	uint8_t		superframeOrder;
	uint8_t		permitJoining;
	uint8_t		routerCapacity;
	uint8_t		endDeviceCapacity;
	struct NWK_DISCRIPTOR *next;
	struct NWK_DISCRIPTOR *prev;
}nwk_discript_t;

typedef struct NWK_NET_DISCOV{
	nwk_status_t 			status;
	uint8_t					count;
	nwk_discript_t			*first;
}nwk_netDisc_t;



typedef struct NWK_srcRoute
{
	uint8_t relay_cnt;
	uint8_t relay_index;
	short_addr_t relayList[10];//TODO: I need to have a max relay list constant	
}nwk_srcRoute_t;

typedef struct NPDU{
	nwk_fcf_t 				fcf;
	addr_t	 				destination;
	addr_t 					source;
	uint64_t				destExtAddr;
	uint8_t  				radius;
	uint8_t  				sequence_num;
	nwk_multicastControl_t 	multicast_control;
	nwk_srcRoute_t  		src_route;
}npdu_t;

typedef struct NWK_BEACON{
	uint8_t 	protocolID;
	uint8_t		stackProf;
	uint8_t		protocolVer;
	uint8_t		routerCap;
	uint8_t		devDepth;
	uint8_t		endDevCap;
	uint64_t	extendedPANid;
	uint64_t	txOffset;
	uint8_t		nwkUpdateId;
}nwk_beacon_t;

START_PACK
typedef struct PACK NWK_CAP_INFO{
	COMBINE(7, (
	uint8_t 	altPanCoord: 1,
	uint8_t		devType: 1,
	uint8_t		powerSource: 1,
	uint8_t		recWhenIdle: 1,
	uint8_t		reserved2: 2,
	uint8_t		secEnabled: 1,
	uint8_t		allocAddr: 1))
}nwk_capInfo_t;
END_PACK


typedef struct NWK_JOIN{
	uint64_t		extedPANid;
	nwk_rejoinNet_t	rejoinNetwork;
	uint32_t		scanChannels;
	uint8_t			duration;
	nwk_capInfo_t	capabilityInfo;
	uint8_t			securityEnabled;
}nwk_join_t;
/*================================= GLOBAL VARIABLES =========================*/

/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/
nwk_status_t NWK_nlde_data(zig_frame_t);
void NWK_frame_construct(zig_frame_t);
uint8_t get_NWK_Sequence_num(void);

/*TODO:  I need to add the logic for responce to a data transmition
 * 	1. return INVAILD_REQUEST if I get this request when it is not accosiated.
 */

#endif /* NWK_H_ */
