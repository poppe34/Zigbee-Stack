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

#include <frame.h>
#include "conf_zigbee.h"
#include "phy/phy.h"

/*================================= MACROS           =========================*/
/*================================= TYEPDEFS         =========================*/
/*================================= GLOBAL VARIABLES =========================*/

/*================================= LOCAL VARIABLES  =========================*/

phy_pib_t ppib;
/*================================= PROTOTYPES       =========================*/
/*================================= SOURCE CODE      =========================*/

void phy_init(void){

	ppib.phyCurrentChannel = DEFAULT_CHANNEL;
	ppib.phyCurrentPage = DEFAULT_CHANNELPAGE;
	ppib.phyChannelsSuppported[0] = (0x07FFF800);  //TODO: I need to fill out the rest of the channels supported but this is really not important
	ppib.phyTransmitPower = 0x00;//TODO: I don't know what this really does in the grand scheme... Will fix later.
	ppib.phyCCAMode = cca_carrier_sence;
	ppib.phyCurrentPage = 0x00;

//	TODO:	I need to understand these values right now I am going to just throw in values... these need to be variables setup in phy.h
//			This should be what the values are if we are in a 2.4 GHz system

	ppib.phySHRDuration = 40;
	ppib.phySymbolsPerOctet = 2;
	ppib.phyMaxFrameDuration = (10 + 256);
	
	
}

phy_pib_t *get_phyPIB(void){
	return &ppib;
}



/*EOF*/
