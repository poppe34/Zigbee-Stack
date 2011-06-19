/*
 * RF230_xmega_xxx_a3.h
 *
 *  Created on: Nov 9, 2010
 *      Author: mpoppe
 */

#ifndef RF230_XMEGA_XXX_A3_H_
#define RF230_XMEGA_XXX_A3_H_
#include <avr/io.h>


#define RF230_PORT 				PORTD
#define RF230_SPI				SPID

#define SLP_TR		0x08
#define RST			0x00
#define IRQ			0x04
#define SS			0x10
#define MOSI		0x20
#define MISO		0x40
#define SCK			0x80

#endif /* RF230_XMEGA_XXX_A3_H_ */
