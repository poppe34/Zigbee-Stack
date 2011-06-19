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
#include "compiler.h"
#include "frame.h"

#include "alarms_task.h"

#include "MAC/mac_prototypes.h"
#include "MAC/mac.h"
#include "MAC/MAC_mcps.h"

#include "MAC/MAC_NWK_binding.h"

#include "PHY/phy.h"

uint8_t temp = 0;

/*================================= MACROS           =========================*/
/*================================= TYEPDEFS         =========================*/
/*================================= GLOBAL VARIABLES =========================*/
uint8_t MACreceiveBeaconOnly = 0x00;
/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/
/*================================= SOURCE CODE      =========================*/

void MAC_mcps_dataReq(mpdu_t *mpdu, frame_t *fr)
{
	MAC_createFrame(mpdu, fr);
	MAC_setTxCB(&MAC_mcps_dataReq_cb);
	
	frame_sendWithFree(fr);	
}

void MAC_mcps_dataInd(mpdu_t *mpdu, frame_t *fr)
{
	alarm_new(9, "Rx a MAC data Ind");
	//NWK_nlde_dataHandler(mpdu, fr);	
	
}//end MAC_DATA_Indication
void MAC_mcps_dataReq_cb(phy_trac_t status)
{
	switch(status)
	{
		case(TRAC_SUCCESS):
			MAC_mcps_dataConf(MAC_SUCCESS);
		break;

		case(TRAC_NO_ACK):
			MAC_mcps_dataConf(MAC_NO_ACK);
		break;

		case(TRAC_CHANNEL_ACCESS_FAILURE):
			MAC_mcps_dataConf(MAC_ACCESS_FAILURE);
		break;

		case(TRAC_INVALID):
			MAC_mcps_dataConf(MAC_INVALID_ADDRESS);
		break;

		case(TRAC_SUCCESS_DATA_PENDING):
			break;
	}		
}
void MAC_mcps_dataConf(mac_status_t status)
{
	alarm_new(9, "Rx a data Confirm with status: %x", status);	
}



/*EOF*/
