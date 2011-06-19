// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief
 *
 * \par Application note:
 *
 *
 * \par Documentation
 *
 *
 *
 * \author
 *
 *
 *
 * $Id:
 *
 * Copyright (c) 2008 ,
 *
 *
 *****************************************************************************/
#ifndef _MAC_H
#define _MAC_H
/*================================= INCLUDES         =========================*/


#include "frame.h"

#include "PHY/phy.h"

#include "misc/security.h"
/*================================= MACROS           =========================*/


#define aBaseSlotDuration				(60)
#define aExtendedAddress				(0x00000000FF17EFDE)
#define aGTSDescPersistenceTime			(4)
#define aMaxBeaconOverhead				(75)
#define aMaxLostBeacons					(4)
#define aMaxMPDUUnsercuredOverhead		(25)
#define aMaxSIFSFrameSize				(18)
#define aMinCAPLength					(440)
#define aMinMPDUOverhead				(9)
#define aNumSuperframeSlots				(16)
#define aUnitBackoffperiod				(20)
#define aBaseSuperframeDuration			(960)
#define aMaxBeaconPayloadLength			(aMaxPHYPacketSize - aMaxBeaconOverhead)
#define aMaxMACSafePayloadSize			(aMaxPHYPacketSize - aMaxMPDUUnsecuredOverhead)
#define aMaxMACPayloadSize				(aMaxPHYPacketSize - aMinMPDUOverhead)
#define	aMicroSecPerSymbol				(4)

#define MAC_ACK_TRANS_NOT_UNACK_TRANS			(0)
#define MAC_GTS_TRANS_NOT_CAP_TRANS				(1)
#define MAC_INDIRECT_TRANS_NOT_DIRECT_TRANS		(2)

#define aMaxMacPayloadSize				(25)

#define MAC_FCF_FRAME_TYPE_SHIFT			(0)
#define MAC_FCF_SEC_ENABLE_SHIFT			(3)
#define MAC_FCF_FRAME_PENDING_SHIFT			(4)
#define MAC_FCF_ACK_REQUEST_SHIFT			(5)
#define MAC_FCF_PAN_ID_COMPRESS_SHIFT		(6)
#define MAC_FCF_DEST_ADDR_MODE_SHIFT		(10)
#define MAC_FCF_FRAME_VERSION_SHIFT			(12)
#define MAC_FCF_SRC_ADDR_MODE_SHIFT			(14)

#define MAC_SUPERFRAME_ASSOC_PERMIT_SHIFT	(15)
#define MAC_SUPERFRAME_PAN_COORD_SHIFT		(14)
#define MAC_SUPERFRAME_BATT_EX_SHIFT		(12)
#define MAC_SUPERFRAME_CAP_SLOT_SHIFT		(8)
#define MAC_SUPERFRAME_FRAME_ORDER_SHIFT	(4)
#define MAC_SUPERFRAME_BEACON_ORDER_SHIFT	(0)
//#define MAC_SCAN_DELAY(uint8_t duration)	(((aBaseSuperframeDuration << duration) + aBaseSuperframeDuration))
/*================================= TYEPDEFS         =========================*/





typedef enum DISASSOC_REASON{
	COORD_WISHES_DEVICE_TO_LEAVE = 0x01,
	DEV_WISHES_TO_LEAVE = 0x02,
}mac_disassoc_reason_t;


