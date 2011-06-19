/*
 * frame.h
 *
 *  Created on: Oct 12, 2010
 *      Author: mpoppe
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "compiler.h"

#define kFRAME_POOL_SIZE (10)

#define BITS_1(f1) f1;
#define BITS_2(f1, f2) f1; f2;
#define BITS_3(f1, f2, f3)  f1; f2; f3;
#define BITS_4(f1, f2, f3, f4)  f1; f2; f3; f4;
#define BITS_5(f1, f2, f3, f4, f5)  f1; f2; f3; f4; f5;
#define BITS_6(f1, f2, f3, f4, f5, f6)  f1; f2; f3; f4; f5; f6;
#define BITS_7(f1, f2, f3, f4, f5, f6, f7)  f1; f2; f3; f4; f5; f6; f7;
#define BITS_8(f1, f2, f3, f4, f5, f6, f7, f8) f1; f2; f3; f4; f5; f6; f7; f8;

#define COMBINE(size, data) BITS_##size data

#define WAIT_FOR_DURATION(time)	do{									\
									time += get_Ticks();			\
									while(time >= get_Ticks()){;}	\
								}while(0)
#define toFrame	*(NO)--

#define SET_FRAME_DATA_1(frame, info) *frame->ptr++ = info;\
											frame->length++

#define SET_FRAME_DATA_2(frame, info) 	*frame->ptr++ = (uint8_t)info;\
                                            *frame->ptr++ = (uint8_t)(info>>8);\
										    frame->length +=2

#define SET_FRAME_DATA_8(frame, info) *frame->ptr++ = (uint8_t)info;\
                                        *frame->ptr++ = (uint8_t)(info>>8);\
										*frame->ptr++ = (uint8_t)(info>>16);\
										*frame->ptr++ = (uint8_t)(info>>24);\
										*frame->ptr++ = (uint8_t)(info>>32);\
										*frame->ptr++ = (uint8_t)(info>>40);\
										*frame->ptr++ = (uint8_t)(info>>48);\
										*frame->ptr++ = (uint8_t)(info>>56);\
										frame->length +=8

#define SET_FRAME_DATA_try(frame, value, type)     *((type *)frame->ptr) = value; \
                                                    frame->ptr += sizeof(type)



#define SET_FRAME_DATA(frame, info, size) SET_FRAME_DATA_##size(frame,info)


//#define GET_FRAME_DATA(frame, type) *((type *)(frame->ptr));\
  //                                      frame->dataLength += sizeof(type);

#define GET_FRAME_DATA_1(frame, size) *frame->ptr++; \
										frame->length++

#define GET_FRAME_DATA_2(frame, size)  *((uint16_t *)(frame->ptr));\
										frame->length +=size;\
										frame->ptr +=size
#define GET_FRAME_DATA_8(frame, size)  *((uint64_t *)(frame->ptr));\
											frame->length +=size;\
											frame->ptr +=size

#define GET_FRAME_DATA(frame, size) GET_FRAME_DATA_##size(frame, size)


typedef uint16_t PANid_t;
typedef uint16_t short_addr_t;
typedef uint64_t long_addr_t;

typedef enum FRAME_DIRECTION{
	EMPTY		= 0x00,
	OUTGOING	= 0x01,
	INCOMING 	= 0x02,
}direction_t;

typedef enum{
	mac_hdr = 0x01,
	nwk_hdr = 0x02,
	aps_hdr = 0x03,
	payload = 0x04,
	rx_data = 0x05,
}hdr_type_t;

typedef enum ADDRESS_MODE{
	NO_ADDRESS = 0x00,
	none = 0x01,
	SHORT_ADDRESS = 0x02,
	LONG_ADDRESS = 0x03,
}addr_mode_t;

typedef struct ADDRESS{
	uint8_t mode;
	union {
		uint16_t 	shortAddr;
		uint64_t	extAddr;
	};
	uint16_t 	PANid;
}addr_t;

typedef struct mpdu_hdr
{
	uint8_t hdr[20];
	uint8_t  *ptr;
	uint8_t length;
}mac_hdr_t;

typedef struct npdu_hdr
{
	uint8_t hdr[20];
	uint8_t  *ptr;
	uint8_t length;
}nwk_hdr_t;

typedef struct apdu_hdr
{
	uint8_t hdr[20];
	uint8_t  *ptr;
	uint8_t length;
}aps_hdr_t;

typedef struct 
{
	uint8_t pl[100];
	uint8_t	*ptr;
	uint8_t length;
}payload_t;

typedef struct
{
	uint8_t  frame[128];
	uint8_t	 *ptr;
	uint8_t  length;
}frameData_t;

typedef struct FRAME
{
	struct FRAME        *next;
	uint8_t             handler;
	uint32_t 			timestamp;
	uint8_t				LQI;
	//[aMaxPHYPacketSize+1]; TODO:Add this in the future
	direction_t			direction;
	Bool				ackd;
	mac_hdr_t			*mac;
	nwk_hdr_t			*nwk;
	aps_hdr_t			*aps;
	payload_t			*payload;
	frameData_t			*Rx_fr;
}frame_t;




/**************************************************
 * 	PROTOTYPES
 **************************************************/
void    frame_init(void);
void    frame_free(frame_t *fr);
void    frame_sendWithFree(frame_t *fr);
void    frame_clearAll(void);
frame_t *frame_new(void);
voidPtr frame_hdr(hdr_type_t type);

#endif /* FRAME_H_ */
