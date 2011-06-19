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

#ifndef APS_H_
#define APS_H_

/*================================= INCLUDES         =========================*/
#include "compiler.h"
#include <conf_zigbee.h>

/*================================= MACROS           =========================*/

#define SEC_ENABLED			(0)
#define USE_SEC_KEY			(2)
#define ACK_TRANS			(4)
#define FRAG_PERMIT			(8)

#define FRAME_TYPE_DATA 	(0)
#define FRAME_TYPE_COMMAND	(1)
#define	FRAME_TYPE_ACK		(2)
#define	FRAME_TYPE_RESERVED	(3)

#define DEL_MODE_UNICAST	(0)
#define	DEL_MODE_INDIRECT	(1)
#define	DEL_MODE_BROADCAST	(2)
#define	DEL_MODE_GRP_ADDR	(3)

#define TRANS_FRAGMENTED	(0)
#define FIRST_FRAG_FRAME	(1)
#define PART_OF_FRAG		(2)

#define DATA_FRAME_ACK		(0)
#define COMMAND_FRAME_ACK	(1)




/*================================= TYEPDEFS         =========================*/

typedef enum ADDR_MODE{

	NO_DST_ADDR_OR_ENDPOINT,
	GRP_ADDRESS,
	DST_ADDR_AND_ENDPOINT,
	LONG_DST_ADDR_AND_ENDPOINT,

}aps_dstAddrMode_t;

typedef struct ASPDE_DATA{

	aps_dstAddrMode_t 	dstAddrMode;
	uint16_t 			dstAddr;
	uint8_t 			dstEndpoint;
	uint16_t			profileID;
	uint16_t			clusterID;
	uint8_t				srcEndpoint;
	uint8_t				ADSUlength;
	uint8_t				*asdu;//TODO: need to make this a different data type like apdu_t
	uint8_t				TxOptions;
	uint8_t				radius;

}apsde_data_t;



typedef struct FCF_STRUCTOR{

	uint8_t fcf_fr_type;
	uint8_t fcf_del_type;
	uint8_t fcf_ack_format;
	uint8_t	fcf_security;
	uint8_t	fcf_ack_request;
	uint8_t	fcf_ext_header;

}fcf_t;
typedef enum APDU_STATUS{

	SUCCESS,
	NO_BOUND_DEVICE,
	NOT_SUPPORTED,
	NO_SHORT_ADDR,

}apdu_status_t;
typedef struct APDU_FRAME_CONSTRUCT{
	fcf_t 		aps_fcf;
	uint8_t 	dstEndpoint;
	uint16_t 	Addr; //TODO make a union for group or destination addr.
	uint16_t 	clusterID;
	uint16_t	 profileID;
	uint8_t  	srcEndpoint;
	uint8_t  	APScounter;
	uint8_t  	*extHeader;
	uint8_t  	*payload;//TODO: look into changing this.
}apdu_t;

/*================================= GLOBAL VARIABLES =========================*/
uint8_t APS_counter;


#endif /* APS_H_ */