typedef enum MAC_STATUS {
	MAC_SUCCESS = 0x00,
	MAC_BEACON_LOSS = 0xE0,
	MAC_ACCESS_FAILURE = 0xE1,
	MAC_COUNTER_ERROR = 0xDB,
	MAC_DENIED = 0xE2,
	MAC_DISABLE_TRX_FAILURE = 0xE3,
	MAC_FRAME_TOO_LONG = 0xE5,
	MAC_IMPROPER_KEY_TYPE = 0xDC,
	MAC_IMPROPER_SECURITY_LEVEL = 0xDD,
	MAC_INVALID_ADDRESS = 0xF5,
	MAC_INVALID_GTS = 0xE6,
	MAC_INVALID_HANDLE = 0xE7,
	MAC_INVALID_INDEX = 0xF9,
	MAC_INVAILD_PARAMETER = 0xE8,
	MAC_LIMIT_REACHED = 0xFA,
	MAC_NO_ACK = 0xE9,
	MAC_NO_BEACON = 0xEA,
	MAC_NO_DATA = 0xEB,
	MAC_NO_SHORT_ADDRESS = 0xEC,
	MAC_ON_TIME_T00_LONG = 0xF6,
	MAC_OUT_OF_CAP = 0xED,
	MAC_PAN_ID_CONFLICT = 0xEE,
	MAC_PAST_TIME = 0xF7,
	MAC_READ_ONLY = 0xFB,
	MAC_REALIGNMENT = 0xEF,
	MAC_SCAN_IN_PROGRESS = 0xFC,
	MAC_SECURITY_ERROR = 0xE4,
	MAC_SUPERFRAME_OVERLAP = 0xFD,
	MAC_TRACKING_OFF = 0xF8,
	MAC_TRANSACTION_EXPIRED = 0xF0,
	MAC_TRANSACTION_OVERFLOW = 0xF1,
	MAC_TX_ACTIVE = 0xF2,
	MAC_UNAVAILABLE_KEY = 0xF3,
	MAC_UNSUPPORTED_ATTRIBUTE = 0xF4,
	MAC_UNSUPPORTED_LEGACY = 0xDE,
	MAC_UNSUPPORTED_SECURITY = 0xDF,
	MAC_INIT = 0xFF,

}mac_status_t;

typedef enum {
	MAC_BEACON = 0x00,
	MAC_DATA = 0x01,
	MAC_ACK = 0x02,
	MAC_COMMAND = 0x03,
}mac_frame_type_t;

typedef enum MAC_ADDR_MODE {
	MAC_NO_ADDRESS = 0x00,
	MAC_none = 0x01,
	MAC_SHORT_ADDRESS = 0x02,
	MAC_LONG_ADDRESS = 0x03,
}MAC_AddrMode_t;

typedef enum FRAME_VER{
	MAC_COMPATIBLE_WITH_802_15_4_2003 = 0x00,
	MAC_NOT_COMPATIBLE_WITH_802_15_4_2003 = 0x01,
}frame_ver_t;

typedef enum MAC_SEC_LEVEL{
	MAC_sec_none,//TODO: needs to be added currently I am only using 0x00 meaning none: look at section 7.6.2.2.1 in 802.15.4 Spec
}mac_sec_level_t;

typedef enum MAC_FILTER{
	NOT_FILTERED = 0x00,
	level1 = 0x01,
	level2 = 0x02,
	level3 = 0x03,
	level4 = 0x04,
	level5 = 0x05,
	level6 = 0x06,
	level7 = 0x07,
	level8 = 0x08,
	level9 = 0x09,
	FILTERED = 0x0a,
}mac_filter_t;

typedef enum MAC_PIB_ATTR{
	macAckWaitDuration = 0x40,
	macAssociatedPANCoord = 0x56,
	macAssociationPermit = 0x41,
	macAutoRequest = 0x42,
	macBattLifeExt = 0x43,
	macBattLifeExtPeriods = 0x44,
	macBeaconPayload = 0x45,
	macBeaconPayloadLength = 0x46,
	macBeaconOrder = 0x47,
	macBeaconTxTime = 0x48,
	macBSN = 0x49,
	macCoordExtendedAddress = 0x4a,
	macCoordShortAddress = 0x4b,
	macDSN = 0x4c,
	macGTSPermit = 0x4d,
	macMaxBE = 0x57,
	macMaxCSMABackoffs = 0x4e,
	macMaxFrameTotalWaitTime = 0x58,
	macMaxFrameRetries = 0x59,
	macMinBE = 0x4f,
	MACMinLIFSPeriod = 0x70,
	macMinSIFSPeriod = 0x71,
	macPANid = 0x50,
	macPromiscuousMode = 0x51,
	macResponseWaitTime = 0x5a,
	macRxOnWhenIdle = 0x52,
	macSecurityEnabled = 0x5d,
	macShortAddress = 0x53,
	macSupeframeOrder = 0x54,
	macSyncSymbolOffset = 0x5b,
	macTimestampSupported = 0x5c,
	macTransactionPersistenceTime = 0x55,
}mac_pib_attr_t;

