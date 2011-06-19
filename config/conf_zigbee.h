/*
 * conf_zigbee.h
 *
 * Created: 4/18/2011 10:13:42 AM
 *  Author: mpoppe
 */ 


#ifndef CONF_ZIGBEE_H_
#define CONF_ZIGBEE_H_

#include <stdint.h>
/*================================= MACROS           =========================*/

/***********************************
 * Chip Select
 ***********************************/
//#define __AVR_ATxmega256A3__
//#define __AVR_ATxmega64A3__
//#define __AVR_ATmega1281__
//#define __AVR_ATmega1284p__

/***********************************
* Chip Series
***********************************/
//#define __XMEGA
//#define	__MEGA

/***********************************
* Debugging mode
***********************************/
//Debugging mode
//#define DEBUG

 /***********************************
  * Clock Speed
  ***********************************/
//Select Clock Speed
//#define SYSTEM_CLK_1Mhz
//#define SYSTEM_CLK_1Mhz
//#define SYSTEM_CLK_1Mhz
//#define SYSTEM_CLK_1Mhz
//#define SYSTEM_CLK_16Mhz
//#define SYSTEM_CLK_32Mhz

 /***********************************
  * ZIGBEE addressing
  ***********************************/
#define SHORT_ADDR 	0xFFFF
#define PAN_ID		0xFFFF
#define IEEE_ADDR	0x000225ffff17fefd

#define DEFAULT_CHANNEL		(11)
#define DEFAULT_PANID		0xBABE
#define DEFAULT_CHANNELPAGE	(0)
#define DEFAULT_EXT_PANID	0xAAAAAAAAAAAAAAAA
#define DEFAULT_COORD		(0)



#define on					(1)
#define off					(0)
#define null				0x00

#define	SYMBOLS_PER_US		(4)
/*================================= TYEPDEFS         =========================*/


/*================================= GLOBAL VARIABLES =========================*/
/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/
void avr_init(void);



#endif /* CONF_ZIGBEE_H_ */