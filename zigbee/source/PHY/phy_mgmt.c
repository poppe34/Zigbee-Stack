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

#include "RF230/at86rf230_registermap.h"

#include "phy/rc_rf230.h"
#include "phy/phy.h"
/*================================= MACROS           =========================*/

/*================================= TYEPDEFS         =========================*/
/*================================= GLOBAL VARIABLES =========================*/
/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/
/*================================= SOURCE CODE      =========================*/


bool trx_state_request(trx_state_t state){
        //This goes beyond the 802.15.4 states due to RF230 having more states than
        //specified in the standard.
        //
        //Pay attention to this section an make sure we can't put it into more states
        //than we might want.
    uint8_t status;

    switch(state)
	{
        case(FORCE_TRX_OFF):
            status = set_trx_state(state, true);
        break;

        default:
            status = set_trx_state(state, false);
        break;
    }
    return status;
}

ed_request_t ed_request(void) {
    trx_state_t current_state;
    ed_request_t request;

    current_state = RF230_STATE();

    switch(current_state) {

        case(TRX_OFF):

            request.status = ED_TRX_OFF;

        break;

        case(PLL_LOCK):

            request.status = ED_TX_ON;
        break;

        default:

            request.level = get_tx_pwr();
            request.status = ED_SUCCESS;
        break;


    }

    return(request);

}
cca_status_t phy_CCA(void) {

	cca_status_t status;
	trx_state_t state;
	uint8_t rd_status;
	uint8_t rd_result;
	uint8_t reg;

	state = RF230_STATE(); 

	if(state == PLL_ON){

		status = CCA_BUSY;
	}

	else if(state == TRX_OFF){

		status = CCA_TRX_OFF;
	}

	else {
		reg = RF230BitRead(SR_CCA_MODE);


		RF230registerBitWrite(SR_CCA_REQUEST, 0x01);
	
		rd_status = 0;
		
		while(!(rd_status)) {
		
			reg = RF230registerRead(RG_TRX_STATUS);

			rd_status = reg;
			rd_status = ((rd_status >> 7) & 0x01);
	
			
			rd_result = reg;
			rd_result = ((rd_result >> 6) & 0x01);
	
		
			if(rd_result == 0) {
				status = CCA_BUSY;
			}

			else {
				status = CCA_IDLE;
			}
		}
	}

	return status;
}

phy_pib_request_t PIB_request(phy_pib_att_t pib) {

	phy_pib_request_t request;
	phy_pib_t test;
	phy_pib_status_t stat = req_unsupported;

	request.attribute = pib;

	switch(pib) {

		case(phyCurrentChannel):

//			request.value.phyCurrentChannel = get_currentChannel();
//			stat = req_success;

		break;

		case(phyChannelsSupported):
			

		break;

		case(phyTransmitPower):

	//		request.value.phyTransmitPower = get_tx_pwr();
//			stat = req_success;

		break;

		case(phyCCAMode):
			
//			request.value.phyCCAMode = get_CCAmode();
//			stat = req_success;

		break;

		case(phyCurrentPage):

		break;



		case(phySymbolsPerOctet):

		break;

		request.status = stat;
		return request;

	}	

}

/*EOF*/
