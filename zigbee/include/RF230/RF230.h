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
#ifndef _RF230_H
#define _RF230_H

#include "compiler.h"

#define RF230_SPI_READ			(0x80)
#define RF230_SPI_WRITE			(0xC0)
#define RF230_SPI_FRAME_WRITE	(0x60)
#define RF230_SPI_FRAME_READ	(0x20)
#define RF230_SPI_SRAM_READ		(0x00)
#define RF230_SPI_SRAM_WRITE	(0x40)

void 	rf230_init(void);

void	RF230registerBitWrite(uint8_t address, uint8_t mask, uint8_t position, uint8_t value);
void 	RF230registerWrite(uint8_t address, uint8_t value);
void 	RF230frameWrite(uint8_t *frame_wr, uint8_t len);

uint8_t RF230BitRead(uint8_t address, uint8_t mask, uint8_t position);
uint8_t RF230registerRead(uint8_t addr);
uint8_t RF230frameRead(uint8_t *frame_rx);
uint8_t RF230FrameBufferRead(uint8_t *frame_rx);

void 	rc_reset(void);
void 	PHY_TxIrqCB(uint8_t irq_status);

void set_irq_callBack(void *cb);
#endif

/* EOF */
