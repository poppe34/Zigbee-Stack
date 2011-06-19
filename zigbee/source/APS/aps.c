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
#include "phy/phy.h"
#include "RF230/RF230.h"
#include "mac/mac.h"
#include <aps/aps.h>


/*================================= MACROS           =========================*/
/*================================= SOURCE CODE      =========================*/
uint8_t APS_count;

void APS_init(void){
	APS_count = 0;
}

uint8_t get_APS_Count(void){
	APS_count++;
	return((APS_count));
}


/*EOF*/
