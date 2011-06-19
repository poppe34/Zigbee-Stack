/*
 * MAC_mlme_set.c
 *
 *  Created on: Nov 8, 2010
 *      Author: mpoppe
 */

#include <frame.h>
#include <MAC/mac_prototypes.h>


mac_status_t MAC_mlme_setReq(mac_pib_attr_t att, void *value){
	mac_pib_t *mpib = get_macPIB();
	mac_status_t status = MAC_SUCCESS;

	switch(att){

	case(macAckWaitDuration):
		mpib->macAckWaitDuration = *(uint32_t *)value;
	break;

	case(macAssociatedPANCoord):
		MAC_setCoordPANid(*(uint16_t *)value);
	break;
	case(macAssociationPermit):
		mpib->macAssociationPermit = *(uint8_t *)value;
	break;
	case(macAutoRequest):
		mpib->macAutoRequest = *(uint8_t *)value;
	break;
	case(macBattLifeExt):
		mpib->macBattLifeExt = *(uint8_t *)value;
	break;
	case(macBattLifeExtPeriods):
		mpib->macBattLifeExtPeriods = *(uint8_t *)value;
	break;
	case(macBeaconPayload):
		mpib->macBeaconPayload = value;
	break;
	case(macBeaconPayloadLength):
		mpib->macBeaconPayloadLength = *(uint8_t *)value;
	break;
	case(macBeaconOrder):
		mpib->macBeaconOrder= *(uint8_t *)value;
	break;
	case(macBeaconTxTime):
		mpib->macBeaconTxTime = *(uint32_t *)value;
	break;
	case(macBSN):
		mpib->macBSN= *(uint8_t *)value;
	break;
	case(macCoordExtendedAddress):
		MAC_setCoordLongAddr(*(uint64_t *)value);
	break;
	case(macCoordShortAddress):
		MAC_setCoordShortAddr(*(uint16_t *)value);
	break;
	case(macDSN):
		mpib->macDSN = *(uint8_t *)value;
	break;
	case(macGTSPermit):
		mpib->macGTSPermit = *(uint8_t *)value;
	break;
	case(macMaxBE):
		mpib->macMaxBE = *(uint8_t *)value;
	break;
	case(macMaxCSMABackoffs):
		mpib->macMaxCSMABackoffs = *(uint8_t *)value;
	break;
	case(macMaxFrameTotalWaitTime):
		mpib->macMaxFrameTotalWaitTime = *(uint8_t *)value;
	break;
	case(macMaxFrameRetries):
		mpib->macMaxFrameRetries = *(uint8_t *)value;
	break;
	case(macMinBE):
		mpib->macMinBE = *(uint8_t *)value;
	break;
	case(MACMinLIFSPeriod):
		mpib->macMinLIFSPeriod = *(uint8_t *)value;
	break;
	case(macMinSIFSPeriod):
		mpib->macMinSIFSPeriod = *(uint8_t *)value;
	break;
	case(macPANid):
		MAC_setPANid(*(uint16_t *)value);
	break;
	case(macPromiscuousMode):
		mpib->macPromiscuousMode = *(uint8_t *)value;
	break;
	case(macResponseWaitTime):
		mpib->macResponseWaitTime = *(uint32_t *)value;
	break;
	case(macRxOnWhenIdle):
		mpib->macRxOnWhenIdle = *(uint8_t *)value;
	break;
	case(macSecurityEnabled):
		mpib->macSecurityEnabled = *(uint8_t *)value;
	break;
	case(macShortAddress):
		MAC_setShortAddr(*(uint8_t *)value);
	break;
	case(macSupeframeOrder):
		mpib->macSupeframeOrder = *(uint8_t *)value;
	break;
	case(macSyncSymbolOffset):
		mpib->macSyncSymbolOffset = *(uint16_t *)value;
	break;
	case(macTimestampSupported):
		mpib->macTransactionPersistenceTime = *(uint8_t *)value;
	break;
	case(macTransactionPersistenceTime):
		mpib->macTransactionPersistenceTime = *(uint16_t *)value;
	break;
	}//end switch
	return status;
}//end MAC_mlme_setREQ

