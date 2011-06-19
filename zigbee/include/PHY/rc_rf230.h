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
#ifndef _RC_ATMEL_H
#define _RC_ATMEL_H

/*================================= INCLUDES         =========================*/
#include "board.h"
#include "compiler.h"
#include "gpio.h"

#include "RF230/RF230.h"
#include "RF230/at86rf230_registermap.h"

#include "PHY/phy.h"

/*================================= MACROS           =========================*/
#define RF230_RESET_START	gpio_set_pin_low(ZIGBEE_RST)
#define RF230_RESET_END		gpio_set_pin_high(ZIGBEE_RST)

#define RF230_SLP_TR_LOW	gpio_set_pin_low(ZIGBEE_SLP_TR)
#define RF230_SLP_TR_HIGH	gpio_set_pin_high(ZIGBEE_SLP_TR)

#define RF230_STATE() 		(RF230BitRead(SR_TRX_STATUS))

/*================================= TYEPDEFS         =========================*/



/*================================= GLOBAL VARIABLES =========================*/
/*================================= LOCAL VARIABLES  =========================*/
/*================================= PROTOTYPES       =========================*/
void radio_RF230_init(void);
void turn_on_CRC(void);
void rc_reset(void);
void rc_reset_stateMachine(void);
void rc_goto_sleep(void);
void rc_wakeup(void);
cca_mode_t get_CCAmode(void);
void set_CCAmode(cca_mode_t mode);
uint8_t get_currentChannel(void);
bool set_auto_CRC_on(void);
bool set_auto_CRC_off(void);
uint8_t get_auto_CRC(void);
bool set_currentChannel(uint8_t channel);
uint8_t get_tx_pwr(void);
bool set_tx_pwr(uint8_t level);
bool set_trx_state(trx_state_t state, bool force);
bool set_rc_CLKM(uint8_t speed);
uint8_t get_rc_CLKM(void);
void rc_rx_frame(void);
bool rc_send_frame(uint8_t len, uint8_t *frame_tx);
void set_shortAddr(uint16_t addr);
uint16_t get_short_ADDR(void);
void set_PANid(uint16_t pan);
uint16_t get_PANid(void);
void set_IEEE_ADDR(uint64_t addr);
uint64_t get_IEEE_ADDR(void);
void turn_ON_CRC(void);
void I_AM_COORD(uint8_t coord);
Bool is_Coord(void);
uint16_t get_CSMA_seed(void);
bool set_CSMA(uint16_t csma);
uint8_t get_MIN_BE(void);
bool set_MIN_BE(uint8_t be);
uint8_t get_frame_retries (void);
bool set_frame_retries(uint8_t fr);
uint8_t get_CSMA_retries (void);
bool set_CSMA_retries(uint8_t Cr);
uint8_t get_aack_set_pd (void);
bool set_aack_set_pd(uint8_t aack);
#endif
/* EOF */
