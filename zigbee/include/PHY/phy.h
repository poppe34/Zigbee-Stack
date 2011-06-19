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
#ifndef _PHY_H
#define _PHY_H
/*================================= INCLUDES         =========================*/
#include "compiler.h"

#include "MAC/mac.h"

/*================================= MACROS           =========================*/
#define		aMaxPHYPacketSize	(127)
#define		aTurnaroundTime		(12)
#define 	PLL_LOCK  			(0)
#define		PLL_UNLOCK			(1)
#define		RX_START 			(2)
#define		TRX_END  			(3)
#define		TRX_UR  			(0x40)
#define		BAT_LOW 			(0x80)


/*================================= TYEPDEFS         =========================*/

typedef uint8_t trx_state;

typedef enum {
	P_ON							= 0x00,
	BUSY_RX							= 0x01,
	BUSY_TX							= 0x02,
	RX_ON							= 0x06,
    FORCE_TRX_OFF                   = 0x07, //not a part of the defined states add for convince
	TRX_OFF							= 0x08,
	PLL_ON							= 0x09,
	TRX_SLEEP						= 0x0F,
	BUSY_RX_AACK					= 0x11,
	BUSY_TX_ARET					= 0x12,
	RX_AACK_ON						= 0x16,
	TX_ARET_ON						= 0x19,
	RX_ON_NOCLK						= 0x1C,
	RX_AACK_ON_NOCLK				= 0x1D,
	BUSY_RX_AACK_NOCLK				= 0x1E,
	STATE_TRANSITION_IN_PROGRESS	= 0x1F,
}trx_state_t;

typedef enum {

    mgmt_TRX

}temp_t;

typedef enum {

	cca_ed,
	cca_carrier_sence,
	cca_cs_ed

}cca_mode_t;

typedef enum {

	PHY_SUCCESS,
	PHY_RX_ON,
	PHY_TRX_OFF,
	PHY_BUSY_TX,

}phy_data_status_t;

typedef enum {

    CCA_TRX_OFF,
    CCA_BUSY,
    CCA_IDLE,

}cca_status_t;

typedef enum {

    ED_SUCCESS,
    ED_TRX_OFF,
    ED_TX_ON,

}ed_status_t;

typedef struct {

    ed_status_t status;
    uint8_t level;

}ed_request_t;

typedef enum {
	
	req_success,
	req_unsupported,

}phy_pib_status_t;

typedef enum {
	TRAC_INVALID = 0x07,
	TRAC_NO_ACK = 0x05,
	TRAC_CHANNEL_ACCESS_FAILURE = 0x03,
	TRAC_SUCCESS_DATA_PENDING = 0x01,
	TRAC_SUCCESS = 0x00,
}phy_trac_t;

typedef struct PHY_PIB{

    uint8_t 	phyCurrentChannel;
    uint32_t	phyChannelsSuppported[32];
    uint8_t		phyTransmitPower;
    cca_mode_t 	phyCCAMode;
   	uint8_t 	phyCurrentPage;
    uint8_t 	phyMaxFrameDuration;
    uint8_t 	phySHRDuration;
    float 		phySymbolsPerOctet;

}phy_pib_t;


typedef enum {
    phyCurrentChannel = 0x00,
    phyChannelsSupported = 0x01,
    phyTransmitPower = 0x02,
    phyCCAMode = 0x03,
    phyCurrentPage = 0x04,
    phyMaxFrameDuration = 0x05,
    phySHRDuration = 0x05,
    phySymbolsPerOctet = 0x06,

}phy_pib_att_t;

typedef struct {

	phy_pib_status_t status;
	phy_pib_att_t attribute;
	phy_pib_t value;
	
}phy_pib_request_t;



/*================================= CONSTANTS		 =========================*/

#define aMaxPHYPacketSize		(127)
#define aTurnaroundTime         (12)

/*================================= GLOBAL VARIABLES =========================*/

/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/

//bool set_trx_state(trx_state_t state, bool force);
phy_data_status_t PD_DATA_request(uint8_t psduLen, uint8_t *psdu);
bool set_currentChannel(uint8_t channel);
void rc_goto_sleep(void);
void rc_wakeup(void);
uint8_t get_currentChannel(void);
bool set_trx_state(trx_state_t state, bool force);
bool trx_state_request(trx_state_t state);
ed_request_t ed_request(void);
cca_status_t phy_CCA();
phy_pib_request_t PIB_request(phy_pib_att_t pib);
bool set_auto_CRC_on(void);
bool set_auto_CRC_off(void);
uint16_t get_CSMA_seed(void);
uint8_t get_rc_CLKM(void);
uint8_t get_auto_CRC(void);
uint16_t get_PANid(void);
void phy_init(void);
phy_pib_t *get_phyPIB(void);
void PD_DATA_Indication(frame_t *fr);
bool set_padIOPwrLevel(uint8_t level);
uint8_t get_padIOPwrLevel(void);
#endif
