/*
 * NWK_neighborTable.h
 *
 * Created: 6/17/2011 3:40:40 PM
 *  Author: mpoppe
 */ 


#ifndef NWK_NEIGHBORTABLE_H_
#define NWK_NEIGHBORTABLE_H_

typedef enum RELATIONSHIP{
	parent 			= 0x00,
	child  			= 0x01,
	sibling 		= 0x02,
	bastard			= 0x03,
	prev_child 		= 0x04,
	unauth_child 	= 0x05,
}nwk_relation_t;

typedef struct NEIGHBOR{
	struct NEIGHBOR		 	*next;
	addr_t	 				extendAddr;
	addr_t					shortAddr;
	uint8_t					type;
	Bool					RxOnWhenIdle;
	nwk_relation_t			relation;
	uint8_t					failure;
	uint8_t					LQI;
	uint8_t					cost;
	uint8_t					age;
	uint32_t				beaconTime;
	uint32_t				beaconOffset;
	uint64_t				extendPANid;
	uint8_t					logicalChannel;
	uint8_t					depth;
	uint8_t					beaconOrder;
	uint8_t					permitJoining;
	uint8_t					potentialParent;


//TODO:	add optional fields
}nwk_neigh_t;


#endif /* NWK_NEIGHBORTABLE_H_ */