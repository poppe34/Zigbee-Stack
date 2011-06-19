
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
 * Copyright (c) 2010 ,
 *
 *
 *****************************************************************************/
#include "compiler.h"
#include "RF230/RF230.h"
#include "phy/rc_rf230.h"
#include "spi_master.h"
#include "zigbee_task.h"
#include "LED.h"
#include "alarms_task.h"

struct spi_device SPI_DEVICE_ZIGBEE = {
	//! Board specific select id
	.id = SPI_ZIGBEE_DEVICE_ID
};
void rf230_init(void)
{
	//Setup SPI for Zigbee and Clear power reduction
	spi_master_init(SPI_ZIGBEE);

    //Setup SPI speed for Zigbee    
	spi_master_setup_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE, SPI_MODE_0,
			SPI_ZIGBEE_DEFAULT_BAUDRATE, 0);

	spi_enable(SPI_ZIGBEE);

	radio_RF230_init();
    
	turn_ON_CRC();

	alarm_new(9, "CRC Started \0");
	
    
}

uint8_t RF230registerRead(uint8_t addr)
{
    uint8_t temp_addr;
    uint8_t register_value = 0;


    temp_addr = addr;
    temp_addr |= RF230_SPI_READ; // add mask to make register read
    
	cli();

    spi_select_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE); // INITIATE THE TRANSFER

    spi_write_once(SPI_ZIGBEE, temp_addr); // PLACE ADDRESS IN DATA REGISTER AND SEND TO RF230 and wait for transmission

    register_value = spi_read_once(SPI_ZIGBEE); // Read data from the transmission

    spi_deselect_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE); // end of transmissions

    sei();

    return(register_value);// RETURN THE DATA FROM THE READ

}

uint8_t RF230BitRead(uint8_t address, uint8_t mask, uint8_t position)
{

    uint8_t temp_value = 0;
    temp_value = RF230registerRead(address); //Read full byte of register

    temp_value &= mask; //Mask off un-needed bits
    temp_value >>= position;//shift data
    return(temp_value);

}

void RF230registerBitWrite(uint8_t address, uint8_t mask, uint8_t position, uint8_t value)
{

    uint8_t temp_value = 0;

    temp_value |= RF230registerRead(address);// read current register byte

    temp_value &= ~mask;//keep all other bits outside the mask

    /* Shift bits need into appropriate position then mask off all other bits */
    value <<= position;
    value &= mask;

    /*Add previous values into register*/
    value |= temp_value;

    RF230registerWrite(address, value);
}

void RF230registerWrite(uint8_t address, uint8_t data)
{
    uint8_t temp_address;

    temp_address = address;
    temp_address |= RF230_SPI_WRITE;

    cli();
    /* Start transmission */
    spi_select_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE);
    /* Send Address */
    spi_write_once(SPI_ZIGBEE, temp_address);
    /* Send New Register value */
	spi_write_once(SPI_ZIGBEE, data);
	/* End Transmission */
	spi_deselect_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE); // end of transmissions

    sei();

}

void RF230frameWrite(uint8_t *frame_wr, uint8_t len)
{

	report_packet(frame_wr, len);
    cli();

    /* Start transmission */
    spi_select_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE);
    
	spi_write_once(SPI_ZIGBEE, RF230_SPI_FRAME_WRITE);
	
	spi_write_once(SPI_ZIGBEE, len);
	
    spi_write_packet(SPI_ZIGBEE, frame_wr, len);
	
    spi_deselect_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE); // end of transmissions

    sei();
}// end RF230frameWrite

uint8_t RF230frameRead(uint8_t *frame_rx)
{
    uint8_t dummy = 0x00;
	uint8_t len, index = 0, length;

    cli();
    /* Start transmission */
    spi_select_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE);
    
	spi_write_once(SPI_ZIGBEE, RF230_SPI_FRAME_READ);
    /* Wait for transmission complete */
    len = spi_read_once(SPI_ZIGBEE);
    length = len;
    
	spi_read_packet(SPI_ZIGBEE, frame_rx, len);
    
	spi_deselect_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE); // end of transmissions

    sei();
	
    return length;
}// end RF230frameRead

uint8_t RF230FrameBufferRead(uint8_t *frame_rx)
{
	    uint8_t dummy = 0x00;
	uint8_t len, index = 0, length;

    cli();
    /* Start transmission */
    spi_select_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE);
    
	spi_write_once(SPI_ZIGBEE, RF230_SPI_SRAM_READ);
    /* Wait for transmission complete */
    len = spi_read_once(SPI_ZIGBEE);
    length = len;
    
	spi_read_packet(SPI_ZIGBEE, frame_rx, len);
    
	spi_deselect_device(SPI_ZIGBEE, &SPI_DEVICE_ZIGBEE); // end of transmissions
	//report_packet(frame_rx, len);
    sei();
    return length;
}

