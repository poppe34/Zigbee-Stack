/*
 * security.h
 *
 * Created: 5/27/2011 6:34:31 AM
 *  Author: matt
 */ 


#ifndef SECURITY_H_
#define SECURITY_H_

typedef struct security_packet{
	uint8_t     securityLevel;
	uint8_t     keyIdMode;
	uint8_t     keyIndex;
	union {
		uint8_t     longKeySource[8];
		uint8_t     shortKeySource[4];
	};
}security_t;



#endif /* SECURITY_H_ */