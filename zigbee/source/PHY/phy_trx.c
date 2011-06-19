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

/*================================= INCLUDES         =========================*/

#include "frame.h"

#include "PHY/phy.h"

#include "phy/rc_rf230.h"
#include "RF230/RF230.h"

#include "MAC/mac_prototypes.h"


/*================================= MACROS           =========================*/
/*================================= TYEPDEFS         =========================*/
/*================================= GLOBAL VARIABLES =========================*/
/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/
/*================================= SOURCE CODE      =========================*/


phy_data_status_t PD_DATA_request(uint8_t psduLen, uint8_t *psdu) {

	trx_state_t state = RF230_STATE();
	phy_data_status_t status;
	switch(state) 
	{
	/*Make sure we are not in TRX_OFF*/
		case(TRX_OFF):
			status = PHY_TRX_OFF;
		break;
	/*Make sure we are not in TX_BUSY*/
		case(BUSY_TX):
			status = PHY_BUSY_TX;
		break;
	/*build the PPDU frame out of the PSDU and send it to the transeiver
	  if the send fails then we are waiting for an acknowlegement in RX_ON */
		default:
		break;
	}
		/*TODO::: add logic to transform PSDU to PPDU*/
	if(rc_send_frame(psduLen, psdu))
	{
		status = PHY_SUCCESS;
	}
	else 
	{
		status = PHY_RX_ON;
	}
	return status;
}


void make_ppdu_frame(void){


}


void PD_DATA_Indication(frame_t *fr) {
/* This where i ended on 9.10.10 I am trying to start receiving a message. */
//All this does is relay the message to the MAC....

	MAC_incomingFrame(fr);

}
