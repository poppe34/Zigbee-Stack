/*
 * global_datatypes.h
 *
 *  Created on: Oct 12, 2010
 *      Author: mpoppe
 */

#ifndef GLOBAL_DATATYPES_H_
#define GLOBAL_DATATYPES_H_
#include <avr/io.h>
#include <avr/pgmspace.h>
//#include <avr/boot.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#ifndef NULL
#define NULL (void *)0
#endif // #ifndef NULL

typedef uint16_t PANid_t;
typedef uint16_t short_addr_t;
typedef uint64_t long_addr_t;

typedef enum ADDRESS_MODE{
	NO_ADDRESS = 0x00,
	none = 0x01,
	SHORT_ADDRESS = 0x02,
	LONG_ADDRESS = 0x03,
}addr_mode_t;

typedef struct ADDRESS{
	addr_mode_t mode;
	union {
		uint16_t 	shortAddr;
		uint64_t	extAddr;
	};
	uint16_t 	PANid;
}addr_t;

#define PACK
#define START_PACK
#define END_PACK

#define INLINE static inline __attribute__ ((always_inline))

#define BITS_1(f1) f1;
#define BITS_2(f1, f2) f1; f2;
#define BITS_3(f1, f2, f3)  f1; f2; f3;
#define BITS_4(f1, f2, f3, f4)  f1; f2; f3; f4;
#define BITS_5(f1, f2, f3, f4, f5)  f1; f2; f3; f4; f5;
#define BITS_6(f1, f2, f3, f4, f5, f6)  f1; f2; f3; f4; f5; f6;
#define BITS_7(f1, f2, f3, f4, f5, f6, f7)  f1; f2; f3; f4; f5; f6; f7;
#define BITS_8(f1, f2, f3, f4, f5, f6, f7, f8) f1; f2; f3; f4; f5; f6; f7; f8;

#define COMBINE(size, data) BITS_##size data

#endif /* GLOBAL_DATATYPES_H_ */
