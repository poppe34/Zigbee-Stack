/*
 * RF230_mega1281.h
 *
 *  Created on: Nov 9, 2010
 *      Author: mpoppe
 */

#ifndef RF230_MEGA1281_H_
#define RF230_MEGA1281_H_

#define SLP_TR            (0x06)  //!< Pin number that corresponds to the SLP_TR line.
#define DDR_SLP_TR        (DDRB)  //!< Data Direction Register associated with the SLP_TR pin.
#define PORT_SLP_TR       (PORTB) //!< Port Register associated with the SLP_TR pin.
#define PIN_SLP_TR        (PINB)  //!< Pin Register associated with the SLP_TR pin.
#define RST               (0x05)  //!< Pin number that corresponds to the RST line.
#define DDR_RST           (DDRB)  //!< Data Direction Register associated with the RST pin.
#define PORT_RST          (PORTB) //!< Port Register associated with the RST pin.
#define PIN_RST           (PINB)  //!< Pin Register associated with the RST pin.
#define TST               (0x04)  //!< Pin number that corresponds to the TST line.
#define DDR_TST           (DDRB)  //!< Data Direction Register associated with the TST pin.
#define PORT_TST          (PORTB) //!< Port Register associated with the TST pin.
#define PIN_TST           (PINB)  //!< Pin Register associated with the TST pin.
#define IRQ               (0x04)  //!< Pin number that corresponds to the IRQ line.
#define DDR_IRQ           (DDRD)  //!< Data Direction Register associated with the IRQ pin.
#define PORT_IRQ          (PORTD) //!< Port Register associated with the IRQ pin.
#define PIN_IRQ           (PIND)  //!< Pin Register associated with the IRQ pin.

#define RF230_SPI_PORT    (PORTB) //!< Port Register associated with the SPI module.
#define RF230_SPI_DDR     (DDRB)  //!< Data Direction Register associated with the SPI module.
#define RF230_SPI_SS       (0x00)
#define RF230_SPI_SCK      (0x01)
#define RF230_SPI_MOSI     (0x02)
#define RF230_SPI_MISO     (0x03)

#define TIMER3				(0x06)

#define	DDR_TIMER3			(DDRE)
#define PORT_TIMER3			(PORTE)
#define PIN_TIMER3			(PINE)

#define RF230_SPI_PRR     (PRR0)  //!< Power reduction register associated with the RF230 radio transceiver.
#define RF230_SPI_PRR_BIT (PRSPI) //!< Bit in the PRR associated with the RF230 radio transceiver.
#define RF230_SPI_SPCR	  (SPCR) // SPI control Register
#define RF230_SPI_SPCR_SPE 	(SPE)
#define RF230_SPI_SPCR_MSTR (MSTR)
#define RF230_SPI_SPCR_SPR0	(SPR0)
#define RF230_SPI_FINISHED_FLAG (SPIF)
#define RF230_SPI_SPSR		(SPSR)

#define RF230_SPI_DATA	(SPDR)


#endif /* RF230_MEGA1281_H_ */