mac_pib_value_t MAC_mlme_getReq(mac_pib_attr_t att){
mac_pib_value_t value;
	mac_pib_t *mpib = get_macPIB();

	switch(att){

	case(macAckWaitDuration):
		value.macAckWaitDuration = mpib->macAckWaitDuration;
	break;
	case(macAssociatedPANCoord):
		value.macAssociatedPANCoord = mpib->macAssociatedPANCoord;
	break;
	case(macAssociationPermit):
		value.macAssociationPermit = mpib->macAssociationPermit;
	break;
	case(macAutoRequest):
		value.macAutoRequest = mpib->macAutoRequest;
	break;
	case(macBattLifeExt):
		value.macBattLifeExt = mpib->macBattLifeExt;
	break;
	case(macBattLifeExtPeriods):
		value.macBattLifeExtPeriods = mpib->macBattLifeExtPeriods;
	break;
	case(macBeaconPayload):
		value.macBeaconPayload = mpib->macBeaconPayload;
	break;
	case(macBeaconPayloadLength):
		value.macBeaconPayloadLength = mpib->macBeaconPayloadLength;
	break;
	case(macBeaconOrder):
		value.macBeaconOrder = mpib->macBeaconOrder;
	break;
	case(macBeaconTxTime):
		value.macBeaconTxTime = mpib->macBeaconTxTime;
	break;
	case(macBSN):
		value.macBSN = mpib->macBSN;
	break;
	case(macCoordExtendedAddress):
		value.macCoordExtendedAddress = mpib->macCoordExtendedAddress.extAddr;
	break;
	case(macCoordShortAddress):
		value.macCoordShortAddress = mpib->macCoordShortAddress.shortAddr;
	break;
	case(macDSN):
		value.macDSN = mpib->macDSN;
	break;
	case(macGTSPermit):
		value.macGTSPermit = mpib->macGTSPermit;
	break;
	case(macMaxBE):
		value.macMaxBE = mpib->macMaxBE;
	break;
	case(macMaxCSMABackoffs):
		value.macMaxCSMABackoffs = mpib->macMaxCSMABackoffs;
	break;
	case(macMaxFrameTotalWaitTime):
		value.macMaxFrameTotalWaitTime = mpib->macMaxFrameTotalWaitTime;
	break;
	case(macMaxFrameRetries):
		value.macMaxFrameRetries = mpib->macMaxFrameRetries;
	break;
	case(macMinBE):
		value.macMinBE = mpib->macMinBE;
	break;
	case(MACMinLIFSPeriod):
		value.macMinLIFSPeriod = mpib->macMinLIFSPeriod;
	break;
	case(macMinSIFSPeriod):
		value.macMinSIFSPeriod = mpib->macMinSIFSPeriod;
	break;
	case(macPANid):
		value.macPANid = mpib->macPANid;
	break;
	case(macPromiscuousMode):
		value.macPromiscuousMode = mpib->macPromiscuousMode;
	break;
	case(macResponseWaitTime):
		value.macResponseWaitTime = mpib->macResponseWaitTime;
	break;
	case(macRxOnWhenIdle):
		value.macRxOnWhenIdle = mpib->macRxOnWhenIdle;
	break;
	case(macSecurityEnabled):
		value.macSecurityEnabled = mpib->macSecurityEnabled;
	break;
	case(macShortAddress):
		value.macShortAddress = mpib->macShortAddress.shortAddr;
	break;
	case(macSupeframeOrder):
		value.macSupeframeOrder = mpib->macSupeframeOrder;
	break;
	case(macSyncSymbolOffset):
		value.macSyncSymbolOffset = mpib->macSyncSymbolOffset;
	break;
	case(macTimestampSupported):
		value.macTimestampSupported = mpib->macTransactionPersistenceTime;
	break;
	case(macTransactionPersistenceTime):
		value.macTransactionPersistenceTime = mpib->macTransactionPersistenceTime;
	break;
	}//end switch

	return value;
}