typedef union MAC_VALUE{
	uint16_t	macAckWaitDuration;
	bool		macAssociatedPANCoord;
	bool		macAssociationPermit;
	bool 		macAutoRequest;
	bool		macBattLifeExt;
	uint8_t 	macBattLifeExtPeriods;
	uint8_t		*macBeaconPayload;
	uint8_t		macBeaconPayloadLength;
	uint8_t		macBeaconOrder;
	uint32_t	macBeaconTxTime;
	uint8_t		macBSN;
	uint64_t	macCoordExtendedAddress;
	uint16_t	macCoordShortAddress;
	uint8_t		macDSN;
	bool		macGTSPermit;
	uint8_t		macMaxBE;
	uint8_t		macMaxCSMABackoffs;
	uint8_t		macMaxFrameTotalWaitTime;
	uint8_t		macMaxFrameRetries;
	uint8_t		macMinBE;
	uint8_t		macMinLIFSPeriod;
	uint8_t		macMinSIFSPeriod;
	uint16_t	macPANid;
	bool		macPromiscuousMode;
	uint8_t		macResponseWaitTime;
	bool		macRxOnWhenIdle;
	bool		macSecurityEnabled;
	uint16_t	macShortAddress;
	uint8_t		macSupeframeOrder;
	uint16_t	macSyncSymbolOffset;
	bool		macTimestampSupported;
	uint16_t	macTransactionPersistenceTime;
}mac_pib_value_t;

typedef union ADDR_TYPE{
	MAC_AddrMode_t 	mode;
	uint8_t 		addr[8];
	uint8_t 		PANid[2];
}mac_addr_t;

typedef struct {//not sure if I need this
	uint8_t 	short_addr_pending;
	uint8_t		long_addr_pending;

}pending_addr_t;
START_PACK
typedef struct PACK MAC_FCF{
	COMBINE(6, (
	uint8_t 	MAC_fcf_Frame_Type: 3,
	uint8_t 	MAC_fcf_Sec_enabled: 1,
	uint8_t 	MAC_fcf_Frame_Pending: 1,
	uint8_t 	MAC_fcf_Ack_Request: 1,
	uint8_t		MAC_fcf_PANid_Compression: 1,
	uint8_t		res1: 1))
	COMBINE(4, (
	uint8_t	res2: 2,
	uint8_t		MAC_fcf_DstAddr_Mode: 2,
	uint8_t		MAC_fcf_Frame_Ver: 2,
	uint8_t		MAC_fcf_SrcAddr_Mode: 2))
}mac_fcf_t;
END_PACK

START_PACK
typedef struct PACK MAC_CAPIBILITIES
{
	COMBINE(7, (
	uint8_t		alt_PAN_coord:1,
	uint8_t		device_type:1,
	uint8_t		pwr_src:1,
	uint8_t		Rx_on_idle:1,
	uint8_t		resrv:2,
	uint8_t		sec_capib:1,
	uint8_t		alloc_addr:1))	
}mac_capibilities_t;
END_PACK

typedef struct MCPS_DATA{
	mac_addr_t		MAC_dstAddr;
	uint8_t			MAC_srcPANid[2];
	uint8_t 		msduLength;
	uint8_t 		*msdu; //TODO: I need to use a declaration other than uint8_t but not sure what(I have the same problem on other layers)
	uint8_t 		MAC_handle;
	uint8_t			MAC_TxOptions;
	mac_sec_level_t	MAC_securityLevel;//TODO: needs to be added currently I am only using 0x00 meaning none: look at section 7.6.2.2.1 in 802.15.4 Spec
	uint8_t			MAC_KeyIdMode;//TODO: needs to be added look at section 7.6.2.2.2 in 802.15.4 Spec
	uint8_t			MAC_KeySource;//''
	uint8_t			MAC_KeyIndex;//	''
}mcps_data_t;

typedef struct MLME_ASSOC{
	uint8_t			LogicalChannel;
	uint8_t			ChannelPage;
	addr_t			Coord;
	uint8_t			CapabilityInfo;
	uint8_t			SecurityLevel;
	uint8_t			KeyIDMode; // TODO: I need to add the proper info here
	uint8_t			KeySource; // TODO: I need to add the proper info here
	uint8_t			KeyIndex; //TODO: I need to add the proper info here
}mlme_assoc_t;

typedef struct MLME_DISASSOC{
	uint64_t	DeviceAddr;
	uint8_t		DisassocReason;
	uint8_t		SecurityLevel;
	uint8_t		KeyIdMode;
	uint8_t		keyIndex;
}mlme_disassoc_t;

