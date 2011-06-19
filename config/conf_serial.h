/*
 * conf_serial.h
 *
 *  Created on: Feb 26, 2011
 *      Author: mattpoppe
 */

#ifndef CONF_SERIAL_H_
#define CONF_SERIAL_H_

#include "compiler.h"
//#include "usart.h"



#define USART_BAUDRATE           38400
#define USART_CHAR_LENGTH        USART_CHSIZE_8BIT_gc
#define USART_PARITY             USART_PMODE_DISABLED_gc
#define USART_STOP_BIT           NO
#define USART_PORT               &USARTD0

U8 serial_init(void);

#endif /* CONF_SERIAL_H_ */
