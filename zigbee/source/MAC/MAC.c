// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief
 *
 * \par
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
 * $Id: 1284p_main
 *
 *
 *
 *
 *****************************************************************************/

/*================================= INCLUDES         =========================*/

#include "frame.h"

#include "alarms_task.h"

#include "PHY/rc_rf230.h"

#include "mac/mac.h"
#include "mac/MAC_conf.h"
#include "mac/mac_prototypes.h"
#include "MAC/MAC_mlme.h"

#include "conf_zigbee.h"
/*================================= MACROS           =========================*/
/*================================= TYEPDEFS         =========================*/

/*================================= GLOBAL VARIABLES =========================*/
static Bool associated = NO, panCoord = NO;

uint8_t MAC_seq_num;
static mac_pib_t macPIB;
mpdu_t mpdu;
mcps_data_t mcps;


/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/

/*	/brief	
 *
 */
/**
 * \brief This section configures the MAC sublayers default values.  
 *		
 * This section can be called to reset the MAC
 *
 * \param spi Base address of the SPI instance.
 *
 * \pre SPI device must be selected with spi_select_device() first
 *
 * \return Mac Status 
 */
mac_status_t mac_init(void) {

    MAC_seq_num = (uint8_t)rand();
	
	mac_status_t status = MAC_SUCCESS;
    associated = NO;
    uint64_t macCoordExtendedAddress = 0x0000000000000000;
    uint16_t macCoordShortAddress = 0xffff;
    uint16_t macCoordPANid = 0xffff;

    uint16_t macPANid = 0xffff;
    uint64_t macLongAddr = aExtendedAddress;
    uint16_t macShortAddr = 0xffff;

    MAC_setCoordShortAddr(macCoordShortAddress);
    MAC_setCoordLongAddr(macCoordExtendedAddress);
    MAC_setCoordPANid(macCoordPANid);

    MAC_setShortAddr(macShortAddr);
    MAC_setLongAddr(macLongAddr);
    MAC_setPANid(macPANid);

    macPIB.macAckWaitDuration = 84;//TODO: there is an equation to find this I need to add it.
    macPIB.macAssociatedPANCoord = NO;
    macPIB.macAutoRequest = YES;
    macPIB.macBattLifeExt = false;
    macPIB.macBattLifeExtPeriods = 20;//TODO: there is an equation to find this I need to add it.
    macPIB.macBeaconPayloadLength = 0;
    macPIB.macBeaconOrder = 15;
    macPIB.macBeaconTxTime = 0x00000000;
    macPIB.macBSN = (uint8_t)rand();//TODO: put a random equation on this
    macPIB.macDSN = (uint8_t)rand();//TODO: put a random equation on this
    macPIB.macGTSPermit = YES;
    macPIB.macMaxBE = 5;
    macPIB.macMaxCSMABackoffs = 4;
    macPIB.macMaxFrameTotalWaitTime = 40;//TODO: add the equation for this
    macPIB.macMaxFrameRetries = 3;
    macPIB.macMinBE = 0;
    macPIB.macMinLIFSPeriod = 20;//TODO: add the equation for this
    macPIB.macMinSIFSPeriod = 20;//TODO: add the equation for this
    macPIB.macPromiscuousMode = NO;
    macPIB.macResponseWaitTime = 32;
    macPIB.macRxOnWhenIdle = NO;
    macPIB.macSecurityEnabled = false;
	macPIB.macShortAddress.mode = SHORT_ADDRESS;
	macPIB.macLongAddress.mode = LONG_ADDRESS;
	macPIB.macCoordShortAddress.mode = SHORT_ADDRESS;
	macPIB.macCoordExtendedAddress.mode = LONG_ADDRESS;
    macPIB.macSupeframeOrder = 15;
    macPIB.macSyncSymbolOffset = 0x0050;//TODO: add the equation for this
    macPIB.macTimestampSupported = true;
    macPIB.macTransactionPersistenceTime = 0x01f4;

    MAC_setCurrentChannel(DEFAULT_CHANNEL);

//	TODO:	the following arguments need to be moved to a better location.
	turn_ON_CRC();
	if(ioport_pin_is_high(ZIGBEE_COORD_GPIO))
	{
		MAC_mlme_startReq();
		MAC_setLongAddr(0x0000222388894343);
		MAC_setShortAddr(0x000);
		panCoord = YES;
		macPIB.macAssociatedPANCoord = YES;
	}
	else
	{
		I_AM_COORD(NO);
	}
	set_MIN_BE(macPIB.macMinBE);

//	RF230registerBitWrite(SR_AACK_SET_PD, 0x01);



//    status = RF230BitRead(SR_TRAC_STATUS);
	
	set_trx_state(RX_AACK_ON, NO);
	mac_status_t state = RF230_STATE();
	alarm_new(9, "TRX status during MAC init is: %x", state);
	
	return status;
}

uint8_t get_MAC_seqNum(void){
	return (MAC_seq_num++);
}

mac_pib_t *get_macPIB(void){
	return &macPIB;
}
mpdu_t *get_macMPDU(void){
	return &mpdu;
}
mcps_data_t *get_macMCPS(void){
	return &mcps;
}

void MAC_setPANid(uint16_t pan){

	macPIB.macShortAddress.PANid = pan;

	macPIB.macLongAddress.PANid = pan;

	macPIB.macPANid = pan;

	set_PANid(pan);
}

void MAC_setShortAddr(uint16_t addr)
{
	macPIB.macShortAddress.shortAddr = addr;
	set_shortAddr(addr);
}

void MAC_setCurrentChannel(uint8_t chan)
{
	phy_pib_t *ppib = get_phyPIB();

	set_currentChannel(chan);
	ppib->phyCurrentChannel = chan;
}

void MAC_setLongAddr(uint64_t addr){
	macPIB.macLongAddress.extAddr = addr;
	set_IEEE_ADDR(addr);
}
void MAC_setCoordPANid(uint16_t pan){
	macPIB.macCoordShortAddress.PANid = pan;

	macPIB.macCoordExtendedAddress.PANid = pan;
}

void MAC_setCoordShortAddr(uint16_t addr){
	 macPIB.macCoordShortAddress.shortAddr = addr;
}
void MAC_setCoordLongAddr(uint64_t addr){
	macPIB.macCoordExtendedAddress.extAddr = addr;

}
Bool MAC_isAssoc(void)
{
	return associated;
}
void MAC_setAssoc(Bool value)
{
	associated = value;
	macPIB.macAssociatedPANCoord = value;
}

Bool MAC_isPanCoord(void)
{
	return(panCoord);
}

void MAC_setPanCoord(Bool coord)
{
	panCoord = coord;
}