typedef struct MPDU{// This should be the data type for msdu(I have the same problem on other layers)
	mac_fcf_t 	fcf;
	uint8_t 	seq_num;
	addr_t		destination;
	addr_t		source;
	uint8_t 	len; //I may not need this...
	uint16_t 	crc;//TODO: initial development will have the transceiver generate CRC
	uint8_t		payload[aMaxMacPayloadSize];
	uint8_t 	*ptr;
	security_t  sec;
}mpdu_t;


typedef struct MSDU{
	uint8_t *ptr;
	uint8_t length;
	uint8_t data[128];
}msdu_t;

typedef struct MAC_PIB{
	uint32_t	macAckWaitDuration;
	bool		macAssociatedPANCoord;
	bool		macAssociationPermit;
	bool 		macAutoRequest;
	bool		macBattLifeExt;
	uint8_t 	macBattLifeExtPeriods;
	uint8_t		*macBeaconPayload;
	uint8_t		macBeaconPayloadLength;
	uint8_t		macBeaconOrder;
	uint32_t	macBeaconTxTime;
	uint8_t		macBSN;
	addr_t		macCoordExtendedAddress;
	addr_t		macCoordShortAddress;
	uint8_t		macDSN;
	bool		macGTSPermit;
	uint8_t		macMaxBE;
	uint8_t		macMaxCSMABackoffs;
	uint8_t		macMaxFrameTotalWaitTime;
	uint8_t		macMaxFrameRetries;
	uint8_t		macMinBE;
	uint8_t		macMinLIFSPeriod;
	uint8_t		macMinSIFSPeriod;
	uint16_t	macPANid;
	bool		macPromiscuousMode;
	uint32_t	macResponseWaitTime;
	bool		macRxOnWhenIdle;
	bool		macSecurityEnabled;
	addr_t		macShortAddress;
	addr_t		macLongAddress;
	uint8_t		macSupeframeOrder;
	uint16_t	macSyncSymbolOffset;
	bool		macTimestampSupported;
	uint16_t	macTransactionPersistenceTime;
}mac_pib_t;



typedef struct MAC_SUPERFRAME{
	uint8_t		superframeOrder;
	uint8_t		beaconOrder;
	uint8_t		capSlot;
	uint8_t		assocPermit;
	uint8_t		panCoord;
	uint8_t		battLifeExt;
}mac_superframe_t;

typedef struct PAN_DESCRIPTOR{
	addr_t				Coord;
	uint8_t				LogicalChannel;
	uint8_t				ChannelPage;
	mac_superframe_t	SuperframeSpec;//TODO: I need to do more research and figure this out????
	uint8_t				GTSPermit;//TODO: I might make this boolean
	uint8_t				LinkQuality;
	uint32_t			Timestamp;
	uint8_t				SecurityFailure;//TODO: I need to make this an enum when i get security started
	mac_sec_level_t 	SecurityLevel;
	uint8_t				KeyIdMode;
	uint8_t				KeySource; //TODO: I need to fix to be a union to
	uint8_t		 		KeyIndex;
}mac_pan_descriptor_t;

typedef struct MAC_BEACON{
	uint8_t					BSN;
	mac_pan_descriptor_t	pan_desc;
	uint8_t					pend_addr;//TODO: look into what to do with this... I am not sure i want to leave it an uint8
	uint16_t				AddrList;//TODO: this is not right and i will need to fix this..............I am not sure what it is.
	uint8_t					sduLength;
	uint8_t					*sdu;
}mac_beacon_t;

typedef struct MAC_PIB_REQUEST{
	mac_pib_attr_t	attr;
	uint8_t			index;
}mac_pib_request_t;

typedef struct MAC_PIB_CONFIRM{
	mac_status_t 	status;
	mac_pib_attr_t	attr;
	uint8_t			index;
	mac_pib_value_t	value;
}mac_pib_confirm_t;

typedef struct MAC_ORPHAN{
	addr_t 		orphanAddr;
	uint8_t 	securityLevel;
	uint8_t 	KeyIdMode;
	uint8_t		KeySource;
	uint8_t		KeyIndex;
}mac_orphan_t;


/*================================= GLOBAL VARIABLES =========================*/
typedef void (*trx_cb_t)(phy_trac_t);

//extern static Bool associated;
/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/
void MAC_setPanCoord(Bool coord);
Bool MAC_isPanCoord(void);
#endif
/* EOF */
